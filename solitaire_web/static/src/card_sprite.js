const pileLocations = [
  [ 10, 3 ],
  [ 10, 0 ],
  [ 40, 0 ],
  [ 50, 0 ],
  [ 60, 0 ],
  [ 70, 0 ],
  [ 10, 40 ],
  [ 50, 40 ],
  [ 90, 40 ],
  [ 130, 40 ],
  [ 170, 40 ],
  [ 210, 40 ],
  [ 250, 40 ]
];

export default class CardSprite {
  constructor(canvas, suit, rank) {
    this.canvas = canvas;
    this.row = suit;
    this.col = rank;
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
  draw(pile, vertOffset) {
    let [ pileX, pileY ] = pileLocations[pile];
    let img = new Image();
    img.onload = () => {
      this.ctx2d.drawImage(
        img,
        this.sx,
        this.sy,
        this.sWidth,
        this.sHeight,
        pileX,
        pileY + vertOffset,
        this.dWidth,
        this.dHeight);
    }
    img.src = $("#spritesheet").attr("src");
  }
}
