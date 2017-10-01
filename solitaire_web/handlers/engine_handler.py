import sys
import os
import subprocess
import json

class Engine(object):
  def __init__(self, game_name, debug=False):
    engine_execs = {
      "solitaire": "../solitaire_engine_linux/build/solitaire_engine"
    }
    self.engine = None
    self.engine_path = engine_execs[game_name]
    self.debug_arg = "--debug" if debug else ""


  def run(self):  
    # TODO: Pass parameters to executable for debugging
    self.engine = subprocess.Popen([self.engine_path, self.debug_arg], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    response = json.loads(self.engine.stdout.readline().strip())

    if(response['response'] == 'ok'):
      return response
    
    return 'Error connecting to engine.'


  def send(self, command):
    if(self.engine != None):
      self.engine.stdin.write(command)
      self.engine.stdin.flush()
      return json.loads(self.engine.stdout.readline().strip())

    return 'Engine has not been initialized.'


  def close(self):
    if(self.engine != None):
      self.engine.terminate()

