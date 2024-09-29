#include "mainwindow.h"
#include "./ui_mainwindow.h"

namespace s21{
MainWindow::MainWindow(Controller<s21::Snake> *snake,Controller<s21::Tetris_model>*tetris,Widget widget,QWidget *parent)
    : QMainWindow(parent),snake_controller(snake),tetris_controller(tetris),widget(widget)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene_2=new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView->setScene(scene);
    m_timer_ = new QTimer(this);
    action=UserAction_t::Start;
    label = new QLabel(this);
    label->setGeometry(QRect(QPoint(100, 80), QSize(200, 50)));
    connect(m_timer_, &QTimer::timeout, this, &MainWindow::UpdateWindow);
    m_timer_->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCurrentState()
{
    scene->clear();
    int pixelSize=25;
    for (int x = 0+field_height_shift; x < field_height-field_height_shift; ++x) {
        for (int y = 0+field_width_shift; y < field_width-field_width_shift; ++y) {
            QGraphicsRectItem* rect = new QGraphicsRectItem(y * pixelSize, x * pixelSize, pixelSize, pixelSize);
            if (game_info->field[x][y] == 1) {
                rect->setBrush(Qt::black); // Черный цвет для 1
            } else if(game_info->field[x][y] == 2) {
                rect->setBrush(Qt::red); // red для 0
            }
            else if(game_info->field[x][y]==3){
                rect->setBrush(Qt::green);
            }
            else{
                rect->setBrush(Qt::white);
            }
            scene->addItem(rect);
        }
    }
    scene_2->clear();
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            QGraphicsRectItem* rect = new QGraphicsRectItem(y * pixelSize, x * pixelSize, pixelSize, pixelSize);
            if (game_info->next[x][y] == 1) {
                rect->setBrush(Qt::black); // Черный цвет для 1
            }
            else{
                rect->setBrush(Qt::white);
            }
            scene_2->addItem(rect);
        }
    }
    ui->label_level->setText(QString::number(game_info->level));
    ui->label_score->setText(QString::number(game_info->score));
    ui->label_high_score->setText(QString::number(game_info->high_score));
}


void MainWindow::UpdateWindow()
{
    if (widget==Widget::Snake){
        game_info=snake_controller->Update(action);
    } else {
        game_info=tetris_controller->Update(action);
    }
    if (game_info->pause==2){
        Game_over_screen();
        action=UserAction_t::No_act;
        return;
    }
    if (game_info->pause==1){
        label->setText("Paused");
        return;
    }
    action=UserAction_t::No_act;
    label->setText("");
    updateCurrentState();

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    switch (key) {
    case Qt::Key_A:
        action = UserAction_t::Left;
        qInfo()<<"left";
        break;
    case Qt::Key_D:
        action = UserAction_t::Right;
        qInfo()<<"right";
        break;
    case Qt::Key_W:
        action = UserAction_t::Up;
        qInfo()<<"up";
        break;
    case Qt::Key_S:
        action = UserAction_t::Down;
        qInfo()<<"down";
        break;
    case Qt::Key_F:
        action = UserAction_t::Start;
        qInfo()<<"enter";
        break;
    case Qt::Key_E:
        action=UserAction_t::Action;
        break;
    case Qt::Key_P:
        action = UserAction_t::Pause;
        break;
    default:
        break;
    }
}

void MainWindow::Game_over_screen()
{

    label->setText("Game_over");
    label->show();
}
}
