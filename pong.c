#include <stdio.h>
// Move Racket
int Mov_Racket(int racket_y_center, int mov) {
  if ((racket_y_center != 2) && (racket_y_center != 24))
    return racket_y_center += mov;
  else
    return racket_y_center;
}
// Change the direction of ball
int Ball_DY_Change_Racket_Top(int ball_dy) {
  return (ball_dy < 0) ? 0 : (ball_dy == 0) ? -1 : ball_dy;
}
// Change the direction of ball
int Ball_DY_Change_Racket_Bottom(int ball_dy) {
  return (ball_dy > 0) ? 0 : (ball_dy == 0) ? 1 : ball_dy;
}
// Check if ball has touched the top of the racket
int Encount_Racket_Top(int ball_x, int ball_dx, int ball_y, int racket_x,
                       int racket_y_center) {
  return (((ball_x + ball_dx) == racket_x) && (ball_y == racket_y_center - 1));
}
// Check if ball has touched the center of the racket
int Encount_Racket_Center(int ball_x, int ball_dx, int ball_y, int racket_x,
                          int racket_y_center) {
  return (((ball_x + ball_dx) == racket_x) && (ball_y == racket_y_center));
}
// Check if ball has touched the racket
int Encount_Racket(int ball_x, int ball_dx, int ball_y, int racket_x,
                   int racket_y_center) {
  return (((ball_x + ball_dx) == racket_x) &&
          ((ball_y == racket_y_center - 1) || (ball_y == racket_y_center) ||
           (ball_y == racket_y_center + 1)));
}
// Check if ball has touched the wall
int Encount_Wall(int ball_y, int ball_dy) {
  return (ball_y + ball_dy == 27 || ball_y + ball_dy == 1);
}
// Check if part of racket is sutuated on (x,y) coords
int If_Racket(int racket_x, int racket_y_center, int x, int y) {
  return ((racket_x == x) &&
          ((racket_y_center - 1 == y) || (racket_y_center == y) ||
           (racket_y_center + 1 == y)));
}
// Displays playing table
void Grid_Display(int score_first_player, int score_second_player, int ball_x,
                  int ball_y, int racket_left_x, int racket_left_y_center,
                  int racket_right_x, int racket_right_y_center) {
  // Display the grid
  for (int y = 0; y < 28; y++) {
    for (int x = 0; x < 82; x++) {
      if (y == 0 || y == 26)
        printf("-");
      else if (y == 27 && x == 40)
        printf("]");
      else if (y == 27 && x == 41)
        printf("[");
      else if (y == 27 && x == 37)
        printf("%02d", score_first_player);
      else if (y == 27 && x == 44)
        printf("%02d", score_second_player);
      else if (y == 27 && (x == 38 || x == 42))
        continue;
      else if (y != 27 && (x == 0 || x == 81))
        printf(":");
      else if (x == ball_x && y == ball_y)
        printf("o");
      else if (x == 40 || x == 41)
        printf("|");
      else if (If_Racket(racket_left_x, racket_left_y_center, x, y) ||
               If_Racket(racket_right_x, racket_right_y_center, x, y))
        printf("I");
      else
        printf(" ");
    }
    printf("\n");
  }
}
// Initializes the game round
void Game_Init() {
  // Input key
  char key = '0';
  // Score for players
  static int score_first_player = 0, score_second_player = 0;
  // Right Racket parameters
  int racket_right_y_center = 13, racket_right_x = 79,
      // Left Racket parameters
      racket_left_y_center = 13, racket_left_x = 2,
      // Ball parameters
      ball_x = 40, ball_y = 13, ball_dx = 1, ball_dy = 0;
  // Check what of the keys was pressed
  do {
    // Moving the left racket position up the board (and down the coordinate
    // axis)
    if (key == 'a')
      racket_left_y_center = Mov_Racket(racket_left_y_center, -1);
    // Moving the left racket position down the board (and up the coordinate
    // axis)
    if (key == 'z')
      racket_left_y_center = Mov_Racket(racket_left_y_center, 1);
    // Moving the right racket position up the board (and down the coordinate
    // axis)
    if (key == 'k')
      racket_right_y_center = Mov_Racket(racket_right_y_center, -1);
    // Moving the right racket position down the board (and up the coordinate
    // axis)
    if (key == 'm')
      racket_right_y_center = Mov_Racket(racket_right_y_center, 1);
    // Skip one frame
    if (key == ' ') {
      key = '0';
      continue;
    }

    // Check if ball has touched racket
    if (Encount_Racket(ball_x, ball_dx, ball_y, racket_left_x,
                       racket_left_y_center) ||
        Encount_Racket(ball_x, ball_dx, ball_y, racket_right_x,
                       racket_right_y_center)) {
      // Check if ball has touched center of the any racket
      if (Encount_Racket_Center(ball_x, ball_dx, ball_y, racket_left_x,
                                racket_left_y_center) ||
          Encount_Racket_Center(ball_x, ball_dx, ball_y, racket_right_x,
                                racket_right_y_center)) {
        ball_dx *= -1;
        ball_dy *= -1;
      } else {
        ball_dx *= -1;
        // Check if ball has touched top of the any racket
        if (Encount_Racket_Top(ball_x, ball_dx, ball_y, racket_left_x,
                               racket_left_y_center) ||
            Encount_Racket_Top(ball_x, ball_dx, ball_y, racket_right_x,
                               racket_right_y_center)) {
          ball_dy = Ball_DY_Change_Racket_Top(ball_dy);
        }
        // If hasn't touched - change movement vector because ball had touched
        // bottom of any racket
        else {
          ball_dy = Ball_DY_Change_Racket_Bottom(ball_dy);
        }
      }
    }
    // Check if ball had touched any wall. If touched - change the movement
    // vector
    if (Encount_Wall(ball_y, ball_dy)) {
      ball_dy *= -1;
    }
    // Display grid
    Grid_Display(score_first_player, score_second_player, ball_x, ball_y,
                 racket_left_x, racket_left_y_center, racket_right_x,
                 racket_right_y_center);
    // Change the position of the ball
    ball_x += ball_dx;
    ball_y += ball_dy;

    // Gets input characters from players
    key = getchar();
    // printf("\e[2J\e[3J\e[H");
  } while (key != 'q');
}

int main(void) {
  // printf("\e[2J\e[3J\e[H");
  Game_Init();
}