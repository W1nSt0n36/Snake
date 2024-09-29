#ifndef SNAKE_H
#define SNAKE_H

#include <set>

#include "../Basemodel.h"

namespace s21 {
class Snake : public Base {
 public:
  Coords head;
  std::vector<Coords> body;
  Direction dir;
  GameInfo_t game_info;
  GameState state;
  Coords fruit;
  long long cur_time_{};
  long long last_move_time_{};
  // long long cur_interval_{};
 public:
  Snake();
  ~Snake();
  GameInfo_t* UpdateData(UserAction_t);
  void InitGame();
  void Move();
  void Start();
  void ExitGame();
  void Moveleft();
  void Moveright();
  void Moveup();
  void Movedown();
  void Collide();
  void To_array();
  void Game_over();
  void New_fruit();
  void Check_score();
  void Move_acton();
  void Pause();
  void unPause();
  void exit_game();

 private:
  ActionMatrix<Snake> Events;
  void InitActionMatrix();
};
}  // namespace s21
#endif  // SNAKE_H
