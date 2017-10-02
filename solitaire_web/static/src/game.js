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

function spritesheetLocation(cardStr) {
  const suit = cardStr.slice(0, 1);
  const rank = cardStr.slice(1, cardStr.length);
  return [ rankMap[rank] * cardWidth, suitMap[suit] * cardHeight ];
}

function drawRect(ctx, x, y, dx, dy) {
  ctx.beginPath();
  ctx.rect(x, y, dx, dy);
  ctx.fillStyle = 'transparent';
  ctx.fill();
  ctx.lineWidth = 2;
  ctx.strokeStyle = 'black';
  ctx.stroke();
}

function coordIn(coord, rect) {
  const [ x, y ] = coord;
  const [ rx, ry, rdx, rdy ] = rect;
  return rx - x < 0 && rx + rdx - x > 0 && 
         ry - y < 0 && ry + rdy - y > 0;
}

function cardAtCoords(layout, x, y) {
  if (coordIn([x, y], pileLocations[0].concat([cardWidth, cardHeight]))) {
    return "deck";
  }
}

export default class Game {

  constructor(canvas, image, sendCmd) {
    this.canvas = canvas;
    this.context2d = canvas.getContext("2d");
    this.image = image;
    this.sendCmd = sendCmd;
    this.cardLayout = [ [], [], [], [], [], [], [], [], [], [], [], [], [] ];
    this.responses = [];
    this.commands = [];

    this.canvas.addEventListener("mousedown", e => this._mousedown(e), false);
    this.canvas.addEventListener("mouseup", e => this._mouseup(e), false);
  }

  pushResponse(response) {
    this.responses.push(response);
  }
  
  run() {
    this._loop();
  }

  _mousedown(e) {
    console.log("drag start: ", e.offsetX, e.offsetY);
    const card = cardAtCoords(this.cardLayout, e.offsetX, e.offsetY);
    if (card) {
      switch (card) {
      case "deck":
        this.commands.push({
          cmd: "draw"
        });
      }
    }
  }

  _mouseup(e) {
    console.log("drag end: ", e.offsetX, e.offsetY);
  }

  _update() {
    if (this.responses.length > 0) {
      const response = this.responses.shift();
      for (const update of response.update) {
        for (let i = 0; i < update.pop; i++) {
          this.cardLayout[update.pile].pop();
        }
        this.cardLayout[update.pile].push(...update.push);
      }
    }
    if (this.commands.length > 0) {
      this.sendCmd(this.commands.shift());
    }
  }

  _draw() {
    this.context2d.clearRect(0, 0, 800, 600);
    for (const foundation of foundationBases) {
      const [ x, y, dx, dy ] = foundation;
      drawRect(this.context2d, x, y, dx, dy);
    }
    for (const [ index, entry ] of this.cardLayout.entries()) {
      const shouldUpdate = pilesWithOffset.find(a => a === index);
      let voffset = 0;
      for (const card of entry) {
        const [ sx, sy ] = spritesheetLocation(card);
        const [ pileX, pileY ] = pileLocations[index];
        this.context2d.drawImage(
          this.image,
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

  _loop() {
    window.requestAnimationFrame(() => this._loop());
    this._update();
    this._draw();
  }
}