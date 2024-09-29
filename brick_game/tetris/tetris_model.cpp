#include "tetris_model.h"

s21::Tetris_model::Tetris_model() : game_info() {
  field_temp = new int*[field_height];
  for (int i = 0; i < field_height; i++) {
    field_temp[i] = new int[field_width];
  }

  s21::Tetris_model::InitActionMatrix();
  InitGame();
  game_info.high_score = readBestScore("TetrisScore.txt");
}

s21::Tetris_model::~Tetris_model() {
  for (int i = 0; i < field_height; i++) {
    delete[] field_temp[i];
  }
  delete[] field_temp;
  writeBestScore(game_info.high_score, "TetrisScore.txt");
}

void s21::Tetris_model::InitActionMatrix() {
  Event[GameState::START][UserAction_t::Action] = &s21::Tetris_model::InitGame;
  Event[GameState::START][UserAction_t::Start] = &s21::Tetris_model::InitGame;
  Event[GameState::START][UserAction_t::No_act] = &s21::Tetris_model::InitGame;
  // Event[GameState::START][UserAction_t::Terminate] = &s21::Snake::ExitGame;

  for (int i = 0; i < user_act_count; i++) {
    Event[GameState::SPAWN][static_cast<UserAction_t>(i)] =
        &Tetris_model::Spawn;

    Event[GameState::COLLIDE][static_cast<UserAction_t>(i)] =
        &Tetris_model::check_collide;
    Event[GameState::GAMEOVER][static_cast<UserAction_t>(i)] =
        &Tetris_model::Game_over;
    Event[GameState::PAUSE][static_cast<UserAction_t>(i)] =
        &s21::Tetris_model::unPause;
  }
  Event[GameState::GAMEOVER][UserAction_t::Start] = &Tetris_model::InitGame;
  /* MOVING STATE */
  Event[GameState::MOVING][UserAction_t::Down] = &Tetris_model::Move_down;
  Event[GameState::MOVING][UserAction_t::Right] = &Tetris_model::Move_right;
  Event[GameState::MOVING][UserAction_t::Left] = &Tetris_model::Move_left;
  Event[GameState::MOVING][UserAction_t::Action] = &Tetris_model::Rotate;
  Event[GameState::MOVING][UserAction_t::Terminate] = &Tetris_model::exit_game;
  // Event[GameState::MOVING][UserAction_t::Start] =
  //    &Tetris_model::Move;
  Event[GameState::MOVING][UserAction_t::No_act] = &Tetris_model::Move;
  Event[GameState::MOVING][UserAction_t::Pause] = &Tetris_model::Pause;
  Event[GameState::PAUSE][UserAction_t::Pause] = &s21::Tetris_model::Pause;
  Event[GameState::PAUSE][UserAction_t::No_act] = &s21::Tetris_model::Pause;
}

GameInfo_t* s21::Tetris_model::UpdateData(UserAction_t action) {
  using Action = void (Tetris_model::*)();
  Action cur_func = Event[state][action];

  if (cur_func) (this->*cur_func)();

  To_array();
  return &game_info;
}

void s21::Tetris_model::InitGame() {
  game_info.level = 1;
  game_info.score = 0;
  game_info.pause = 0;
  game_info.speed = 0;

  cur_time_ = getCurTime();
  last_move_time_ = cur_time_;
  next_figure = get_random_number();
  current_figure = next_figure;
  next_figure = get_random_number();

  state = GameState::SPAWN;

  for (int x = 0; x < field_height; x++) {
    for (int y = 0; y < field_width; y++) {
      field_temp[x][y] = 0;
    }
  }
}

void s21::Tetris_model::Move() {
  cur_time_ = getCurTime();

  if (cur_time_ - last_move_time_ <= 220 - game_info.level * 20) {
    return;
  }
  figure.pos_x1++;
  figure.pos_x2++;
  figure.pos_x3++;
  figure.pos_x4++;

  state = GameState::COLLIDE;
  last_move_time_ = cur_time_;
  // qInfo()<<"move state";
}

void s21::Tetris_model::Spawn() {
  current_figure = next_figure;
  next_figure = get_random_number();
  void (*init_figure)(Figure*) = pointer_figure[current_figure];
  init_figure(&figure);
  next_fig();
  state = GameState::MOVING;
}

int s21::Tetris_model::get_random_number() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> random(0, 6);
  return (random(gen)) % 7;
}

void s21::Tetris_model::Move_left() {
  if (figure.pos_y1 > 1 && figure.pos_y2 > 1 && figure.pos_y3 > 1 &&
      figure.pos_y4 > 1) {
    if (field_temp[figure.pos_x1][figure.pos_y1 - 1] != 1 &&
        field_temp[figure.pos_x2][figure.pos_y2 - 1] != 1 &&
        field_temp[figure.pos_x3][figure.pos_y3 - 1] != 1 &&
        field_temp[figure.pos_x4][figure.pos_y4 - 1] != 1) {
      figure.pos_y1--;
      figure.pos_y2--;
      figure.pos_y3--;
      figure.pos_y4--;
    }
  }

  Move();
}

void s21::Tetris_model::Move_right() {
  if (figure.pos_y1 < 10 && figure.pos_y2 < 10 && figure.pos_y3 < 10 &&
      figure.pos_y4 < 10) {
    if (field_temp[figure.pos_x1][figure.pos_y1 + 1] != 1 &&
        field_temp[figure.pos_x2][figure.pos_y2 + 1] != 1 &&
        field_temp[figure.pos_x3][figure.pos_y3 + 1] != 1 &&
        field_temp[figure.pos_x4][figure.pos_y4 + 1] != 1) {
      figure.pos_y1++;
      figure.pos_y2++;
      figure.pos_y3++;
      figure.pos_y4++;
    }
  }

  Move();
}

void s21::Tetris_model::Move_down() {
  if (figure.pos_x1 < field_height - 1 && figure.pos_x2 < field_height - 1 &&
      figure.pos_x3 < field_height - 1 && figure.pos_x4 < field_height - 1) {
    if (field_temp[figure.pos_x1 + 1][figure.pos_y1] != 1 &&
        field_temp[figure.pos_x2 + 1][figure.pos_y2] != 1 &&
        field_temp[figure.pos_x3 + 1][figure.pos_y3] != 1 &&
        field_temp[figure.pos_x4 + 1][figure.pos_y4] != 1) {
      figure.pos_x1++;
      figure.pos_x2++;
      figure.pos_x3++;
      figure.pos_x4++;
    }
  }
  state = GameState::COLLIDE;
}

void s21::Tetris_model::Rotate() { rotate(&figure, field_temp); }

void s21::Tetris_model::check_collide() {
  for (int i = 0; i < field_width; i++) {
    if (field_temp[2][i] == 1) {
      state = GameState::GAMEOVER;
      return;
    }
  }

  if (figure.pos_x1 + 1 != field_height - 1 &&
      figure.pos_x2 + 1 != field_height - 1 &&
      figure.pos_x3 + 1 != field_height - 1 &&
      figure.pos_x4 + 1 != field_height - 1) {
    if (field_temp[figure.pos_x1 + 1][figure.pos_y1] == 1 ||
        field_temp[figure.pos_x2 + 1][figure.pos_y2] == 1 ||
        field_temp[figure.pos_x3 + 1][figure.pos_y3] == 1 ||
        field_temp[figure.pos_x4 + 1][figure.pos_y4] == 1) {
      field_temp[figure.pos_x1][figure.pos_y1] = 1;
      field_temp[figure.pos_x2][figure.pos_y2] = 1;
      field_temp[figure.pos_x3][figure.pos_y3] = 1;
      field_temp[figure.pos_x4][figure.pos_y4] = 1;
      state = GameState::SPAWN;
      check_score();
      return;
    }
  } else if (figure.pos_x1 + 1 == field_height - 1 ||
             figure.pos_x2 + 1 == field_height - 1 ||
             figure.pos_x3 + 1 == field_height - 1 ||
             figure.pos_x4 + 1 == field_height - 1) {
    field_temp[figure.pos_x1][figure.pos_y1] = 1;
    field_temp[figure.pos_x2][figure.pos_y2] = 1;
    field_temp[figure.pos_x3][figure.pos_y3] = 1;
    field_temp[figure.pos_x4][figure.pos_y4] = 1;
    state = GameState::SPAWN;
    check_score();
    return;
  }
  state = GameState::MOVING;
}

void s21::Tetris_model::To_array() {
  for (int x = 0; x < field_height; x++) {
    for (int y = 0; y < field_width; y++) {
      game_info.field[x][y] = field_temp[x][y];
    }
  }
  game_info.field[figure.pos_x1][figure.pos_y1] = 2;
  game_info.field[figure.pos_x2][figure.pos_y2] = 2;
  game_info.field[figure.pos_x3][figure.pos_y3] = 2;
  game_info.field[figure.pos_x4][figure.pos_y4] = 2;
}

void s21::Tetris_model::check_score() {
  game_info.level = game_info.score / 100 + 1;
  int count_1 = 0;
  int count_rows = 0;
  for (int i = field_height - 1; i >= 1; i--) {
    for (int j = 0; j < field_width; j++) {
      if (field_temp[i][j] == 1) {
        count_1++;
      }
    }
    if (count_1 == field_width - 2) {
      count_rows++;
      for (int j = 0; j < field_width - 1; j++) {
        field_temp[i][j] = 0;
      }
      for (int j = i - 1; j >= 0; j--) {
        int* temp = field_temp[j];
        field_temp[j] = field_temp[j + 1];
        field_temp[j + 1] = temp;
      }
    }
    count_1 = 0;
  }
  if (count_rows == 1) {
    game_info.score += 100;
  } else if (count_rows == 2) {
    game_info.score += 300;
  } else if (count_rows == 3) {
    game_info.score += 700;
  } else if (count_rows == 4) {
    game_info.score += 1500;
  }
  if (game_info.score > game_info.high_score) {
    game_info.high_score = game_info.score;
  }
}

void s21::Tetris_model::Game_over() { game_info.pause = 2; }

void s21::Tetris_model::Pause() {
  game_info.pause = 1;
  state = GameState::PAUSE;
}

void s21::Tetris_model::unPause() {
  game_info.pause = 0;
  state = GameState::MOVING;
}

void s21::Tetris_model::next_fig() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      game_info.next[i][j] = 0;
    }
  }
  switch (next_figure) {
    case 0:
      game_info.next[1][0] = 1;
      game_info.next[1][1] = 1;
      game_info.next[1][2] = 1;
      game_info.next[1][3] = 1;
      break;
    case 1:
      game_info.next[0][0] = 1;
      game_info.next[1][0] = 1;
      game_info.next[1][1] = 1;
      game_info.next[1][2] = 1;
      break;
    case 2:
      game_info.next[1][0] = 1;
      game_info.next[1][1] = 1;
      game_info.next[1][2] = 1;
      game_info.next[0][2] = 1;
      break;
    case 3:
      game_info.next[0][0] = 1;
      game_info.next[1][1] = 1;
      game_info.next[1][0] = 1;
      game_info.next[0][1] = 1;
      break;
    case 4:
      game_info.next[1][0] = 1;
      game_info.next[1][1] = 1;
      game_info.next[0][1] = 1;
      game_info.next[0][2] = 1;
      break;
    case 5:
      game_info.next[1][0] = 1;
      game_info.next[1][1] = 1;
      game_info.next[0][1] = 1;
      game_info.next[1][2] = 1;
      break;
    case 6:
      game_info.next[0][0] = 1;
      game_info.next[0][1] = 1;
      game_info.next[1][1] = 1;
      game_info.next[1][2] = 1;
      break;
    default:
      break;
  }
}

void s21::Tetris_model::exit_game() { game_info.pause = 3; }
