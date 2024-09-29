#ifndef BASEMODEL_H
#define BASEMODEL_H

#define field_height 22
#define field_width 12
#define field_height_shift 1
#define field_width_shift 1
#define user_act_count 9
#define START_X 0+field_height_shift
#define START_Y (field_width / 2)
#include <cstddef>
#include <tuple>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include <set>
enum class GameState { START, SPAWN, MOVING, COLLIDE, PAUSE, EXIT, GAMEOVER  };
enum class Direction {UP,DOWN,LEFT,RIGHT};
enum class Widget{Tetris,Snake};

struct Coords
{
    int x;
    int y;


    Coords() {x=0;y=0;}
    Coords(int x1,int y1):x(x1),y(y1){}

    bool operator<(const Coords& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

enum class UserAction_t {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action,
    No_act
};

struct GameInfo_t {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;



    GameInfo_t() {
        field = new int*[field_height];
        for (int i = 0;i<field_height;i++){
            field[i]=new int[field_width];
        }
        next = new int*[4];
        for (int i = 0;i<4;i++){
            next[i]=new int[4];
        }
        score = 0;
        high_score=0;
        level=1;
        speed=1;
        pause=0;

    }
    ~GameInfo_t(){
        for (int i = 0;i<field_height;i++){
            delete[] field[i];
        }
        delete[] field;

        for (int i = 0;i<4;i++){
            delete[] next[i];
        }
        delete[] next;
    }
};



template<class Model>
class ActionMatrix
{

    using Action = void (Model::*)();

    Action matrix[8][8]={};

    class Proxy {
    private:
        Action* row;

    public:
        /// @brief Constructs a Proxy object.
        ///
        /// @param row The row of the matrix to proxy.
        explicit Proxy(Action* row) : row(row) {}

        /// @brief Returns the function pointer for a given action.
        ///
        /// @param action The action to access.
        /// @return The function pointer for the action.
        Action& operator[](UserAction_t action) {
            return row[static_cast<size_t>(action)];
        }

        /// @brief Returns the function pointer for a given index.
        ///
        /// @param action The index to access.
        /// @return The function pointer for the index.
        Action& operator[](int action) { return row[action]; }
    };
public:
    ActionMatrix() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                matrix[i][j] = nullptr;
            }
        }
    }

    Proxy operator[](GameState state) {
        return Proxy(matrix[static_cast<size_t>(state)]);
    }

};

class Base
{
public:
    static long long getCurTime() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        return ms.count();
    }

    static int readBestScore(const std::string& filename) {
        int val = 0;
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> val;
            file.close();
        }
        return val;
    }

    static void writeBestScore(int val, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << val;
            file.close();
        }
    }

};

#endif // BASEMODEL_H
