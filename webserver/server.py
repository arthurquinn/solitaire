#!/usr/bin/python3

from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)

@app.route("/")
def index():
  return render_template("index.html")

if __name__ == "__main__":
  app.run(port=8080)
