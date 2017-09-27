const cardSpriteIndex = function(card) {
  var s, r;
  let suit = card.charAt(0);
  let rank = card.slice(1, card.length);
  switch (suit) {
    case "h":
      s = 1;
      break;
    case "d":
      s = 2;
      break;
    case "c":
      s = 3;
      break;
    case "s": 
      s = 0;
      break;
  }
  if (!isNaN(rank)) {
    r = Number(rank) - 2;
  } else {
    switch (rank) {
      case "j": 
        r = 9;
        break;
      case "q": 
        r = 10;
        break;
      case "k": 
        r = 11;
        break;
      case "a": 
        r = 12;
        break;
    }
  }
  console.log(s, r, suit, rank);
  return [s, r];
}

export default class CardSprite {
  constructor(canvas, card) {
    this.canvas = canvas;
    this.card = card;
    [this.row, this.col] = cardSpriteIndex(card);
    this.ctx2d = canvas.getContext("2d");
    this.sWidth = 53;
    this.sHeight = 79.4;
    this.sx = this.sWidth * this.col;
    this.sy = this.sHeight * this.row;
    this.dScaleX = 0.67;
    this.dScaleY = 0.43;
    this.dWidth = this.sWidth * this.dScaleX;
    this.dHeight = this.sHeight * this.dScaleY;
  }
  draw() {
    let img = new Image();
    img.onload = () => {
      console.log("sx: " + this.sx);
      console.log("sy: " + this.sy);
      console.log("sWidth: " + this.sWidth);
      console.log("sHeight: " + this.sHeight);
      this.ctx2d.drawImage(
        img,
        this.sx,
        this.sy,
        this.sWidth,
        this.sHeight,
        0,
        0,
        this.dWidth,
        this.dHeight);
    }
    img.src = $("#spritesheet").attr("src");
  }
}
