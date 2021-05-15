#include "game.h"
#include <string>

void Game::OnMouseEvent(const graphics::MouseEvent &mouseEvent) {
  if (mouseEvent.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
    int currentX = myPlayer.GetX();
    int currentY = myPlayer.GetY();
    int newX = mouseEvent.GetX() - myPlayer.GetWidth() * (0.5);
    int newY = mouseEvent.GetY() - myPlayer.GetHeight() * (0.5);
    myPlayer.SetX(newX);
    myPlayer.SetY(newY);

    if (myPlayer.IsOutOfBounds(screen)) {
      myPlayer.SetX(currentX);
      myPlayer.SetY(currentY);
    }
  }
  if (mouseEvent.GetMouseAction() == graphics::MouseAction::kDragged ||
      mouseEvent.GetMouseAction() == graphics::MouseAction::kPressed) {
    int newX = mouseEvent.GetX() - myPlayer.GetWidth() * (0.5);
    int newY = mouseEvent.GetY() - myPlayer.GetHeight() * (0.5);
    std::unique_ptr<PlayerProjectile> myPlayer_ptr =
        std::make_unique<PlayerProjectile>(newX, newY);
    playerProjectiles.push_back(std::move(myPlayer_ptr));
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_.size(); i++) {
      if ((*opponent_[i]).GetIsActive() && myPlayer.GetIsActive() && myPlayer.IntersectsWith(opponent_[i].get())) {
        (*opponent_[i]).SetIsActive(false);
        myPlayer.SetIsActive(false);
        gameOver = true;
      } else {
        for (int j = 0; j < playerProjectiles.size(); j++) {
          if ((*opponent_[i]).GetIsActive() &&
              (*playerProjectiles[j]).GetIsActive() &&
              (*playerProjectiles[j]).IntersectsWith(opponent_[i].get())) {
            (*opponent_[i]).SetIsActive(false);
            (*playerProjectiles[j]).SetIsActive(false);
              scoreCount = scoreCount + 1;
          }
        }
      }
    }
    for (int i = 0; i < opponentProjectiles.size(); i++) {
      if ((*opponentProjectiles[i]).GetIsActive() && myPlayer.GetIsActive() &&
          myPlayer.IntersectsWith(opponentProjectiles[i].get())) {
        (*opponentProjectiles[i]).SetIsActive(false);
        myPlayer.SetIsActive(false);
        gameOver = true;
      }
    }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    if ((*opponent_[i]).LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> opponent_ptr =
          std::make_unique<OpponentProjectile>((*opponent_[i]).GetX(),
                                               (*opponent_[i]).GetY());
      opponentProjectiles.push_back(std::move(opponent_ptr));
    }
  }
}

void Game::MoveGameElements() {
    for (int i = 0; i < playerProjectiles.size(); i++) {
    if ((*playerProjectiles[i]).GetIsActive()) {
      (*playerProjectiles[i]).Move(screen);
    }
  }
  for (int i = 0; i < opponent_.size(); i++) {
    if ((*opponent_[i]).GetIsActive()) {
      (*opponent_[i]).Move(screen);
    }
  }
  for (int i = 0; i < opponentProjectiles.size(); i++) {
    if ((*opponentProjectiles[i]).GetIsActive()) {
      (*opponentProjectiles[i]).Move(screen);
    }
  }
}

void Game::RemoveInactive() {
  for (int i = playerProjectiles.size() - 1; i >= 0; i--) {
    if ((*playerProjectiles[i]).GetIsActive() == false) {
      playerProjectiles.erase(playerProjectiles.begin() + i);
    }
  }
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if ((*opponent_[i]).GetIsActive() == false) {
      opponent_.erase(opponent_.begin() + i);
    }
  }
  for (int i = opponentProjectiles.size() - 1; i >= 0; i--) {
    if ((*opponentProjectiles[i]).GetIsActive() == false) {
      opponentProjectiles.erase(opponentProjectiles.begin() + i);
    }
  }
}

void Game::CreateOpponents() {
  std::unique_ptr<Opponent> opponent = std::make_unique<Opponent>();
  opponent_.push_back(std::move(opponent));
}

void Game::UpdateScreen() {
  graphics::Color navyBlue(25, 0, 142);
  graphics::Color brightRed(255, 11, 0);
  screen.DrawRectangle(0, 0, screen.GetWidth(), screen.GetHeight(),
                          graphics::Color(255, 255, 255));
  std::string scoreCounttxt = "Score: " + std::to_string(gameOver);
  screen.DrawText(3, 3, scoreCounttxt, 20, navyBlue);
  if (gameOver == true) {
    screen.DrawText(250, 300, "GAME OVER", 60, brightRed);
  }

  if (myPlayer.GetIsActive()) {
    myPlayer.Draw(screen);
  }
  for (int i = 0; i < opponent_.size(); i++) {
    if ((*opponent_[i]).GetIsActive()) {
      (*opponent_[i]).Draw(screen);
    }
  }
  for (int i = 0; i < opponentProjectiles.size(); i++) {
    if ((*opponentProjectiles[i]).GetIsActive()) {
      (*opponentProjectiles[i]).Draw(screen);
    }
  }
  for (int i = 0; i < playerProjectiles.size(); i++) {
    if ((*playerProjectiles[i]).GetIsActive()) {
      (*playerProjectiles[i]).Draw(screen);
    }
  }
}

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen.Flush();
}
