#ifndef SNAKE_H
#define SNAKE_H

#include <colors.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

<<<<<<< HEAD
#define WIDTH 1028
=======
#define WIDTH 1024
>>>>>>> 1c57567c4713d3577d6092910f34636e77dd2178
#define HEIGHT 768
#define SIZE 32

int startGame(int players);
void paintBackground(char board[HEIGHT][WIDTH]);
void singlePlayer();
void gameFunction(char board[HEIGHT][WIDTH]);

#endif