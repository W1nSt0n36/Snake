CC := g++
CFLAGS := -I gui/cli -I brick_game/tetris -I brick_game -I brick_game/snake -I controller -Wall -Werror -Wextra --coverage
OBJS_FSM := tetris_model.o backend.o snake.o frontend.o main.o
OBJ_CLI := gui/cli/frontend.o
DIST_DIR := tetris_1.0
DESKTOR_TARGET= snake

TEST_SRC=tests/tests.cpp
TEST_OBJ := $(TEST_SRC:.cpp=.o)

brick_game_cli: brick_game_cli.a
	$(CC) $(CFLAGS) main.o brick_game_cli.a -lncurses -o brick_game_cli
	rm -f $(OBJS_FSM) $(OBJ_CLI)

%.o: brick_game/tetris/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: gui/cli/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: brick_game/snake/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: controller/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

brick_game_cli.a: $(OBJS_FSM)
	ar rc brick_game_cli.a $(OBJS_FSM)
	ranlib brick_game_cli.a

brick_game_desktop:
	cmake -B build 
	cd build && cmake --build ./ && mv $(DESKTOR_TARGET) ../


test: $(TEST_OBJ) snake.o
	$(CC) $(CFLAGS) $^ -o $@ -lgtest -pthread 

$(TEST_OBJ): $(TEST_SRC) 
	$(CC) $(CFLAGS) -c $< -o $@ 



coverage: test
	lcov --directory . --zerocounters
	./test
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage_filtered.info  # Exclude system headers
	lcov --remove coverage_filtered.info '*/gtest/*' --output-file coverage_filtered.info  # Exclude gtest files
	genhtml coverage_filtered.info --output-directory coverage_report


clean: 
	rm -rf $(OBJS_FSM) $(OBJ_CLI)  brick_game_cli.a brick_game_cli SnakeScore.txt TetrisScore.txt snake test *.info coverage_report tests/*.gcda tests/*.gcno  tests/tests.o
	rm -rf snake.gcda snake.gcno
	rm -rf build/*