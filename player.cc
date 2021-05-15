#include "player.h"
#include <iostream>
#include <string>
#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image &screen) {
  int thick = 1;
  graphics::Color ufoGreen(61, 217, 93);
  graphics::Color ufoGrey(159, 158, 158);
  graphics::Color ufoWhite(
      0, 0, 0);  // made this black so you can see it against the background
  graphics::Color ufoBlue(21, 219, 176);
  graphics::Color ufoRed(169, 27, 27);

  // draws middle green in ufo
  screen.DrawLine(x_ + 16, y_ + 27, x_ + 30, y_ + 27, ufoGreen, thick);
  screen.SetColor(x_ + 22, y_ + 27, ufoRed);
  screen.SetColor(x_ + 24, y_ + 27, ufoRed);

  // draws the base white
  screen.DrawLine(x_ + 17, y_ + 28, x_ + 29, y_ + 28, ufoWhite, thick);
  screen.SetColor(x_ + 23, y_ + 28, ufoBlue);

  // draws the feet of ufo
  screen.SetColor(x_ + 19, y_ + 29, ufoWhite);
  screen.SetColor(x_ + 27, y_ + 29, ufoWhite);

  screen.SetColor(x_ + 17, y_ + 26, ufoGrey);
  screen.SetColor(x_ + 18, y_ + 25, ufoGrey);
  screen.SetColor(x_ + 19, y_ + 24, ufoGrey);
  screen.DrawLine(x_ + 20, y_ + 23, x_ + 26, y_ + 23, ufoGrey, thick);
  screen.SetColor(x_ + 27, y_ + 24, ufoGrey);
  screen.SetColor(x_ + 28, y_ + 25, ufoGrey);
  screen.SetColor(x_ + 29, y_ + 26, ufoGrey);
  screen.SetColor(x_ + 20, y_ + 24, ufoWhite);
  screen.SetColor(x_ + 19, y_ + 25, ufoWhite);
}

void PlayerProjectile::Draw(graphics::Image &screen) {
  int thick = 1;
  graphics::Color superGreen(139, 255, 0);
  screen.DrawLine(x_ + 2, y_ + 1, x_ + 2, y_ + 2, superGreen, thick);
}

void PlayerProjectile::Move(const graphics::Image &screen) {
  if (IsOutOfBounds(screen)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ - 3);
  }
}

void Player::Move(const graphics::Image &screen) {}
