#include "backend.h"

void (*pointer_figure[7])(Figure*) = {
    init_figure_1, init_figure_2, init_figure_3, init_figure_4,
    init_figure_5, init_figure_6, init_figure_7};

void init_figure_1(Figure* figure) {
  figure->pos_x2 = START_X;
  figure->pos_y2 = START_Y;
  figure->pos_x1 = figure->pos_x2;
  figure->pos_y1 = figure->pos_y2 - 1;
  figure->pos_x3 = figure->pos_x2;
  figure->pos_y3 = figure->pos_y2 + 1;
  figure->pos_x4 = figure->pos_x3;
  figure->pos_y4 = figure->pos_y3 + 1;
  figure->type = 1;
  figure->rotate = 0;
  // ****//
}

void init_figure_2(Figure* figure) {
  figure->pos_x3 = START_X + 1;
  figure->pos_y3 = START_Y;
  figure->pos_x2 = figure->pos_x3;
  figure->pos_y2 = figure->pos_y3 - 1;
  figure->pos_x1 = figure->pos_x2 - 1;
  figure->pos_y1 = figure->pos_y2;
  figure->pos_x4 = figure->pos_x3;
  figure->pos_y4 = figure->pos_y3 + 1;
  figure->type = 2;
  figure->rotate = 0;
  /*

  *
  ***

    */
}

void init_figure_3(Figure* figure) {
  figure->pos_x2 = START_X + 1;
  figure->pos_y2 = START_Y;
  figure->pos_x1 = figure->pos_x2;
  figure->pos_y1 = figure->pos_y2 - 1;
  figure->pos_x3 = figure->pos_x2;
  figure->pos_y3 = figure->pos_y2 + 1;
  figure->pos_x4 = figure->pos_x3 - 1;
  figure->pos_y4 = figure->pos_y3;
  figure->type = 3;
  figure->rotate = 0;
  /*

    *
  ***

    */
}

void init_figure_4(Figure* figure) {
  figure->pos_x2 = START_X + 1;
  figure->pos_y2 = START_Y;
  figure->pos_x1 = figure->pos_x2 - 1;
  figure->pos_y1 = figure->pos_y2;
  figure->pos_x3 = figure->pos_x2;
  figure->pos_y3 = figure->pos_y2 + 1;
  figure->pos_x4 = figure->pos_x3 - 1;
  figure->pos_y4 = figure->pos_y3;
  figure->type = 4;
  figure->rotate = 0;
  /*

  **
  **

    */
}

void init_figure_5(Figure* figure) {
  figure->pos_x2 = START_X + 1;
  figure->pos_y2 = START_Y;
  figure->pos_x1 = figure->pos_x2;
  figure->pos_y1 = figure->pos_y2 - 1;
  figure->pos_x3 = figure->pos_x2 - 1;
  figure->pos_y3 = figure->pos_y2;
  figure->pos_x4 = figure->pos_x3;
  figure->pos_y4 = figure->pos_y3 + 1;
  figure->type = 5;
  figure->rotate = 0;
  /*

   **
  **

    */
}

void init_figure_6(Figure* figure) {
  figure->pos_x2 = START_X + 1;
  figure->pos_y2 = START_Y;
  figure->pos_x1 = figure->pos_x2;
  figure->pos_y1 = figure->pos_y2 - 1;
  figure->pos_x3 = figure->pos_x2 - 1;
  figure->pos_y3 = figure->pos_y2;
  figure->pos_x4 = figure->pos_x3 + 1;
  figure->pos_y4 = figure->pos_y3 + 1;
  figure->type = 6;
  figure->rotate = 0;
  /*

   *
  ***

    */
}

void init_figure_7(Figure* figure) {
  figure->pos_x2 = START_X;
  figure->pos_y2 = START_Y;
  figure->pos_x1 = figure->pos_x2;
  figure->pos_y1 = figure->pos_y2 - 1;
  figure->pos_x3 = figure->pos_x2 + 1;
  figure->pos_y3 = figure->pos_y2;
  figure->pos_x4 = figure->pos_x3;
  figure->pos_y4 = figure->pos_y3 + 1;
  figure->type = 7;
  figure->rotate = 0;
  /*

   **
    **

    */
}

void rotate(Figure* figure, int** field_temp) {
  switch (figure->type) {
    case 1:
      rotate_figure_1(figure, field_temp);
      break;
    case 2:
      rotate_figure_2(figure, field_temp);
      break;
    case 3:
      rotate_figure_3(figure, field_temp);
      break;
    case 5:
      rotate_figure_5(figure, field_temp);
      break;
    case 6:
      rotate_figure_6(figure, field_temp);
      break;
    case 7:
      rotate_figure_7(figure, field_temp);
      break;
    default:
      break;
  }
}

void rotate_figure_1(Figure* figure, int** field_temp) {
  if (figure->rotate % 2 == 0) {
    if (figure->pos_x2 + 2 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x1 + 2][figure->pos_y1 + 2] != 1) {
        figure->pos_x1 += 2;
        figure->pos_y1 += 2;
        figure->pos_x2 += 1;
        figure->pos_y2 += 1;
        figure->pos_x3 += 0;
        figure->pos_y3 += 0;
        figure->pos_x4 -= 1;
        figure->pos_y4 -= 1;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 2 == 1) {
    if (figure->pos_y1 - 2 >= 0) {
      if (field_temp[figure->pos_x1 - 2][figure->pos_y1 - 2] != 1 &&
          field_temp[figure->pos_x4 + 1][figure->pos_y4 + 1] != 1) {
        figure->pos_x1 -= 2;
        figure->pos_y1 -= 2;
        figure->pos_x2 -= 1;
        figure->pos_y2 -= 1;
        figure->pos_x3 += 0;
        figure->pos_y3 += 0;
        figure->pos_x4 += 1;
        figure->pos_y4 += 1;
        figure->rotate++;

        return;
      }
    }
  }
}

void rotate_figure_2(Figure* figure, int** field_temp) {
  if (figure->rotate % 4 == 0) {
    if (figure->pos_x3 + 1 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x1 + 2][figure->pos_y1] != 1 &&
          field_temp[figure->pos_x2 + 1][figure->pos_y2 + 1] != 1) {
        figure->pos_x1 += 2;
        figure->pos_y1 += 0;
        figure->pos_x2 += 1;
        figure->pos_y2 += 1;
        figure->pos_x3 += 0;
        figure->pos_y3 += 0;
        figure->pos_x4 -= 1;
        figure->pos_y4 -= 1;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 1) {
    if (figure->pos_y1 + 2 < field_width - field_width_shift) {
      if (field_temp[figure->pos_x1][figure->pos_y1 + 2] != 1 &&
          field_temp[figure->pos_x2 - 1][figure->pos_y2 + 1] != 1 &&
          field_temp[figure->pos_x4 + 1][figure->pos_y4 - 1] != 1) {
        figure->pos_x1 -= 0;
        figure->pos_y1 += 2;
        figure->pos_x2 -= 1;
        figure->pos_y2 += 1;
        figure->pos_x3 += 0;
        figure->pos_y3 += 0;
        figure->pos_x4 += 1;
        figure->pos_y4 -= 1;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 2) {
    if (figure->pos_x1 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x1 - 2][figure->pos_y1] != 1 &&
          field_temp[figure->pos_x2 - 1][figure->pos_y2 - 1] != 1 &&
          field_temp[figure->pos_x4 + 1][figure->pos_y4 + 1] != 1) {
        figure->pos_x1 -= 2;
        figure->pos_y1 += 0;
        figure->pos_x2 -= 1;
        figure->pos_y2 -= 1;
        figure->pos_x3 += 0;
        figure->pos_y3 += 0;
        figure->pos_x4 += 1;
        figure->pos_y4 += 1;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 3) {
    if (figure->pos_y1 - 2 < field_width - field_width_shift) {
      if (field_temp[figure->pos_x1][figure->pos_y1 - 2] != 1 &&
          field_temp[figure->pos_x2 + 1][figure->pos_y2 - 1] != 1 &&
          field_temp[figure->pos_x4 - 1][figure->pos_y4 + 1] != 1) {
        figure->pos_x1 -= 0;
        figure->pos_y1 += -2;
        figure->pos_x2 += 1;
        figure->pos_y2 -= 1;
        figure->pos_x3 += 0;
        figure->pos_y3 += 0;
        figure->pos_x4 -= 1;
        figure->pos_y4 += 1;
        figure->rotate++;

        return;
      }
    }
  }
}

void rotate_figure_3(Figure* figure, int** field_temp) {
  if (figure->rotate % 4 == 0) {
    if (figure->pos_x1 + 1 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x1 + 1][figure->pos_y1 + 1] != 1 &&
          field_temp[figure->pos_x4][figure->pos_y4 - 2] != 1) {
        figure->pos_x1 += 1;
        figure->pos_y1 += 1;
        figure->pos_x2 += 0;
        figure->pos_y2 += 0;
        figure->pos_x3 -= 1;
        figure->pos_y3 -= 1;
        figure->pos_x4 -= 0;
        figure->pos_y4 -= 2;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 1) {
    if (figure->pos_y1 + 1 < field_width - field_width_shift) {
      if (field_temp[figure->pos_x1 - 1][figure->pos_y1 + 1] != 1 &&
          field_temp[figure->pos_x3 + 1][figure->pos_y3 - 1] != 1 &&
          field_temp[figure->pos_x4 + 2][figure->pos_y4 - 0] != 1) {
        figure->pos_x1 -= 1;
        figure->pos_y1 += 1;
        figure->pos_x2 -= 0;
        figure->pos_y2 += 0;
        figure->pos_x3 += 1;
        figure->pos_y3 -= 1;
        figure->pos_x4 += 2;
        figure->pos_y4 -= 0;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 2) {
    if (figure->pos_y1 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x3 + 1][figure->pos_y3 + 1] != 1 &&
          field_temp[figure->pos_x4 + 0][figure->pos_y4 + 2] != 1) {
        figure->pos_x1 -= 1;
        figure->pos_y1 -= 1;
        figure->pos_x2 -= 0;
        figure->pos_y2 -= 0;
        figure->pos_x3 += 1;
        figure->pos_y3 += 1;
        figure->pos_x4 += 0;
        figure->pos_y4 += 2;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 3) {
    if (figure->pos_y1 - 1 >= 0) {
      if (field_temp[figure->pos_x1 + 1][figure->pos_y1 - 1] != 1 &&
          field_temp[figure->pos_x3 - 1][figure->pos_y3 + 1] != 1 &&
          field_temp[figure->pos_x4 - 2][figure->pos_y4 + 0] != 1) {
        figure->pos_x1 += 1;
        figure->pos_y1 -= 1;
        figure->pos_x2 += 0;
        figure->pos_y2 -= 0;
        figure->pos_x3 -= 1;
        figure->pos_y3 += 1;
        figure->pos_x4 -= 2;
        figure->pos_y4 += 0;
        figure->rotate++;

        return;
      }
    }
  }
}

void rotate_figure_5(Figure* figure, int** field_temp) {
  if (figure->rotate % 2 == 0) {
    if (figure->pos_x1 + 1 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x1 + 1][figure->pos_y1 + 1] != 1 &&
          field_temp[figure->pos_x4][figure->pos_y4 - 2] != 1) {
        figure->pos_x1 += 1;
        figure->pos_y1 += 1;
        figure->pos_x2 += 0;
        figure->pos_y2 += 0;
        figure->pos_x3 += 1;
        figure->pos_y3 -= 1;
        figure->pos_x4 -= 0;
        figure->pos_y4 -= 2;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 2 == 1) {
    if (figure->pos_y4 + 2 < field_width - field_width_shift) {
      if (field_temp[figure->pos_x4 - 0][figure->pos_y4 + 2] != 1) {
        figure->pos_x1 -= 1;
        figure->pos_y1 -= 1;
        figure->pos_x2 -= 0;
        figure->pos_y2 += 0;
        figure->pos_x3 -= 1;
        figure->pos_y3 += 1;
        figure->pos_x4 += 0;
        figure->pos_y4 += 2;
        figure->rotate++;

        return;
      }
    }
  }
}

void rotate_figure_6(Figure* figure, int** field_temp) {
  if (figure->rotate % 4 == 0) {
    if (figure->pos_x1 + 1 < field_height - field_height_shift) {
      if (field_temp[figure->pos_x1 + 1][figure->pos_y1 + 1] != 1) {
        figure->pos_x1 += 1;
        figure->pos_y1 += 1;
        figure->pos_x2 += 0;
        figure->pos_y2 += 0;
        figure->pos_x3 += 1;
        figure->pos_y3 -= 1;
        figure->pos_x4 -= 1;
        figure->pos_y4 -= 1;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 1) {
    if (figure->pos_y1 + 1 < field_width - field_width_shift) {
      if (field_temp[figure->pos_x1 - 1][figure->pos_y1 + 1] != 1) {
        figure->pos_x1 -= 1;
        figure->pos_y1 += 1;
        figure->pos_x2 -= 0;
        figure->pos_y2 += 0;
        figure->pos_x3 += 1;
        figure->pos_y3 += 1;
        figure->pos_x4 += 1;
        figure->pos_y4 -= 1;
        figure->rotate++;

        return;
      }
    }
  }
  if (figure->rotate % 4 == 2) {
    figure->pos_x1 -= 1;
    figure->pos_y1 -= 1;
    figure->pos_x2 -= 0;
    figure->pos_y2 -= 0;
    figure->pos_x3 -= 1;
    figure->pos_y3 += 1;
    figure->pos_x4 += 1;
    figure->pos_y4 += 1;
    figure->rotate++;

    return;
  }
  if (figure->rotate % 4 == 3) {
    if (figure->pos_y1 - 1 >= 0) {
      if (field_temp[figure->pos_x1 + 1][figure->pos_y1 - 1] != 1) {
        figure->pos_x1 += 1;
        figure->pos_y1 -= 1;
        figure->pos_x2 += 0;
        figure->pos_y2 -= 0;
        figure->pos_x3 -= 1;
        figure->pos_y3 -= 1;
        figure->pos_x4 -= 1;
        figure->pos_y4 += 1;
        figure->rotate++;

        return;
      }
    }
  }
}

void rotate_figure_7(Figure* figure, int** field_temp) {
  if (figure->rotate % 2 == 0) {
    if (field_temp[figure->pos_x1 + 1][figure->pos_y1 + 1] != 1) {
      figure->pos_x1 += 1;
      figure->pos_y1 += 1;
      figure->pos_x2 += 0;
      figure->pos_y2 += 0;
      figure->pos_x3 -= 1;
      figure->pos_y3 += 1;
      figure->pos_x4 -= 2;
      figure->pos_y4 -= 0;
      figure->rotate++;

      return;
    }
  }
  if (figure->rotate % 2 == 1) {
    if (figure->pos_y1 - 1 >= 0) {
      if (field_temp[figure->pos_x1 - 1][figure->pos_y1 - 1] != 1 &&
          field_temp[figure->pos_x3 + 1][figure->pos_y3 - 1] != 1 &&
          field_temp[figure->pos_x4 + 2][figure->pos_y4] != 1) {
        figure->pos_x1 -= 1;
        figure->pos_y1 -= 1;
        figure->pos_x2 -= 0;
        figure->pos_y2 += 0;
        figure->pos_x3 += 1;
        figure->pos_y3 -= 1;
        figure->pos_x4 += 2;
        figure->pos_y4 += 0;
        figure->rotate++;

        return;
      }
    }
  }
}
