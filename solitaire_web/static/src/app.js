const cardWidth = 53;
const cardHeight = 79.4;
const suitMap = { "s": 0, "h": 1, "d": 2, "c": 3, "x": 4 };
const rankMap = { "2": 0, "3": 1, "4": 2, "5": 3, "6": 4, "7": 5, "8": 6, "9": 7, "10": 8, "j": 9, "q": 10, "k": 11, "a": 12, "x": 1 };
const pilesWithOffset = [ 6, 7, 8, 9, 10, 11, 12 ];
const foundationBases = [ [330, 20, 53, 79.4], [420, 20, 53, 79.4], [510, 20, 53, 79.4], [600, 20, 53, 79.4] ];
const pileLocations = [
  [ 20, 20 ],
  [ 60, 20 ],
  [ 300, 20 ],
  [ 400, 20 ],
  [ 500, 20 ],
  [ 600, 20 ],
  [ 60, 200 ],
  [ 150, 200 ],
  [ 240, 200 ],
  [ 330, 200 ],
  [ 420, 200 ],
  [ 510, 200 ],
  [ 600, 200 ]
];

let cardLayout = [ [], [], [], [], [], [], [], [], [], [], [], [], [] ];

function spritesheetLocation(cardStr) {
  const suit = cardStr.slice(0, 1);
  const rank = cardStr.slice(1, cardStr.length);
  return [ rankMap[rank] * cardWidth, suitMap[suit] * cardHeight ];
}

const drawRect = function(ctx, x, y, dx, dy) {
  ctx.beginPath();
  ctx.rect(x, y, dx, dy);
  ctx.fillStyle = 'transparent';
  ctx.fill();
  ctx.lineWidth = 2;
  ctx.strokeStyle = 'black';
  ctx.stroke();
}

function drawLayout(context2d, image) {
  context2d.clearRect(0, 0, 800, 600);
  for (const foundation of foundationBases) {
    const [ x, y, dx, dy ] = foundation;
    drawRect(context2d, x, y, dx, dy);
  }
  for (const [ index, entry ] of cardLayout.entries()) {
    const shouldUpdate = pilesWithOffset.find(a => a === index);
    let voffset = 0;
    for (const card of entry) {
      const [ sx, sy ] = spritesheetLocation(card);
      const [ pileX, pileY ] = pileLocations[index];
      context2d.drawImage(
        image,
        sx,
        sy,
        cardWidth,
        cardHeight,
        pileX,
        pileY + voffset,
        cardWidth,
        cardHeight);
      if (shouldUpdate) {
        voffset += 20;
      }
    }
  }
}

function updateLayout(response) {
  for (const update of response.update) {
    for (let i = 0; i < update.pop; i++) {
      cardLayout[update.pile].pop();
    }
    cardLayout[update.pile].push(...update.push);
  }
}

function startGameLoop(canvas, cardImages) {
  const context2d = canvas.getContext("2d");
  // const fps = 30;
  // let bX = 30;
  // let bY = 30;
  // let mX = 150;
  // let mY = 300;
  // let lastTime = (new Date()).getTime();
  // let currentTime = 0;
  // let delta = 0;

  const gameLoop = function() {
    window.requestAnimationFrame(gameLoop);
  
    drawLayout(context2d, cardImages);
    // currentTime = (new Date()).getTime();
    // delta = (currentTime - lastTime) / 1000;
    // context2d.clearRect(0, 0, canvas.width, canvas.height);
  
    // context2d.beginPath();
    // context2d.fillStyle = 'red';
    // context2d.arc(bX, bY, 20, 0, Math.PI * 360);
    // context2d.fill();
    // if (bX >= cw || bX <= 0) {
    //     mX *= -1;
    // }
    // if (bY >= ch || bY <= 0) {
    //     mY *= -1;
    // }
  
    // bX += (mX * delta);
    // bY += (mY * delta);
  
    // lastTime = currentTime;
  };
  gameLoop();
}

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
      socket.emit("command", {
        "cmd": "init"
      });
      socket.on("command_response", function(response) {
        if (response.response == "ok") {
          updateLayout(response);
        } else {
          console.error("bad command -- some kind of error to user, e.g. you cant do that move, guy")
        }
        startGameLoop(canvas, cardImages);
      });
      socket.on("disconnect", function() {
        socket.emit("disconnect");
      });
    });
  };
  cardImages.src = $("#spritesheet").attr("src");
});

