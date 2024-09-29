#ifndef MAINWINDO_0_H
#define MAINWINDO_0_H

#include <QMainWindow>

#include <Basemodel.h>
#include <snake.h>
#include <tetris_model.h>
#include <mainwindow.h>

namespace Ui {
class MainWindo_0;
}

class MainWindo_0 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindo_0(Controller<s21::Snake> *snake,Controller<s21::Tetris_model>*tetris,QWidget *parent = nullptr);
    ~MainWindo_0();
    using SnakeController = Controller<s21::Snake>;
    using TetrisController = Controller<s21::Tetris_model>;

private:
    Ui::MainWindo_0 *ui;
    s21::MainWindow *window;

    SnakeController *snake_controller;
    TetrisController *tetris_controller;

private slots:
    void onSnakeButtonClicked();  // Слот для запуска игры Snake
    void onTetrisButtonClicked(); // Слот для запуска игры Tetris
};

#endif // MAINWINDO_0_H
