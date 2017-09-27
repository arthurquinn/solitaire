import CardSprite from './card_sprite'

var socket = io.connect("http://" + document.domain + ":" + location.port);
socket.on("connect", function() {
  socket.emit("my event", {data: "I\'m connected!"}); 
});

$(document).ready(function() {
  let canvas = document.getElementById("game-canvas");
  console.log(canvas);
  let sprite = new CardSprite(canvas, 0, 0);
  sprite.draw();
});
