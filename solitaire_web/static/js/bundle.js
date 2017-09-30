(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
"use strict";

var _board = require("./board");

var _board2 = _interopRequireDefault(_board);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _toConsumableArray(arr) { if (Array.isArray(arr)) { for (var i = 0, arr2 = Array(arr.length); i < arr.length; i++) { arr2[i] = arr[i]; } return arr2; } else { return Array.from(arr); } }

$(document).ready(function () {
  var canvas = document.getElementById("game-canvas");
  var board = new _board2.default(canvas);
  var socket = io.connect("http://" + document.domain + ":" + location.port);
  socket.on("connect", function () {
    socket.emit("command", {
      "cmd": "init"
    });
    socket.on("command_response", function (response) {
      console.log("command_response received");
      if (response.response == "ok") {
        var _iteratorNormalCompletion = true;
        var _didIteratorError = false;
        var _iteratorError = undefined;

        try {
          for (var _iterator = response.update[Symbol.iterator](), _step; !(_iteratorNormalCompletion = (_step = _iterator.next()).done); _iteratorNormalCompletion = true) {
            var update = _step.value;

            board.update.apply(board, [update.pile].concat(_toConsumableArray(update.push)));
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

        board.draw();
      } else {
        console.error("bad command -- some kind of error to user, e.g. you cant do that move, guy");
      }
    });
  });
  // setInterval(function() {
  //   board.draw();
  // }, 1000);
});

},{"./board":2}],2:[function(require,module,exports){
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _slicedToArray = function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; }();

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _card_sprite = require("./card_sprite");

var _card_sprite2 = _interopRequireDefault(_card_sprite);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var suitMap = { "s": 0, "h": 1, "d": 2, "c": 3 };
var rankMap = { "2": 0, "3": 1, "4": 2, "5": 3, "6": 4, "7": 5, "8": 6, "9": 7, "10": 8, "j": 9, "q": 10, "k": 11, "a": 12 };

var pilesWithOffset = [6, 7, 8, 9, 10, 11, 12];

var Board = function () {
  function Board(canvas) {
    _classCallCheck(this, Board);

    this.canvas = canvas;
    this.cards = {};
    var _iteratorNormalCompletion = true;
    var _didIteratorError = false;
    var _iteratorError = undefined;

    try {
      for (var _iterator = Object.keys(suitMap)[Symbol.iterator](), _step; !(_iteratorNormalCompletion = (_step = _iterator.next()).done); _iteratorNormalCompletion = true) {
        var suit = _step.value;
        var _iteratorNormalCompletion2 = true;
        var _didIteratorError2 = false;
        var _iteratorError2 = undefined;

        try {
          for (var _iterator2 = Object.keys(rankMap)[Symbol.iterator](), _step2; !(_iteratorNormalCompletion2 = (_step2 = _iterator2.next()).done); _iteratorNormalCompletion2 = true) {
            var rank = _step2.value;

            var cardStr = suit + rank;
            this.cards[cardStr] = new _card_sprite2.default(this.canvas, suitMap[suit], rankMap[rank]);
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

    this.cards["xx"] = new _card_sprite2.default(this.canvas, 4, 1);
    this.cardLayout = [[], [], [], [], [], [], [], [], [], [], [], [], []];
  }

  _createClass(Board, [{
    key: "update",
    value: function update(pile) {
      for (var _len = arguments.length, cards = Array(_len > 1 ? _len - 1 : 0), _key = 1; _key < _len; _key++) {
        cards[_key - 1] = arguments[_key];
      }

      // Do pops here
      var _iteratorNormalCompletion3 = true;
      var _didIteratorError3 = false;
      var _iteratorError3 = undefined;

      try {
        for (var _iterator3 = cards[Symbol.iterator](), _step3; !(_iteratorNormalCompletion3 = (_step3 = _iterator3.next()).done); _iteratorNormalCompletion3 = true) {
          var card = _step3.value;

          this.cardLayout[pile].push(card);
        }
      } catch (err) {
        _didIteratorError3 = true;
        _iteratorError3 = err;
      } finally {
        try {
          if (!_iteratorNormalCompletion3 && _iterator3.return) {
            _iterator3.return();
          }
        } finally {
          if (_didIteratorError3) {
            throw _iteratorError3;
          }
        }
      }
    }
  }, {
    key: "draw",
    value: function draw() {
      var _this = this;

      var _loop = function _loop(index, value) {
        var vertOffset = 0;
        var shouldOffset = pilesWithOffset.find(function (a) {
          return a === index;
        });
        var _iteratorNormalCompletion5 = true;
        var _didIteratorError5 = false;
        var _iteratorError5 = undefined;

        try {
          for (var _iterator5 = _this.cardLayout[index][Symbol.iterator](), _step5; !(_iteratorNormalCompletion5 = (_step5 = _iterator5.next()).done); _iteratorNormalCompletion5 = true) {
            var card = _step5.value;

            _this.cards[card].draw(index, vertOffset);
            if (shouldOffset) {
              vertOffset += 10;
            }
          }
        } catch (err) {
          _didIteratorError5 = true;
          _iteratorError5 = err;
        } finally {
          try {
            if (!_iteratorNormalCompletion5 && _iterator5.return) {
              _iterator5.return();
            }
          } finally {
            if (_didIteratorError5) {
              throw _iteratorError5;
            }
          }
        }
      };

      var _iteratorNormalCompletion4 = true;
      var _didIteratorError4 = false;
      var _iteratorError4 = undefined;

      try {
        for (var _iterator4 = this.cardLayout.entries()[Symbol.iterator](), _step4; !(_iteratorNormalCompletion4 = (_step4 = _iterator4.next()).done); _iteratorNormalCompletion4 = true) {
          var _ref = _step4.value;

          var _ref2 = _slicedToArray(_ref, 2);

          var index = _ref2[0];
          var value = _ref2[1];

          _loop(index, value);
        }
      } catch (err) {
        _didIteratorError4 = true;
        _iteratorError4 = err;
      } finally {
        try {
          if (!_iteratorNormalCompletion4 && _iterator4.return) {
            _iterator4.return();
          }
        } finally {
          if (_didIteratorError4) {
            throw _iteratorError4;
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

var pileLocations = [[10, 3], [10, 0], [40, 0], [50, 0], [60, 0], [70, 0], [10, 40], [50, 40], [90, 40], [130, 40], [170, 40], [210, 40], [250, 40]];

var CardSprite = function () {
  function CardSprite(canvas, suit, rank) {
    _classCallCheck(this, CardSprite);

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

  _createClass(CardSprite, [{
    key: "draw",
    value: function draw(pile, vertOffset) {
      var _this = this;

      var _pileLocations$pile = _slicedToArray(pileLocations[pile], 2),
          pileX = _pileLocations$pile[0],
          pileY = _pileLocations$pile[1];

      var img = new Image();
      img.onload = function () {
        _this.ctx2d.drawImage(img, _this.sx, _this.sy, _this.sWidth, _this.sHeight, pileX, pileY + vertOffset, _this.dWidth, _this.dHeight);
      };
      img.src = $("#spritesheet").attr("src");
    }
  }]);

  return CardSprite;
}();

exports.default = CardSprite;

},{}]},{},[1,2,3]);
