from flask import Flask, request, jsonify
import json
import time
import threading
from slack_sdk import WebClient

app = Flask(__name__)

# 사용자별 명령 정보
user_commands = {}

@app.route("/", methods=["GET"])
def index():
    return "bobveda 서버 실행 중"

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

# 커맨드 처리
@app.route("/slack/bobveda", methods=["POST"])
def handle_bobveda():
    user_id = request.form.get("user_id")
    user_name = request.form.get("user_name")
    text = request.form.get("text")
    channel_id = request.form.get("channel_id")

    print(f"밥베다 호출! From {user_name} → 명령어 내용: {text}")

    div_group, remove_p = parse_command(text)

    user_commands[user_id] = {
        'timestamp': time.time(),
        'channel_id': channel_id,
        'div_group': div_group,
        'remove_p': remove_p,
        'waiting_for_file': True


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
