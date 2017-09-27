import CardSprite from './card_sprite'

export default class Board {
  constructor(canvas) {
    this.canvas = canvas;
    this.cardLayout = [
      ["h10"], [], [], [], [], [], [], [], [], [], [], [], []
    ];
  }
  push(key, val) {
    this.cardLayout[key].push(val);
  }
  pop(key, num) {
    let a = this.cardLayout[key];
    a = a.slice(0, a.length - num);
  }
  draw() {
    for (let pile of this.cardLayout) {
      for (let card of pile) {
        let cs = new CardSprite(this.canvas, card);
        cs.draw();
      }
    }
  }
}