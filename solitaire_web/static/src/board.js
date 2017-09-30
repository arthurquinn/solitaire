import CardSprite from './card_sprite'

const suitMap = { "s": 0, "h": 1, "d": 2, "c": 3 };
const rankMap = { "2": 0, "3": 1, "4": 2, "5": 3, "6": 4, "7": 5, "8": 6, "9": 7, "10": 8, "j": 9, "q": 10, "k": 11, "a": 12 };

const pilesWithOffset = [ 6, 7, 8, 9, 10, 11, 12 ]

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
    this.cards["xx"] = new CardSprite(this.canvas, 4, 1);
    this.cardLayout = [ [], [], [], [], [], [], [], [], [], [], [], [], [] ];
  }
  update(pile, ...cards) {
    // Do pops here
    for (let card of cards) {
      this.cardLayout[pile].push(card);
    }
  }
  draw() {
    for (let [ index, value ] of this.cardLayout.entries()) {
      let vertOffset = 0;
      let shouldOffset = pilesWithOffset.find(a => a === index);
      for (let card of this.cardLayout[index]) {
        this.cards[card].draw(index, vertOffset);
        if (shouldOffset) {
          vertOffset += 10;
        }
      }
    }
  }
}