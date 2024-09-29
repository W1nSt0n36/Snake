#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>

#include "Basemodel.h"
#include "controller.h"
#include "snake.h"
#include "tetris_model.h"

#define BOARDS_BEGIN 5
#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define ROWS_MAP field_height - field_height_shift
#define COLS_MAP field_width - field_width_shift
#define BOARD_N (ROWS_MAP + MAP_PADDING * 2)
#define BOARD_M 11
#define MAP_PADDING 3
#define HUD_WIDTH 3

void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

class ConsoleView {
 public:
  using SnakeController = Controller<s21::Snake>;
  using TetrisController = Controller<s21::Tetris_model>;
  ConsoleView(SnakeController *snake, TetrisController *tetris);

 private:
  SnakeController *snake_controller;
  TetrisController *tetris_controller;
  int widget;
  GameInfo_t *game_info;
  UserAction_t action;
  void updateCurrentState();

 public:
  void eventloop();
  void displayMenu();
  int performChoice();
  void Game_over_screen();
  void enter_action();
};

#endif
