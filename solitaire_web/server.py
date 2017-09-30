#!/usr/bin/python3
from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit
from handlers.login_handler import Login


app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/login", methods=['GET', 'POST'])
def route_login():
  if request.method == 'POST':
    login = Login(request.form['username'], request.form['password'])
    return login.login()
  else:
    return render_template("login.html")

@app.route("/")
def route_index():
  return render_template("index.html")

"""
TODO: Implement logger instead of printing to console, look into python logging library
"""
@socketio.on("message")
def handle_message(message):
  print("Invalid message received (all messages should have target event)")

@socketio.on("command")
def handle_command(command):
  print(command)
  retval = {
    "response": "ok",
    "update": [{
      "pile": 0,
      "push": [ "d10" ],
      "pop": 0
    }, {
      "pile": 6,
      "push": [ "ha" ],
      "pop": 0
    }, {
      "pile": 7,
      "push": [ "c3", "d2" ],
      "pop": 0
    }, {
      "pile": 8,
      "push": [ "s4", "d5", "sq" ],
      "pop": 0
    }, {
      "pile": 9,
      "push": [ "hk", "dj", "c7", "s9" ],
      "pop": 0
    }, {
      "pile": 10,
      "push": [ "ca", "c2", "d3", "d4", "sk" ],
      "pop": 0
    }, {
      "pile": 11,
      "push": [ "hq", "hj", "h2", "h3", "h9", "h5" ],
      "pop": 0
    }, {
      "pile": 12,
      "push": [ "c4", "c5", "c6", "c8", "c9", "c10", "cj" ],
      "pop": 0
    }]
  }
  #this will eventually be somewhere else in the code after asynchronus processing of the command,
  #but for now we can leave it here for testing
  emit("command_response", retval, json=True)


if __name__ == "__main__":
  print("Running app...")
  socketio.run(app)

