#ifndef BACKEND_H
#define BACKEND_H

#include "Basemodel.h"

struct Figure {
  int pos_x1;
  int pos_y1;
  int pos_x2;
  int pos_y2;
  int pos_x3;
  int pos_y3;
  int pos_x4;
  int pos_y4;
  int rotate;
  int type;

  Figure() {
    pos_x1 = 0;
    pos_y1 = 0;
    pos_x2 = 0;
    pos_y2 = 0;
    pos_x3 = 0;
    pos_y3 = 0;
    pos_x4 = 0;
    pos_y4 = 0;
    rotate = 0;
    type = 0;
  }
};

void init_figure_1(Figure* figure);
void init_figure_2(Figure* figure);
void init_figure_3(Figure* figure);
void init_figure_4(Figure* figure);
void init_figure_5(Figure* figure);
void init_figure_6(Figure* figure);
void init_figure_7(Figure* figure);

void rotate(Figure* figure, int** field_temp);

void rotate_figure_1(Figure* figure, int** field_temp);
void rotate_figure_2(Figure* figure, int** field_temp);
void rotate_figure_3(Figure* figure, int** field_temp);
void rotate_figure_5(Figure* figure, int** field_temp);
void rotate_figure_6(Figure* figure, int** field_temp);
void rotate_figure_7(Figure* figure, int** field_temp);

extern void (*pointer_figure[7])(Figure*);

#endif
