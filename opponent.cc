#include "opponent.h"
#include <iostream>

void Opponent::Draw(graphics::Image &screen) {
  int thick = 1;
  graphics::Color oppCyan(118, 255, 231);
  graphics::Color oppBlue(2, 153, 253);
  graphics::Color oppLtBlue(81, 240, 255);
  graphics::Color oppGreen(192, 247, 178);

  screen.DrawLine(x_ + 22, y_ + 24, x_ + 22, y_ + 26, oppBlue, thick);
  screen.DrawLine(x_ + 23, y_ + 23, x_ + 25, y_ + 23, oppBlue, thick);
  screen.DrawLine(x_ + 26, y_ + 24, x_ + 26, y_ + 26, oppBlue, thick);
  screen.DrawLine(x_ + 23, y_ + 27, x_ + 25, y_ + 27, oppBlue, thick);

  screen.SetColor(x_ + 21, y_ + 25, oppCyan);
  screen.SetColor(x_ + 24, y_ + 22, oppCyan);
  screen.SetColor(x_ + 27, y_ + 25, oppCyan);
  screen.SetColor(x_ + 24, y_ + 28, oppCyan);

  screen.SetColor(x_ + 24, y_ + 24, oppLtBlue);
  screen.SetColor(x_ + 23, y_ + 25, oppLtBlue);
  screen.SetColor(x_ + 24, y_ + 26, oppLtBlue);
  screen.SetColor(x_ + 25, y_ + 25, oppLtBlue);

  screen.SetColor(x_ + 23, y_ + 24, oppGreen);
  screen.SetColor(x_ + 25, y_ + 24, oppGreen);
  screen.SetColor(x_ + 24, y_ + 25, oppGreen);
  screen.SetColor(x_ + 23, y_ + 26, oppGreen);
  screen.SetColor(x_ + 25, y_ + 26, oppGreen);
}

void OpponentProjectile::Draw(graphics::Image &screen) {
  int thick = 1;
  graphics::Color oppRed(255, 79, 79);
  screen.SetColor(x_ + 2, y_ + 0, oppRed);
  screen.SetColor(x_ + 2, y_ + 2, oppRed);
  screen.SetColor(x_ + 2, y_ + 4, oppRed);
}

void Opponent::Move(const graphics::Image &screen) {
  if (IsOutOfBounds(screen)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ + 1);
  }
}

void OpponentProjectile::Move(const graphics::Image &screen) {
  if (IsOutOfBounds(screen)) {
    is_active = false;
  } else {
    SetX(x_ + 1);
    SetY(y_ + 2);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  oppProjCount = oppProjCount + 1;
  if (oppProjCount % 10 == 0) {
    std::unique_ptr<OpponentProjectile> resetOppProj =
        std::make_unique<OpponentProjectile>(GetX(), GetY());
    return std::move(resetOppProj);
  } else {
    return nullptr;
  }
}
