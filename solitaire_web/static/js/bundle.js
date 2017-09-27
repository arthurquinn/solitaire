(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
"use strict";

var _game_board = require("./game_board");

var _game_board2 = _interopRequireDefault(_game_board);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var socket = io.connect("http://" + document.domain + ":" + location.port);
socket.on("connect", function () {
  socket.emit("my event", { data: "I\'m connected!" });
});

$(document).ready(function () {
  var canvas = document.getElementById("game-canvas");
  console.log(canvas);
  var gb = new _game_board2.default(canvas);
  gb.draw();
});

},{"./game_board":2}],2:[function(require,module,exports){
"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var GameBoard = function () {
  function GameBoard(canvas) {
    _classCallCheck(this, GameBoard);

    this.canvas = canvas;
    this.ctx2d = canvas.getContext("2d");
  }

  _createClass(GameBoard, [{
    key: "draw",
    value: function draw() {
      var _this = this;

      var img = new Image();
      img.onload = function () {
        _this.ctx2d.drawImage(img, 0, 0);
      };
      img.src = $("#spritesheet").attr("src");
    }
  }]);

  return GameBoard;
}();

exports.default = GameBoard;

},{}]},{},[1,2]);
