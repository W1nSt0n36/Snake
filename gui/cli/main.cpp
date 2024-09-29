#include "controller.h"
#include "frontend.h"
#include "snake.h"
#include "tetris_model.h"

int main() {
  s21::Snake snake;
  s21::Tetris_model tetris;
  Controller<s21::Snake> snake_controller(&snake);
  Controller<s21::Tetris_model> tetris_controller(&tetris);
  ConsoleView w(&snake_controller, &tetris_controller);
  w.eventloop();
  return 0;
}
