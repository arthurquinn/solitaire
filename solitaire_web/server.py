#/usr/bin/python3

from flask import Flask, render_template, request
from flask_socketio import SocketIO
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

@socketio.on("message")
def handle_message(message):
  print(message)

@socketio.on("my event")
def handle_my_event(message):
  print("received my event: " + str(message))

if __name__ == "__main__":
  print("Running app...")
  socketio.run(app)

