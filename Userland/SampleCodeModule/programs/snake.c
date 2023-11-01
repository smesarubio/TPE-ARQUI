#include <libc.h>
#include <snake.h>



int gameEnded;

int startGame(int players){
    //clearScSaveBuf(); //ver que hace
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
            if ((i+j) % 2 == 0){
                colorToPrint = LIGHT_BACKGROUND;
            }else {
                colorToPrint = DARK_BACKGROUND;
            }
            if (board[i][j] == SNAKE_HEAD){
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
    int c = 0;
    player playerONE;
    gameFunction(board, &playerONE);
    paintBackground(board,&playerONE);
    char key = RIGHT;
    while (!gameEnded){
        //handleInput(&playerONE);
        //action(&playerONE);
        //updateBackground(board, &playerONE);
        //paintBackground(board, &playerONE);
        key = readChar();
        if(key ==  'q' ){
            gameEnded = 1;
        }
        if(!((playerONE.move == UP && key == DOWN) || (playerONE.move == DOWN && key == UP) || (playerONE.move == LEFT && key == RIGHT) || (playerONE.move == RIGHT && key == LEFT))){
            if(key == 'w' ||key == 'a' ||key == 's' || key == 'd'){
                playerONE.move = key;
            }
        }
        waitSec();
        move(&playerONE);
    }
    backToTerm();
    
}

void move(player * playerOne){
    int current_hx = playerOne->head.x;
    int current_hy = playerOne->head.y;
    drawSquare(SIZE, current_hx*SIZE, current_hy*SIZE, ERROR);
    switch (playerOne->move) {
        case UP:
            playerOne->head.y--;
            break;
        case DOWN:
            playerOne->head.y++;
            break;
        case LEFT:
            playerOne->head.x--;
            break;
        case RIGHT:
            playerOne->head.x++;
            break;
    }
    drawSquare(SIZE, playerOne->head.x * SIZE,playerOne->head.y * SIZE, ERROR);
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
    player->move = RIGHT;
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




