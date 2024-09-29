#ifndef TETRIS_MODEL_H
#define TETRIS_MODEL_H

#include <random>

#include "../Basemodel.h"
#include "backend.h"

namespace s21 {

class Tetris_model : public Base {
 private:
  GameState state;
  GameInfo_t game_info;
  int** field_temp;
  Figure figure;
  int current_figure;
  int next_figure;
  long long cur_time_{};
  long long last_move_time_{};

 public:
  Tetris_model();
  ~Tetris_model();
  GameInfo_t* UpdateData(UserAction_t);

 private:
  ActionMatrix<Tetris_model> Event;
  void InitActionMatrix();
  void InitGame();
  void Move();
  void Spawn();
  int get_random_number();
  void Move_left();
  void Move_right();
  void Move_down();
  void Rotate();
  void check_collide();
  void To_array();
  void check_score();
  void Game_over();
  void Pause();
  void unPause();
  void next_fig();
  void exit_game();
};
}  // namespace s21

#endif  // TETRIS_MODEL_H
