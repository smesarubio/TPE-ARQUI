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
        case 2:
            doublePlayers();
            break;
        default:
            valid = 0;
            break;
    }
    return valid;
}

void paintBackground(char board[HEIGHT][WIDTH], player * playerONE, player * playerTWO){
    int colorToPrint;
    for (int i = 0; i<HEIGHT; i++){
        for(int j = 0; j<WIDTH; j++){
            if (board[i][j] == playerONE->character){
                colorToPrint = playerONE->gender;
            }
            else if (playerTWO != NULL && board[i][j] == playerTWO->character){
                colorToPrint = playerTWO->gender;
            }
            else if (board[i][j] == FOOD){
                 colorToPrint = FRUIT;
            }
            else {
                if ((i+j) % 2 == 0){
                    colorToPrint = LIGHT_BACKGROUND;
                }else {
                    colorToPrint = DARK_BACKGROUND;
                }
            }
            drawSquare(SIZE, i*SIZE, j*SIZE, colorToPrint);
        }
    }
}

void Snake(char board[HEIGHT][WIDTH], player * player, int color, char character, char DIR){
    player->head.x = randInt(0, HEIGHT - 1);
    player->head.y = randInt(0, WIDTH - 1);
    // player->head.x = WIDTH/2;
    // player->head.y = HEIGHT/2;
    player->move = DIR;
    player->gender = color;
    player->character = character;
    player->lenght = 1;
    player->flag = 1;
    for (int i = 0; i< HEIGHT; i++){
        for (int j=0; j<WIDTH; j++)
            board[i][j] = ' ';
    }

    for (int i = 0; i<player->lenght; i++){
        player->body[i].x = player->head.x;
        player->body[i].y = player->head.y - (i + 1);
        board[player->body[i].x][player->body[i].y] = character;
    }
    board[player->head.x][player->head.y] = player->character;
}


void action(char board[HEIGHT][WIDTH], player* player, int *gameEnded){
    Point prevHead = player->head;
    switch (player->move) {
        case UP:
        case UP2:
            player->head.y--;
            break;
        case DOWN:
        case DOWN2:
            player->head.y++;
            break;
        case LEFT:
        case LEFT2:
            player->head.x--;
            break;
        case RIGHT:
        case RIGHT2:
            player->head.x++;
            break;
    }
    for (int i = 0; i < player->lenght ; i++){
        if (player->head.x == player->body[i].x && player->head.y == player->body[i].y){
            *gameEnded = 1;
            player->flag = 0;
        }
    }
    if (player->head.x == -1 || player->head.x == HEIGHT || player->head.y == -1 || player->head.y == WIDTH ){
        *gameEnded = 1;
        player->flag = 0;
    }
     if (board[player->head.x][player->head.y] == FOOD){
        player->lenght++; 
        playSound(100);
        mute();
        generateFood(board);
    }
    //actualizo el cuerpo mientras se mueve
    for (int i = player->lenght - 1; i >= 0; i--) {
        player->body[i + 1] = player->body[i];
    }
    // muevo la cabeza
    player->body[0] = prevHead;
    // Update board with new positions
    board[player->head.x][player->head.y] = player->character;
    for (int i = 0; i < player->lenght; i++) {
        board[player->body[i].x][player->body[i].y] = player->character;
    }
    //borro la ultima posicion de la cola
    Point lastMove = player->body[player->lenght];
    board[lastMove.x][lastMove.y] = ' ';
    //paintBackground(board, player, NULL);
}

void UpdateMove(char key, player*player){
    if(key ==  'q' ){
            gameEnded = 1;
    }
    if(!((player->move == UP && key == DOWN) || (player->move == DOWN && key == UP) || (player->move == LEFT && key == RIGHT) || (player->move == RIGHT && key == LEFT))){
        if(key == UP ||key == LEFT ||key == DOWN || key == RIGHT){
            player->move = key;
        }
    }
    
}

void generateFood(char board[HEIGHT][WIDTH]){
    int randy = randInt(0, WIDTH - 1);
    int randx = randInt(0, HEIGHT - 1);
    board[randx][randy] = FOOD;
}

// void gameOver(){
//     printInScreen("GAME OVER", 9);
// }

//SINGLE PLAYER

void singlePlayer(){
    char board[HEIGHT][WIDTH];
    gameEnded = 0;

    player playerONE;
    
    Snake(board, &playerONE, COMP1, SNAKE_ONE, RIGHT);
    generateFood(board);
    paintBackground(board,&playerONE, NULL);
    char key = RIGHT;
    while (!gameEnded){
        key = readChar();
        UpdateMove(key, &playerONE);
        action(board, &playerONE, &gameEnded);
        paintBackground(board, &playerONE, NULL);
        waitSec();
    }
    backToTerm();
    
}

/// 2 PLAYERS

void doublePlayers(){
    char board[HEIGHT][WIDTH];
    gameEnded = 0;

    player playerONE;
    player playerTWO;
    
    Snake(board, &playerONE, COMP1, SNAKE_ONE, RIGHT);
    Snake(board, &playerTWO, COMP2, SNAKE_TWO, DOWN2);
    generateFood(board);
    paintBackground(board,&playerONE, &playerTWO);
    char keyONE = RIGHT;
    char keyTWO = DOWN2;
    while (!gameEnded){
        keyONE = readChar();
        UpdateMove(keyONE, &playerONE);
        action(board, &playerONE, &gameEnded);
        keyTWO = readChar();
        UpdateMove(keyTWO, &playerTWO);
        action(board, &playerTWO, &gameEnded);
        paintBackground(board, &playerONE, &playerTWO);
        waitSec();
    }
    backToTerm();
}