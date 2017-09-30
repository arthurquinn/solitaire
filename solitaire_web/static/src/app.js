import Board from "./board"

$(document).ready(function() {
  let canvas = document.getElementById("game-canvas");
  let board = new Board(canvas);
  let socket = io.connect("http://" + document.domain + ":" + location.port);
  socket.on("connect", function() {
    socket.emit("command", {
      "cmd": "init"
    });
    socket.on("command_response", function(response) {
      console.log("command_response received");
      if (response.response == "ok") {
        for (let update of response.update) {
          board.update(update.pile, ...update.push);
        }
        board.draw();
      } else {
        console.error("bad command -- some kind of error to user, e.g. you cant do that move, guy")
      }
    })
  });
  // setInterval(function() {
  //   board.draw();
  // }, 1000);
});

