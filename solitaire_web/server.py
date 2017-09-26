#/usr/bin/python3

from flask import Flask, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/")
def route_index():
  return render_template("index.html")

@socketio.on("message")
def handle_message(message):
  print(message)

@socketio.on("my event")
def handle_my_event(message):
  print("received my event: " + str(message))

if __name__ == "__main__":
  print("Running app...")
  socketio.run(app)