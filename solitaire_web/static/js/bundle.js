(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
"use strict";

var _board = require("./board");

var _board2 = _interopRequireDefault(_board);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var socket = io.connect("http://" + document.domain + ":" + location.port);
socket.on("connect", function () {
  socket.emit("my event", { data: "I\'m connected!" });
});

$(document).ready(function () {
  var canvas = document.getElementById("game-canvas");
  console.log(canvas);
  var board = new _board2.default(canvas);
  board.draw();
});

},{"./board":2}],2:[function(require,module,exports){
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _card_sprite = require("./card_sprite");

var _card_sprite2 = _interopRequireDefault(_card_sprite);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var Board = function () {
  function Board(canvas) {
    _classCallCheck(this, Board);

    this.canvas = canvas;
    this.cardLayout = [["h10"], [], [], [], [], [], [], [], [], [], [], [], []];
  }

  _createClass(Board, [{
    key: "push",
    value: function push(key, val) {
      this.cardLayout[key].push(val);
    }
  }, {
    key: "pop",
    value: function pop(key, num) {
      var a = this.cardLayout[key];
      a = a.slice(0, a.length - num);
    }
  }, {
    key: "draw",
    value: function draw() {
      var _iteratorNormalCompletion = true;
      var _didIteratorError = false;
      var _iteratorError = undefined;

      try {
        for (var _iterator = this.cardLayout[Symbol.iterator](), _step; !(_iteratorNormalCompletion = (_step = _iterator.next()).done); _iteratorNormalCompletion = true) {
          var pile = _step.value;
          var _iteratorNormalCompletion2 = true;
          var _didIteratorError2 = false;
          var _iteratorError2 = undefined;

          try {
            for (var _iterator2 = pile[Symbol.iterator](), _step2; !(_iteratorNormalCompletion2 = (_step2 = _iterator2.next()).done); _iteratorNormalCompletion2 = true) {
              var card = _step2.value;

              var cs = new _card_sprite2.default(this.canvas, card);
              cs.draw();
            }
          } catch (err) {
            _didIteratorError2 = true;
            _iteratorError2 = err;
          } finally {
            try {
              if (!_iteratorNormalCompletion2 && _iterator2.return) {
                _iterator2.return();
              }
            } finally {
              if (_didIteratorError2) {
                throw _iteratorError2;
              }
            }
          }
        }
      } catch (err) {
        _didIteratorError = true;
        _iteratorError = err;
      } finally {
        try {
          if (!_iteratorNormalCompletion && _iterator.return) {
            _iterator.return();
          }
        } finally {
          if (_didIteratorError) {
            throw _iteratorError;
          }
        }
      }
    }
  }]);

  return Board;
}();

exports.default = Board;

},{"./card_sprite":3}],3:[function(require,module,exports){
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _slicedToArray = function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; }();

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var cardSpriteIndex = function cardSpriteIndex(card) {
  var s, r;
  var suit = card.charAt(0);
  var rank = card.slice(1, card.length);
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
};

var CardSprite = function () {
  function CardSprite(canvas, card) {
    _classCallCheck(this, CardSprite);

    this.canvas = canvas;
    this.card = card;

    var _cardSpriteIndex = cardSpriteIndex(card);

    var _cardSpriteIndex2 = _slicedToArray(_cardSpriteIndex, 2);

    this.row = _cardSpriteIndex2[0];
    this.col = _cardSpriteIndex2[1];

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

  _createClass(CardSprite, [{
    key: "draw",
    value: function draw() {
      var _this = this;

      var img = new Image();
      img.onload = function () {
        console.log("sx: " + _this.sx);
        console.log("sy: " + _this.sy);
        console.log("sWidth: " + _this.sWidth);
        console.log("sHeight: " + _this.sHeight);
        _this.ctx2d.drawImage(img, _this.sx, _this.sy, _this.sWidth, _this.sHeight, 0, 0, _this.dWidth, _this.dHeight);
      };
      img.src = $("#spritesheet").attr("src");
    }
  }]);

  return CardSprite;
}();

exports.default = CardSprite;

},{}]},{},[1,2,3]);
