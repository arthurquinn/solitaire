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
          game.pushUpdate(response);
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

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _slicedToArray = function () { function sliceIterator(arr, i) { var _arr = []; var _n = true; var _d = false; var _e = undefined; try { for (var _i = arr[Symbol.iterator](), _s; !(_n = (_s = _i.next()).done); _n = true) { _arr.push(_s.value); if (i && _arr.length === i) break; } } catch (err) { _d = true; _e = err; } finally { try { if (!_n && _i["return"]) _i["return"](); } finally { if (_d) throw _e; } } return _arr; } return function (arr, i) { if (Array.isArray(arr)) { return arr; } else if (Symbol.iterator in Object(arr)) { return sliceIterator(arr, i); } else { throw new TypeError("Invalid attempt to destructure non-iterable instance"); } }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _toConsumableArray(arr) { if (Array.isArray(arr)) { for (var i = 0, arr2 = Array(arr.length); i < arr.length; i++) { arr2[i] = arr[i]; } return arr2; } else { return Array.from(arr); } }

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

var drawRect = function drawRect(ctx, x, y, dx, dy) {
  ctx.beginPath();
  ctx.rect(x, y, dx, dy);
  ctx.fillStyle = 'transparent';
  ctx.fill();
  ctx.lineWidth = 2;
  ctx.strokeStyle = 'black';
  ctx.stroke();
};

function draw(context2d, image, cardLayout) {
  context2d.clearRect(0, 0, 800, 600);
  var _iteratorNormalCompletion = true;
  var _didIteratorError = false;
  var _iteratorError = undefined;

  try {
    for (var _iterator = foundationBases[Symbol.iterator](), _step; !(_iteratorNormalCompletion = (_step = _iterator.next()).done); _iteratorNormalCompletion = true) {
      var foundation = _step.value;

      var _foundation = _slicedToArray(foundation, 4),
          x = _foundation[0],
          y = _foundation[1],
          dx = _foundation[2],
          dy = _foundation[3];

      drawRect(context2d, x, y, dx, dy);
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

  var _loop = function _loop(index, entry) {
    var shouldUpdate = pilesWithOffset.find(function (a) {
      return a === index;
    });
    var voffset = 0;
    var _iteratorNormalCompletion3 = true;
    var _didIteratorError3 = false;
    var _iteratorError3 = undefined;

    try {
      for (var _iterator3 = entry[Symbol.iterator](), _step3; !(_iteratorNormalCompletion3 = (_step3 = _iterator3.next()).done); _iteratorNormalCompletion3 = true) {
        var card = _step3.value;

        var _spritesheetLocation = spritesheetLocation(card),
            _spritesheetLocation2 = _slicedToArray(_spritesheetLocation, 2),
            sx = _spritesheetLocation2[0],
            sy = _spritesheetLocation2[1];

        var _pileLocations$index = _slicedToArray(pileLocations[index], 2),
            pileX = _pileLocations$index[0],
            pileY = _pileLocations$index[1];

        context2d.drawImage(image, sx, sy, cardWidth, cardHeight, pileX, pileY + voffset, cardWidth, cardHeight);
        if (shouldUpdate) {
          voffset += 20;
        }
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
  };

  var _iteratorNormalCompletion2 = true;
  var _didIteratorError2 = false;
  var _iteratorError2 = undefined;

  try {
    for (var _iterator2 = cardLayout.entries()[Symbol.iterator](), _step2; !(_iteratorNormalCompletion2 = (_step2 = _iterator2.next()).done); _iteratorNormalCompletion2 = true) {
      var _ref = _step2.value;

      var _ref2 = _slicedToArray(_ref, 2);

      var index = _ref2[0];
      var entry = _ref2[1];

      _loop(index, entry);
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

function update(layout, response) {
  var _iteratorNormalCompletion4 = true;
  var _didIteratorError4 = false;
  var _iteratorError4 = undefined;

  try {
    for (var _iterator4 = response.update[Symbol.iterator](), _step4; !(_iteratorNormalCompletion4 = (_step4 = _iterator4.next()).done); _iteratorNormalCompletion4 = true) {
      var _layout$_update$pile;

      var _update = _step4.value;

      for (var i = 0; i < _update.pop; i++) {
        layout[_update.pile].pop();
      }
      (_layout$_update$pile = layout[_update.pile]).push.apply(_layout$_update$pile, _toConsumableArray(_update.push));
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

var Game = function () {
  function Game(canvas, image) {
    _classCallCheck(this, Game);

    this.context2d = canvas.getContext("2d");
    this.image = image;
    this.cardLayout = [[], [], [], [], [], [], [], [], [], [], [], [], []];
    this.updates = [];
  }

  _createClass(Game, [{
    key: "pushUpdate",
    value: function pushUpdate(update) {
      this.updates.push(update);
    }
  }, {
    key: "run",
    value: function run() {
      var _this = this;

      // const fps = 30;
      // let bX = 30;
      // let bY = 30;
      // let mX = 150;
      // let mY = 300;
      // let lastTime = (new Date()).getTime();
      // let currentTime = 0;
      // let delta = 0;

      var gameLoop = function gameLoop() {
        window.requestAnimationFrame(gameLoop);

        if (_this.updates.length > 0) {
          update(_this.cardLayout, _this.updates.shift());
        }
        draw(_this.context2d, _this.image, _this.cardLayout);
        // currentTime = (new Date()).getTime();
        // delta = (currentTime - lastTime) / 1000;
        // context2d.clearRect(0, 0, canvas.width, canvas.height);

        // context2d.beginPath();
        // context2d.fillStyle = 'red';
        // context2d.arc(bX, bY, 20, 0, Math.PI * 360);
        // context2d.fill();
        // if (bX >= cw || bX <= 0) {
        //     mX *= -1;
        // }
        // if (bY >= ch || bY <= 0) {
        //     mY *= -1;
        // }

        // bX += (mX * delta);
        // bY += (mY * delta);

        // lastTime = currentTime;
      };
      gameLoop();
    }
  }]);

  return Game;
}();

exports.default = Game;

},{}]},{},[1,2]);
