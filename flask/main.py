from flask import Flask, request, jsonify
import json
import time
import threading
import os
import requests
from slack_sdk import WebClient
from slack_sdk.errors import SlackApiError
from slack_sdk import WebClient
from dotenv import load_dotenv

load_dotenv()
app = Flask(__name__)

#토큰 설정
SLACK_TOKEN = os.environ.get("SLACK_TOKEN")
if not SLACK_TOKEN:
    print("토큰오류남")
    exit(1)

client = WebClient(token=SLACK_TOKEN)

# 사용자별 명령 정보
user_commands = {}
# 파일 저장 폴더
UPLOAD_FOLDER = './uploads'
RESULT_FOLDER = './results'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
os.makedirs(RESULT_FOLDER, exist_ok=True)


@app.route("/", methods=["GET"])
def index():
    return "bobveda 서버 실행"

#슬랙 명령어 파싱
def parse_command(text):
    div_group = None #나눌 조
    remove_p = [] # 뺄사람ㅁ

    parts = text.split('-', 1) # -ㄱㅁㅈ

    if parts and parts[0].strip(): #나눌 조 입력했는지
        try:
            div_group = int(parts[0].strip()) #그룹수가 문자열로 나와서 정수로 바꿔줘야됨
        except ValueError:
            return None, []

    if len(parts) > 1 and parts[1].strip(): #제외할 사람 있는지
        exclude_text = parts[1].strip() 
        remove_p = [name.strip() for name in exclude_text.split(',')]

    #그룹수, 제거자 파싱
    return div_group, remove_p

# 파일 업로드 리마인드 (30초 뒤에도 안 올리면 알림림)
def remind_file(user_id):
    time.sleep(20)
    if user_id in user_commands and user_commands[user_id].get("waiting_for_file", False):
        try:
            client.chat_postMessage(
                channel=user_commands[user_id]['channel_id'],
                text="'이름 성별'로 이루어진 txt파일을 기다리고 있습니다...\n예시:\n김도현 M\n남윤서 F"
            )
            print(f"!!!리마인드 메시지 전송 완료 {user_id}")
        except SlackApiError as e:
            print(f"!!!리마인드 실패함: {e}")

# 커맨드 처리
@app.route("/slack/bobveda", methods=["POST"])
def handle_bobveda():
    user_id = request.form.get("user_id")
    user_name = request.form.get("user_name")
    text = request.form.get("text")
    channel_id = request.form.get("channel_id")

    print(f"밥베다 호출\n 사용자: {user_name} 명령어 내용: {text}")

    div_group, remove_p = parse_command(text)
    
    # 예외처리
    if div_group is None:
        return jsonify({
            "response_type": "ephemeral",
            "text": "올바른 형식으로 입력해주세요. 예: '/bobveda 4 -김민정, 옹미령, 장동철'"
        })

    user_commands[user_id] = {
        'timestamp': time.time(),
        'channel_id': channel_id,
        'div_group': div_group,
        'remove_p': remove_p,
        'waiting_for_file': True
    }

    # 리마인드 스레드 실행
    threading.Thread(target=remind_file, args=(user_id,), daemon=True).start()

    return jsonify({
        "response_type": "in_channel",
        "text": f"밥의 한계를 베다! {user_name}님이 요청한 `{div_group}명 랜밥` 시작!\n 제외 인원: {', '.join(remove_p) if remove_p else '없음'}\n 이제 멤버 목록 파일을 업로드해주세요."
    })
    
@app.route("/slack/events", methods=["POST"])
def slack_events():
    data = request.get_json() #slack 데이터 파싱

    # 슬랫 통신 응답
    if "challenge" in data:
        return jsonify({"challenge": data["challenge"]})

    event = data.get("event", {})
    event_type = event.get("type")

    #파일 이벤트 처리
    if event_type in ("file_shared", "file_created"):
        user_id = event.get("user_id") or event.get("user")
        file_id = event.get("file_id") or event.get("file", {}).get("id")

        if user_id in user_commands and user_commands[user_id].get('waiting_for_file'):
            process_file(user_id, file_id)

    return '', 200

# 파일 처리
def process_file(user_id, file_id):
    try:
        file_info = client.files_info(file=file_id)
        file_url = file_info['file']['url_private']
        file_name = file_info['file']['name']
        channel_id = user_commands[user_id]['channel_id']
        
        client.chat_postMessage(channel=channel_id,
            text="밥배정을 시작합니다...")

        headers = {"Authorization": f"Bearer {SLACK_TOKEN}"}
        response = requests.get(file_url, headers=headers)

        if response.status_code != 200:
            client.chat_postMessage(channel=channel_id,
                text=f"다운로드에 실패했습니다 (코드: {response.status_code})")
            return

        # 유저 ID랑 저장
        file_path = os.path.join(UPLOAD_FOLDER, f"{user_id}_{file_name}")
        with open(file_path, 'wb') as f:
            f.write(response.content)

        print(f"!!!파일 저장 완료: {file_path}")
        user_commands[user_id]['waiting_for_file'] = False
        user_commands[user_id]['file_path'] = file_path

        client.chat_postMessage(channel=channel_id,
            text="조금만 기다려 주세요")

        #C 프로그램 돌리기

    except SlackApiError as e:
        print(f"Slack API 오류: {e}")
        client.chat_postMessage(channel=user_commands[user_id]['channel_id'],
            text=f"오류 {str(e)}")
    except Exception as e:
        print(f"예외 발생: {e}")
        client.chat_postMessage(channel=user_commands[user_id]['channel_id'],
            text=f"오류 {str(e)}")


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
