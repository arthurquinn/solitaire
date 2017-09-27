export default class GameBoard {
  constructor(canvas) {
    this.canvas = canvas;
    this.ctx2d = canvas.getContext("2d");
  }
  draw() {
    let img = new Image();
    img.onload = () => {
      this.ctx2d.drawImage(img, 0, 0);
    }
    img.src = $("#spritesheet").attr("src");
  }
}
