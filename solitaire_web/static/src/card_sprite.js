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
    this.dScaleX = 1;
    this.dScaleY = 1;
    this.dWidth = this.sWidth * this.dScaleX;
    this.dHeight = this.sHeight * this.dScaleY;
  }
  draw(pile, vertOffset) {
    let [ pileX, pileY ] = pileLocations[pile];
    let img = new Image();
    img.onload = () => {
      this.ctx2d.imageSmoothingEnabled = false;
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
