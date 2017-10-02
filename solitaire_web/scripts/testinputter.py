#!/usr/bin/python3

import sys
import os
import subprocess
import json
import time

if __name__ == "__main__":
  engine = subprocess.Popen(["../../solitaire_engine_linux/build/solitaire_engine", "--debug"], \
    stdin=subprocess.PIPE, \
    stdout=subprocess.PIPE, \
    stderr=subprocess.PIPE, \
    universal_newlines=True)

  payload = json.loads(engine.stdout.readline())
  if payload["response"] == "ok":
    print("payload valid")
    print(payload)
    cmd = {}
    cmd["cmd"] = "draw"
    cmd_str = json.dumps(cmd) + "\n"
    for i in range(10):
      engine.stdin.write(cmd_str)
      print("write: " + cmd_str.rstrip())
      engine.stdin.flush()
      print("recv: " + engine.stdout.readline().rstrip())

    print("killing engine")
    engine.kill()
    engine.wait()
  else:
    print("error connecting to engine")

  input("press enter to exit")