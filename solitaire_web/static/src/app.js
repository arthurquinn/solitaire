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
      console.log(response);
    })
  });
});
