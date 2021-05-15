#include "game_element.h"

bool GameElement::IntersectsWith(GameElement *gameCopy) {
  if (GetX() < (*gameCopy).GetX() + (*gameCopy).GetWidth()) {
    if ((*gameCopy).GetX() < GetX() + GetWidth()) {
      if (GetY() < (*gameCopy).GetY() + (*gameCopy).GetWidth()) {
        if ((*gameCopy).GetY() < GetY() + GetHeight()) {
          return true;
        }
      }
    }
  }
  return false;
}

bool GameElement::IsOutOfBounds(const graphics::Image &screen) {
  if (x_ < 0) {
    return true;
  } else if ((x_ + width_) > screen.GetWidth()) {
    return true;
  } else if (y_ < 0) {
    return true;
  } else if ((y_ + height_) > screen.GetHeight()) {
    return true;
  }
  return false;
}

