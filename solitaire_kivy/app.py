from kivy.app import App
from kivy.graphics.context_instructions import Color
from kivy.uix.floatlayout import FloatLayout
from kivy.config import Config
from kivy.uix.widget import Widget

Config.set('graphics', 'width', '800')
Config.set('graphics', 'height', '500')


class Card(Widget):
  def on_touch_move(self, touch):
    self.center_x = touch.x
    self.center_y = touch.y


class SolitaireGame(Widget):
  pass


class SolitaireApp(App):
  def build(self):
    game = SolitaireGame()
    with game.canvas.before:
      Color(0, 1, 0, 1)
    return game


if __name__ == '__main__':
  SolitaireApp().run()
