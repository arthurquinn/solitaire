import CardSprite from './card_sprite'

const suitMap = { "s": 0, "h": 1, "d": 2, "c": 3 };
const rankMap = { "2": 0, "3": 1, "4": 2, "5": 3, "6": 4, "7": 5, "8": 6, "9": 7, "10": 8, "j": 9, "q": 10, "k": 11, "a": 12 };

export default class Board {
  constructor(canvas) {
    this.canvas = canvas;
    this.cards = {};
    for (let suit of Object.keys(suitMap)) {
      for (let rank of Object.keys(rankMap)) {
        let cardStr = suit + rank;
        this.cards[cardStr] = new CardSprite(this.canvas, suitMap[suit], rankMap[rank]);
      }
    }
    this.cardLayout = {
      0: [],
      1: [],
      2: [],
      3: [],
      4: [],
      5: [],
      6: [],
      7: [],
      8: [],
      9: [],
      10: [],
      11: [],
      12: []
    };
  }
  draw() {
    for (let i of Object.keys(this.cardLayout)) {
      for (let card of this.cardLayout[i]) {
        console.log(card, i);
        this.cards[card].draw(i);
      }
    }
  }
}