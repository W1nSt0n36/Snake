#include "frontend.h"

#include <iostream>
void print_overlay(void) {
  print_rectangle(-1, ROWS_MAP - 0, -1, BOARD_M);
  print_rectangle(-1, ROWS_MAP - 1, BOARD_M + 2, BOARD_M + 13);

  print_rectangle(1, 3, BOARD_M + 3, BOARD_M + HUD_WIDTH + 9);
  print_rectangle(4, 6, BOARD_M + 3, BOARD_M + HUD_WIDTH + 9);
  print_rectangle(7, 9, BOARD_M + 3, BOARD_M + HUD_WIDTH + 9);

  MVPRINTW(2, BOARD_M + 5, "LEVEL");
  MVPRINTW(5, BOARD_M + 5, "SCORE");
  MVPRINTW(8, BOARD_M + 5, "MAX SCORE");

  // MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1,
  // INTRO_MESSAGE);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void ConsoleView::updateCurrentState() {
  for (int i = 1; i < field_height - field_height_shift; i++) {
    for (int j = 1; j < field_width - field_width_shift; j++) {
      if (game_info->field[i][j] == 1) {
        MVADDCH(i, j, '*');
      } else if (game_info->field[i][j] == 2) {
        MVADDCH(i, j, '#');
      } else if (game_info->field[i][j] == 3) {
        MVADDCH(i, j, 'o');
      } else
        MVADDCH(i, j, ' ');
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_info->next[i][j] == 1) {
        MVADDCH(14 + i, BOARD_M + 6 + j, '*');
      } else {
        MVADDCH(14 + i, BOARD_M + 6 + j, ' ');
      }
    }
  }
  MVPRINTW(5, BOARD_M + 12, "%d", game_info->score);
  MVPRINTW(8, BOARD_M + 16, "%d", game_info->high_score);
  MVPRINTW(2, BOARD_M + 12, "%d", game_info->level);
}

void ConsoleView::displayMenu() {
  MVPRINTW(1, 1, "=======");
  MVPRINTW(2, 1, "MENU");
  MVPRINTW(3, 1, "=======");
  MVPRINTW(4, 1, "Snake");
  MVPRINTW(5, 1, "Tetris");
}

int ConsoleView::performChoice() {
  std::cout << "Input a menu item digit: ";
  int choice = getch();
  return choice;
}

void ConsoleView::Game_over_screen() { MVPRINTW(1, 1, "GAME_OVER"); }

void ConsoleView::enter_action() {
  int key = getch();
  switch (key) {
    case KEY_LEFT:
      action = UserAction_t::Left;

      break;
    case KEY_RIGHT:
      action = UserAction_t::Right;

      break;
    case KEY_UP:
      action = UserAction_t::Up;

      break;
    case KEY_DOWN:
      action = UserAction_t::Down;

      break;
    case 'f':
      action = UserAction_t::Start;

      break;
    case 'e':
      action = UserAction_t::Action;
      break;
    case 'p':
      action = UserAction_t::Pause;
      break;
    case 't':
      action = UserAction_t::Terminate;
      break;
    default:
      action = UserAction_t::No_act;
      MVPRINTW(1, 1, "no_act");
      break;
  }
}

ConsoleView::ConsoleView(SnakeController* snake, TetrisController* tetris)
    : snake_controller(snake), tetris_controller(tetris) {}

void ConsoleView::eventloop() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  displayMenu();
  nodelay(stdscr, false);
  widget = getch();
  nodelay(stdscr, true);
  action = UserAction_t::No_act;
  // halfdelay(100);
  print_overlay();
  while (true) {
    enter_action();
    if (widget == '0') {
      game_info = snake_controller->Update(action);
    } else {
      game_info = tetris_controller->Update(action);
    }
    if (game_info->pause == 2) {
      Game_over_screen();
      // action=UserAction_t::No_act;
      continue;
    }
    if (game_info->pause == 1) {
      MVPRINTW(1, 1, "PAUSED");
      continue;
    }
    if (game_info->pause == 3) {
      endwin();
      break;
    }
    // action=UserAction_t::No_act;

    updateCurrentState();
  }
}
