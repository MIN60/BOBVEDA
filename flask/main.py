from flask import Flask, request, jsonify
import json
import time
import threading
import os
import requests
import subprocess
from slack_sdk import WebClient
from slack_sdk.errors import SlackApiError
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

        run_c_program(user_id)

    except SlackApiError as e:
        print(f"Slack API 오류: {e}")
        client.chat_postMessage(channel=user_commands[user_id]['channel_id'],
            text=f"오류 {str(e)}")
    except Exception as e:
        print(f"예외 발생: {e}")
        client.chat_postMessage(channel=user_commands[user_id]['channel_id'],
            text=f"오류 {str(e)}")


def run_c_program(user_id):
    command_info = user_commands[user_id]
    input_file = command_info['file_path']
    output_file = os.path.join(RESULT_FOLDER, f"result_{user_id}.txt")
    exclude_list = ','.join(
        command_info['remove_p']) if command_info['remove_p'] else ""
    channel_id = command_info['channel_id']

    try:
        print(f"제외자 목록 (C로 전달됨): '{exclude_list}'")
        cmd = ["./group_maker", input_file, exclude_list, output_file]
        print(f"실행할 명령어: {cmd}")

        result = subprocess.run(cmd, capture_output=True, text=True)

        if result.returncode != 0:
            client.chat_postMessage(channel=channel_id,
                                    text=f"C 프로그램 오류\n```{result.stderr}```")
            return

        if os.path.exists(output_file):
            with open(output_file, 'r', encoding='utf-8') as f:
                result_content = f.read()

            client.chat_postMessage(channel=channel_id,
                                    text=f"밥배정 완료!\n```{result_content}```")

            save_group_history(user_id, result_content)
        else:
            client.chat_postMessage(channel=channel_id, text="파일을 찾을 수 없습니다.")

    except Exception as e:
        client.chat_postMessage(channel=channel_id, text=f"오류 발생: {str(e)}")
        print(f"오류: {e}")


# 결과 저장
def save_group_history(user_id, group_result):
    history_file = 'group_history.json'
    if os.path.exists(history_file):
        # 안깨지게
        with open(history_file, 'r', encoding='utf-8') as f:
            try:
                history = json.load(f)
            except json.JSONDecodeError:
                history = {}
    else:
        history = {}

    timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
    history.setdefault(user_id, []).append({
        'timestamp': timestamp,
        'result': group_result
    })

    with open(history_file, 'w', encoding='utf-8') as f:
        json.dump(history, f, ensure_ascii=False, indent=2)



@app.route("/", methods=["GET"])
def index():
    return "bobveda 서버 실행"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
