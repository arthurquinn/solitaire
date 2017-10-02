#!/usr/bin/python3

import json

from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit
from handlers.login_handler import Login
from handlers.engine_handler import Engine


app = Flask(__name__)
#app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
engine = Engine('solitaire', debug=True)


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


# TODO: Implement logger instead of printing to console, look into python logging library
@socketio.on("message")
def handle_message(message):
  print("Invalid message received (all messages should have target event)")


@socketio.on("command")
def handle_command(command):
  if(command['cmd'] == 'init'):
    retval = engine.run()
  else:
    print("sending: " + json.dumps(command))
    retval = engine.send(json.dumps(command))
  
  # this will eventually be somewhere else in the code after asynchronus processing of the command,
  # but for now we can leave it here for testing
  print("emitting " + str(retval))
  emit("command_response", retval)


@socketio.on("disconnect")
def handle_disconnect():
  engine.close()


if __name__ == "__main__":
  print("Running app...")
  socketio.run(app)
