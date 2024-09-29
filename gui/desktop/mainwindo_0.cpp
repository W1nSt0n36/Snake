#include "mainwindo_0.h"
#include "./ui_mainwindo_0.h"
#include "./ui_mainwindow.h"

MainWindo_0::MainWindo_0(Controller<s21::Snake> *snake,Controller<s21::Tetris_model>*tetris,QWidget *parent)
    : QMainWindow(parent),snake_controller(snake),tetris_controller(tetris)
    , ui(new Ui::MainWindo_0)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindo_0::onSnakeButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindo_0::onTetrisButtonClicked);
}

MainWindo_0::~MainWindo_0()
{
    delete ui;
}

void MainWindo_0::onSnakeButtonClicked()
{
    window = new s21::MainWindow(snake_controller,tetris_controller,Widget::Snake);
    //s21::MainWindow w(&snake_controller,&tetris_controller,Widget::Snake,this);
    window->show();
}

void MainWindo_0::onTetrisButtonClicked()
{
    window = new s21::MainWindow(snake_controller,tetris_controller,Widget::Tetris);
    window->show();
}
