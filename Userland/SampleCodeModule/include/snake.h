#ifndef SNAKE_H
#define SNAKE_H

#include <colors.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define SNAKE_HEAD 'h'
#define SNAKE_TAIL 't'
#define FOOD 'f'

#define WIDTH 24
#define HEIGHT 32
#define SIZE 32

typedef struct Point{
    int x;
    int y;
}Point;

typedef struct player{
    Point head;
    Point body[WIDTH*HEIGHT];
    int move;
    int gender; //rosa o celeste
    char character;
    int lenght;
    int flag;
} player;

int startGame(int players);
void paintBackground(char board[HEIGHT][ WIDTH], player * player);
void singlePlayer();
void gameFunction(char board[HEIGHT][WIDTH], player * player);
void action(char board[HEIGHT][WIDTH], player * playerONE, int * gameEnded);
void generateFood(char board[HEIGHT][WIDTH]);
#endif