
#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/snake/snake.h"
using namespace s21;

class TestSnake : public ::testing::Test {
 protected:
  GameInfo_t *gameinfo;
};

TEST_F(TestSnake, MoveSnakeUp) {
  Snake snake;
  snake.Moveup();
  EXPECT_EQ(snake.dir, Direction::UP);
}

TEST_F(TestSnake, MoveSnakeDown) {
  Snake snake;
  snake.Movedown();
  EXPECT_EQ(snake.dir, Direction::DOWN);
}

TEST_F(TestSnake, MoveSnakeright) {
  Snake snake;
  snake.Moveright();
  EXPECT_EQ(snake.dir, Direction::RIGHT);
}

TEST_F(TestSnake, MoveSnakeleft) {
  Snake snake;
  snake.Movedown();
  snake.Moveleft();
  EXPECT_EQ(snake.dir, Direction::LEFT);
}

TEST_F(TestSnake, EventStart) {
  Snake snake;
  snake.Start();
  EXPECT_EQ(snake.state, GameState::SPAWN);
}

TEST_F(TestSnake, Exitgame) {
  Snake snake;
  snake.ExitGame();
  EXPECT_EQ(snake.state, GameState::EXIT);
}

TEST_F(TestSnake, Collide) {
  Snake snake;
  snake.last_move_time_ = 0;
  snake.Move();
  EXPECT_EQ(snake.state, GameState::COLLIDE);
}

TEST_F(TestSnake, Collide2) {
  Snake snake;
  snake.last_move_time_ = 0;
  snake.Move();
  snake.Collide();
  EXPECT_EQ(snake.state, GameState::MOVING);
}

TEST_F(TestSnake, Collide3) {
  Snake snake;
  snake.last_move_time_ = 0;
  snake.Move();
  snake.head.x = snake.fruit.x;
  snake.head.y = snake.fruit.y;
  snake.Collide();
  EXPECT_EQ(snake.state, GameState::MOVING);
}

TEST_F(TestSnake, action) {
  Snake snake;
  snake.last_move_time_ = 0;
  snake.Move_acton();
  EXPECT_EQ(snake.state, GameState::COLLIDE);
}

TEST_F(TestSnake, array) {
  Snake snake;
  snake.last_move_time_ = 0;
  snake.To_array();
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
