#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtGui>
#include <QtCore>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QTimer>
#include <QKeyEvent>
#include "controller.h"
#include "snake.h"
#include "tetris_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller<s21::Snake> *snake,Controller<s21::Tetris_model>*tetris,Widget,QWidget *parent = nullptr);
    ~MainWindow();
    void updateCurrentState();
    void UpdateWindow();
    using SnakeController = Controller<s21::Snake>;
    using TetrisController = Controller<s21::Tetris_model>;
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *scene_2;
    GameInfo_t* game_info;
    QLabel* label;
    Widget widget;


    QTimer *m_timer_;
    UserAction_t action;
    SnakeController *snake_controller;
    TetrisController *tetris_controller;

    void Game_over_screen();

};
} //namespace s21
#endif // MAINWINDOW_H
