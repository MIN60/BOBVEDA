from flask import Flask

app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    return "bobveda 서버 실행 중"

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
