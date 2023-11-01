#include <libc.h>
#include <snake.h>



int gameEnded;

int startGame(int players){
    clearSc(); //ver que hace
    int valid = 1;  
    switch(players){
        case 1:
            singlePlayer();
            valid = 0;
            break;
        default:
            valid = 0;
            break;
    }
    return valid;
}

void paintBackground(char board[HEIGHT][WIDTH], player * player){
    int colorToPrint;
    for (int i = 0; i<HEIGHT; i++){
        for(int j = 0; j<WIDTH; j++){
            if (board[i][j] == ' '){
                if ((i+j) % 2 == 0){
                   colorToPrint = LIGHT_BACKGROUND;
                }else {
                    colorToPrint = DARK_BACKGROUND;
                }
            }else if (board[i][j] == SNAKE_HEAD){
                colorToPrint = player->gender;
            }
            drawSquare(SIZE, i*SIZE, j*SIZE, colorToPrint);
        }
    }
}

void clearPixel(char board[HEIGHT][WIDTH], int i, int j){
    board[i][j] = ' ';
}

void singlePlayer(){
    char board[HEIGHT][WIDTH];
    gameEnded = 0;
    player playerONE;
    gameFunction(board, &playerONE);
    paintBackground(board,&playerONE);
    while (!gameEnded){
        handleInput(&playerONE);
        action(&playerONE);
        //updateBackground(board, &playerONE);
        paintBackground(board, &playerONE);
    }
    clearSc();
}

void handleInput(player * playerONE){
    char move;
    move = getChar();
    playerONE->move = move;
    return;
}

void action(player* playerONE){

    Point prevHead = playerONE->head;
    switch (playerONE->move) {
        case UP:
            playerONE->head.y--;
            break;
        case DOWN:
            playerONE->head.y++;
            break;
        case LEFT:
            playerONE->head.x--;
            break;
        case RIGHT:
            playerONE->head.x++;
            break;
    }

    for (int i = 0; i < playerONE->lenght; i++) {
        Point temp = playerONE->body[i];
        playerONE->body[i] = prevHead;
        prevHead = temp;
    }
}

void updateBackground(char board[HEIGHT][WIDTH], player * playerONE){
    board[playerONE->head.y][playerONE->head.x] = SNAKE_HEAD;
    for (int i=0; i<playerONE->lenght; i++){
        board[playerONE->body[i].y][playerONE->body[i].x] = SNAKE_HEAD;
    }
}

void gameFunction(char board[HEIGHT][WIDTH], player * player){

    player->head.x = WIDTH/2;
    player->head.y = HEIGHT/2;
    player->move = UP;
    player->gender = COMP1;
    player->character = SNAKE_HEAD;
    player->lenght= 1;

    for (int i = 0; i< HEIGHT; i++){
        for (int j=0; j<WIDTH; j++)
            board[i][j] = ' ';
    }

    board[player->head.x][player->head.y] = player->character;
    for (int k = 0; k < player->lenght; k++){
        board[player->body[k].y][player->body[k].x] = SNAKE_TAIL;
    }
}


