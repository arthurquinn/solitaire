import GameBoard from './game_board'

var socket = io.connect("http://" + document.domain + ":" + location.port);
socket.on("connect", function() {
  socket.emit("my event", {data: "I\'m connected!"}); 
});

$(document).ready(function() {
  let canvas = document.getElementById("game-canvas");
  console.log(canvas);
  let gb = new GameBoard(canvas);
  gb.draw();
});
