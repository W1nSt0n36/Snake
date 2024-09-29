#include "mainwindow.h"
#include "mainwindo_0.h"

#include <QApplication>
#include "controller.h"
#include "snake.h"
#include "tetris_model.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Snake snake;
    s21::Tetris_model tetris;
    Controller<s21::Snake>snake_controller(&snake);
    Controller<s21::Tetris_model>tetris_controller(&tetris);
    //s21::MainWindow w(&snake_controller,&tetris_controller);
    MainWindo_0 w(&snake_controller,&tetris_controller);
    w.show();
    return a.exec();
}
