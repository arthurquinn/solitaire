import Game from "./game"

$(document).ready(function() {
  let canvas = document.getElementById("game-canvas");
  canvas.width = 800;
  canvas.height = 600;
  let context2d = canvas.getContext("2d");
  context2d.imageSmoothingEnabled = false;
  let cardImages = new Image();
  cardImages.onload = function() {
    let socket = io.connect("http://" + document.domain + ":" + location.port, {'sync disconnect on unload': true});
    socket.on("connect", function() {
      let game = new Game(canvas, cardImages);
      socket.emit("command", {
        "cmd": "init"
      });
      socket.on("command_response", function(response) {
        if (response.response == "ok") {
          game.pushResponse(response);
        } else {
          console.error("bad command -- some kind of error to user, e.g. you cant do that move, guy")
        }
      });
      socket.on("disconnect", function() {
        socket.emit("disconnect");
      });
      game.run();
    });
  };
  cardImages.src = $("#spritesheet").attr("src");
});


