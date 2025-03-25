from flask import Flask, request, jsonify
import json
import time

app = Flask(__name__)

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


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
