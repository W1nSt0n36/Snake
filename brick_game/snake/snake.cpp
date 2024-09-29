#include "snake.h"

s21::Snake::Snake() : game_info() {
  InitActionMatrix();
  InitGame();
  game_info.high_score = readBestScore("SnakeScore.txt");
}

s21::Snake::~Snake() { writeBestScore(game_info.high_score, "SnakeScore.txt"); }

GameInfo_t* s21::Snake::UpdateData(UserAction_t action) {
  using Action = void (Snake::*)();
  Action cur_func = Events[state][action];

  if (cur_func) (this->*cur_func)();

  To_array();
  return &game_info;
}

void s21::Snake::InitGame() {
  head.x = 0 + field_height_shift;
  head.y = 3 + field_width_shift;
  body = {{1, 1}, {1, 2}, {1, 3}};
  dir = Direction::RIGHT;
  state = GameState::MOVING;
  fruit.x = 15;
  fruit.y = 8;
  cur_time_ = getCurTime();
  last_move_time_ = cur_time_;
  game_info.pause = 0;
  game_info.level = 1;
  game_info.score = 0;
}

void s21::Snake::InitActionMatrix() {
  Events[GameState::START][UserAction_t::Action] = &s21::Snake::Start;
  Events[GameState::START][UserAction_t::Start] = &s21::Snake::Start;
  Events[GameState::START][UserAction_t::No_act] = &s21::Snake::Start;
  Events[GameState::START][UserAction_t::Terminate] = &s21::Snake::ExitGame;

  for (int i = 0; i < user_act_count; i++) {
    Events[GameState::SPAWN][static_cast<UserAction_t>(i)] = &Snake::InitGame;

    Events[GameState::COLLIDE][static_cast<UserAction_t>(i)] = &Snake::Collide;
    Events[GameState::PAUSE][static_cast<UserAction_t>(i)] =
        &s21::Snake::unPause;

    Events[GameState::GAMEOVER][static_cast<UserAction_t>(i)] =
        &Snake::Game_over;
  }
  Events[GameState::GAMEOVER][UserAction_t::Start] = &Snake::InitGame;
  /* MOVING STATE */
  Events[GameState::MOVING][UserAction_t::Up] = &Snake::Moveup;
  Events[GameState::MOVING][UserAction_t::Down] = &Snake::Movedown;
  Events[GameState::MOVING][UserAction_t::Right] = &Snake::Moveright;
  Events[GameState::MOVING][UserAction_t::Left] = &Snake::Moveleft;
  Events[GameState::MOVING][UserAction_t::Action] = &Snake::Move_acton;
  Events[GameState::MOVING][UserAction_t::Start] = &Snake::Move;
  Events[GameState::MOVING][UserAction_t::No_act] = &Snake::Move;
  Events[GameState::MOVING][UserAction_t::Pause] = &Snake::Pause;
  Events[GameState::MOVING][UserAction_t::Terminate] = &Snake::exit_game;
  Events[GameState::PAUSE][UserAction_t::Pause] = &s21::Snake::Pause;
  Events[GameState::PAUSE][UserAction_t::No_act] = &s21::Snake::Pause;
}
void s21::Snake::Start() { state = GameState::SPAWN; }

void s21::Snake::ExitGame() { state = GameState::EXIT; }

void s21::Snake::Move() {
  cur_time_ = getCurTime();

  if (cur_time_ - last_move_time_ <= 220 - game_info.level * 20) {
    return;
  }
  body.erase(body.begin());
  body.push_back(head);
  if (dir == Direction::RIGHT) {
    head.y++;
  }
  if (dir == Direction::LEFT) {
    head.y--;
  }
  if (dir == Direction::UP) {
    head.x--;
  }
  if (dir == Direction::DOWN) {
    head.x++;
  }

  state = GameState::COLLIDE;
  last_move_time_ = cur_time_;
}

void s21::Snake::Moveleft() {
  if (dir != Direction::RIGHT) dir = Direction::LEFT;
  s21::Snake::Move();
}

void s21::Snake::Moveright() {
  if (dir != Direction::LEFT) dir = Direction::RIGHT;
  s21::Snake::Move();
}

void s21::Snake::Moveup() {
  if (dir != Direction::DOWN) dir = Direction::UP;
  s21::Snake::Move();
}

void s21::Snake::Movedown() {
  if (dir != Direction::UP) dir = Direction::DOWN;
  s21::Snake::Move();
}

void s21::Snake::Collide() {
  if (head.x <= 0 || head.x >= field_height - 1 || head.y <= 0 ||
      head.y >= field_width - 1) {
    state = GameState::GAMEOVER;
    return;
  }
  for (auto iter : body) {
    if (head.x == iter.x && head.y == iter.y) {
      state = GameState::GAMEOVER;
      return;
    }
  }
  if (head.x == fruit.x && head.y == fruit.y) {
    body.push_back(fruit);
    New_fruit();
    Check_score();
  }
  if (body.size() + 1 == 200) {
    state = GameState::GAMEOVER;
  }
  state = GameState::MOVING;
}

void s21::Snake::To_array() {
  for (int x = 0 + field_height_shift; x < field_height - field_height_shift;
       x++) {
    for (int y = 0 + field_width_shift; y < field_width - field_width_shift;
         y++) {
      game_info.field[x][y] = 0;
    }
  }
  game_info.field[head.x][head.y] = 2;
  for (auto iter : body) {
    game_info.field[iter.x][iter.y] = 1;
  }
  game_info.field[fruit.x][fruit.y] = 3;
}

void s21::Snake::Game_over() { game_info.pause = 2; }

void s21::Snake::New_fruit() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_width(1, field_width - 2);
  std::uniform_int_distribution<> dis_height(1, field_height - 2);
  std::set<Coords> snakes_body(body.begin(), body.end());
  snakes_body.insert(head);

  do {
    fruit.x = dis_height(gen);
    fruit.y = dis_width(gen);

  } while (snakes_body.find(fruit) != snakes_body.end());
}

void s21::Snake::Check_score() {
  game_info.score++;
  if (game_info.high_score < game_info.score) {
    game_info.high_score = game_info.score;
  }

  game_info.level = game_info.score / 5 + 1;
}

void s21::Snake::Move_acton() {
  body.erase(body.begin());
  body.push_back(head);
  if (dir == Direction::RIGHT) {
    head.y++;
  }
  if (dir == Direction::LEFT) {
    head.y--;
  }
  if (dir == Direction::UP) {
    head.x--;
  }
  if (dir == Direction::DOWN) {
    head.x++;
  }

  state = GameState::COLLIDE;
}

void s21::Snake::Pause() {
  game_info.pause = 1;
  state = GameState::PAUSE;
}

void s21::Snake::unPause() {
  game_info.pause = 0;
  state = GameState::MOVING;
}

void s21::Snake::exit_game() { game_info.pause = 3; }
