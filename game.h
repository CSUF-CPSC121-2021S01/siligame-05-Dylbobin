#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() : Game(800, 600) {}
  Game(const int &width, const int &height) {
    screen.Initialize(width, height);
  }

  int GetScore() const { return scoreCount; }
  bool HasLost() const { return gameOver; }

  void CreateOpponents();

  void OnMouseEvent(const graphics::MouseEvent &mouseEvent) override;

  void Init() {
    myPlayer.SetX(300);
    myPlayer.SetY(200);
    screen.AddMouseEventListener(*this);
    screen.AddAnimationEventListener(*this);
  }

  void FilterIntersections();

  void MoveGameElements();

  void RemoveInactive();

  void LaunchProjectiles();

  void UpdateScreen();

  void Start() { screen.ShowUntilClosed(); }

  void OnAnimationStep() override;

  graphics::Image &GetGameScreen() { return screen; }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return playerProjectiles;
  }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponentProjectiles;
  }
  Player &GetPlayer() { return myPlayer; }

 private:
  graphics::Image screen;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponentProjectiles;
  std::vector<std::unique_ptr<PlayerProjectile>> playerProjectiles;
  Player myPlayer;
  bool gameOver = false;
  int scoreCount = 0;
};
#endif
