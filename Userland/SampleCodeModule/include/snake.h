#ifndef SNAKE_H
#define SNAKE_H

#include <colors.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

#define WIDTH 1028
#define HEIGHT 768
#define SIZE 32

int startGame(int players);
void paintBackground(char board[HEIGHT][WIDTH]);
void singlePlayer();
void gameFunction(char board[HEIGHT][WIDTH]);

#endif