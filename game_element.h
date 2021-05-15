#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
#include <memory>
#include <string>
#include "cpputils/graphics/image.h"
class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  bool GetIsActive() const { return is_active; }
  void SetIsActive(bool active) { is_active = active; }
  int GetX() const { return x_; }
  void SetX(int const &x) { x_ = x; }
  int GetY() const { return y_; }
  void SetY(int const &y) { y_ = y; }

  virtual void Draw(graphics::Image &screen) = 0;
  virtual void Move(const graphics::Image &screen) = 0;
  bool IntersectsWith(GameElement *gameCopy);
  bool IsOutOfBounds(const graphics::Image &screen);

 protected:
  int width_;
  int height_;
  int x_;
  int y_;
  bool is_active = true;
};
#endif
