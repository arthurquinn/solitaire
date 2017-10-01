#!/usr/bin/python3
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
    retval = engine.send(command)

  # this will eventually be somewhere else in the code after asynchronus processing of the command,
  # but for now we can leave it here for testing
  emit("command_response", retval, json=True)


@socketio.on("disconnect")
def handle_disconnect():
  engine.close()


if __name__ == "__main__":
  print("Running app...")
  socketio.run(app)
