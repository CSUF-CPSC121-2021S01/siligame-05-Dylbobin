#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  Game space;
  space.Init();
  space.UpdateScreen();
  space.Start();
}
