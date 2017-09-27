export default class CardSprite {
  constructor(canvas, row, col) {
    this.canvas = canvas;
    this.ctx2d = canvas.getContext("2d");
    this.sWidth = 53;
    this.sHeight = 79.4;
    this.sx = this.sWidth * col;
    this.sy = this.sHeight * row;
    this.dScaleX = 0.67;
    this.dScaleY = 0.43;
    this.dWidth = this.sWidth * this.dScaleX;
    this.dHeight = this.sHeight * this.dScaleY;
  }
  draw() {
    let img = new Image();
    img.onload = () => {
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
