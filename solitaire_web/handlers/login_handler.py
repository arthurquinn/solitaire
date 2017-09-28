#/usr/bin/python3

from pymongo import MongoClient
import bcrypt

class Login(object):
  def __init__(self, username, password):
    self.form_username = username
    self.form_password = self.encode(password)

    client = MongoClient('localhost', 27017)
    database = client.user_db
    collection = database.users
    self.users = collection

    # ==================== TEST ==================== #
    collection.remove({})
    collection.insert_one({
      "username": 'mo@test.com',
      "display_name": "mo",
      "password": bcrypt.hashpw(self.encode("ic"), bcrypt.gensalt())
    })
    # ==================== TEST ==================== #


  def encode(self, text):
    return text.encode('utf8')


  def check_credentials(self, existing_user):
    return existing_user != None and bcrypt.hashpw(self.form_password, existing_user['password']) == existing_user['password']


  def login(self):
    existing_user = self.users.find_one({"username": self.form_username})

    if(self.check_credentials(existing_user)):
      return 'Logged in!'
    else:
      return 'Username and/or password incorrect.'

