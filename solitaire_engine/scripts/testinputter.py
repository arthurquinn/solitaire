import sys
import subprocess
import json

if __name__ == "__main__":
  response = "NOT_STARTED"
  engine = subprocess.Popen(["../Debug/solitaire_engine.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
  while engine.poll() is None and response is not "EXIT":
    raw = str(engine.stdout.readline(), "utf-8").rstrip()
    print(raw)
    if raw:
      payload = json.loads(raw)
      print(payload["response"] if "response" in payload else "NONE")
  print("Done!")
  sys.exit(0)