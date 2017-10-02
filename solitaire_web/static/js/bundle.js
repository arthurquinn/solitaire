(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
"use strict";

var _game = require("./game");

var _game2 = _interopRequireDefault(_game);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

$(document).ready(function () {
  var canvas = document.getElementById("game-canvas");
  canvas.width = 800;
  canvas.height = 600;
  var context2d = canvas.getContext("2d");
  context2d.imageSmoothingEnabled = false;
  var cardImages = new Image();
  cardImages.onload = function () {
    var socket = io.connect("http://" + document.domain + ":" + location.port, { 'sync disconnect on unload': true });
    socket.on("connect", function () {
      var game = new _game2.default(canvas, cardImages);
      socket.emit("command", {
        "cmd": "init"
      });
      socket.on("command_response", function (response) {
        if (response.response == "ok") {
          game.pushResponse(response);
        } else {
          console.error("bad command -- some kind of error to user, e.g. you cant do that move, guy");
        }
      });
      socket.on("disconnect", function () {
        socket.emit("disconnect");
      });
      game.run();
    });
  };
  cardImages.src = $("#spritesheet").attr("src");
});

},{"./game":2}],2:[function(require,module,exports){
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _slicedToArray = function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; }();

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _toConsumableArray(arr) { if (Array.isArray(arr)) { for (var i = 0, arr2 = Array(arr.length); i < arr.length; i++) { arr2[i] = arr[i]; } return arr2; } else { return Array.from(arr); } }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var cardWidth = 53;
var cardHeight = 79.4;
var suitMap = { "s": 0, "h": 1, "d": 2, "c": 3, "x": 4 };
var rankMap = { "2": 0, "3": 1, "4": 2, "5": 3, "6": 4, "7": 5, "8": 6, "9": 7, "10": 8, "j": 9, "q": 10, "k": 11, "a": 12, "x": 1 };
var pilesWithOffset = [6, 7, 8, 9, 10, 11, 12];
var foundationBases = [[330, 20, 53, 79.4], [420, 20, 53, 79.4], [510, 20, 53, 79.4], [600, 20, 53, 79.4]];
var pileLocations = [[20, 20], [60, 20], [300, 20], [400, 20], [500, 20], [600, 20], [60, 200], [150, 200], [240, 200], [330, 200], [420, 200], [510, 200], [600, 200]];

function spritesheetLocation(cardStr) {
  var suit = cardStr.slice(0, 1);
  var rank = cardStr.slice(1, cardStr.length);
  return [rankMap[rank] * cardWidth, suitMap[suit] * cardHeight];
}

function drawRect(ctx, x, y, dx, dy) {
  ctx.beginPath();
  ctx.rect(x, y, dx, dy);
  ctx.fillStyle = 'transparent';
  ctx.fill();
  ctx.lineWidth = 2;
  ctx.strokeStyle = 'black';
  ctx.stroke();
}

var Game = function () {
  function Game(canvas, image) {
    _classCallCheck(this, Game);

    this.context2d = canvas.getContext("2d");
    this.image = image;
    this.cardLayout = [[], [], [], [], [], [], [], [], [], [], [], [], []];
    this.responses = [];
  }

  _createClass(Game, [{
    key: "pushResponse",
    value: function pushResponse(response) {
      this.responses.push(response);
    }
  }, {
    key: "run",
    value: function run() {
      this._loop();
    }
  }, {
    key: "_update",
    value: function _update() {
      if (this.responses.length > 0) {
        var response = this.responses.shift();
        var _iteratorNormalCompletion = true;
        var _didIteratorError = false;
        var _iteratorError = undefined;

        try {
          for (var _iterator = response.update[Symbol.iterator](), _step; !(_iteratorNormalCompletion = (_step = _iterator.next()).done); _iteratorNormalCompletion = true) {
            var _cardLayout$update$pi;

            var update = _step.value;

            for (var i = 0; i < update.pop; i++) {
              this.cardLayout[update.pile].pop();
            }
            (_cardLayout$update$pi = this.cardLayout[update.pile]).push.apply(_cardLayout$update$pi, _toConsumableArray(update.push));
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
    }
  }, {
    key: "_draw",
    value: function _draw() {
      var _this = this;

      this.context2d.clearRect(0, 0, 800, 600);
      var _iteratorNormalCompletion2 = true;
      var _didIteratorError2 = false;
      var _iteratorError2 = undefined;

      try {
        for (var _iterator2 = foundationBases[Symbol.iterator](), _step2; !(_iteratorNormalCompletion2 = (_step2 = _iterator2.next()).done); _iteratorNormalCompletion2 = true) {
          var foundation = _step2.value;

          var _foundation = _slicedToArray(foundation, 4),
              x = _foundation[0],
              y = _foundation[1],
              dx = _foundation[2],
              dy = _foundation[3];

          drawRect(this.context2d, x, y, dx, dy);
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

      var _loop2 = function _loop2(index, entry) {
        var shouldUpdate = pilesWithOffset.find(function (a) {
          return a === index;
        });
        var voffset = 0;
        var _iteratorNormalCompletion4 = true;
        var _didIteratorError4 = false;
        var _iteratorError4 = undefined;

        try {
          for (var _iterator4 = entry[Symbol.iterator](), _step4; !(_iteratorNormalCompletion4 = (_step4 = _iterator4.next()).done); _iteratorNormalCompletion4 = true) {
            var card = _step4.value;

            var _spritesheetLocation = spritesheetLocation(card),
                _spritesheetLocation2 = _slicedToArray(_spritesheetLocation, 2),
                sx = _spritesheetLocation2[0],
                sy = _spritesheetLocation2[1];

            var _pileLocations$index = _slicedToArray(pileLocations[index], 2),
                pileX = _pileLocations$index[0],
                pileY = _pileLocations$index[1];

            _this.context2d.drawImage(_this.image, sx, sy, cardWidth, cardHeight, pileX, pileY + voffset, cardWidth, cardHeight);
            if (shouldUpdate) {
              voffset += 20;
            }
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
      };

      var _iteratorNormalCompletion3 = true;
      var _didIteratorError3 = false;
      var _iteratorError3 = undefined;

      try {
        for (var _iterator3 = this.cardLayout.entries()[Symbol.iterator](), _step3; !(_iteratorNormalCompletion3 = (_step3 = _iterator3.next()).done); _iteratorNormalCompletion3 = true) {
          var _ref = _step3.value;

          var _ref2 = _slicedToArray(_ref, 2);

          var index = _ref2[0];
          var entry = _ref2[1];

          _loop2(index, entry);
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
    key: "_loop",
    value: function _loop() {
      var _this2 = this;

      window.requestAnimationFrame(function () {
        return _this2._loop();
      });
      this._update();
      this._draw();
    }
  }]);

  return Game;
}();

exports.default = Game;

},{}]},{},[1,2]);
