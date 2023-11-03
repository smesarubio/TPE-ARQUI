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

void Snake(char board[HEIGHT][WIDTH], player * player, int color, char character, char DIR, int posX, int posY){
    player->head.x = posX;
    player->head.y = posY;
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
}

void UpdateMove(char key, player*player, char moveUp, char moveDown, char moveLeft, char moveRight ){
     if(key ==  'q' ){
            gameEnded = 1;
        }
        if(!((player->move == moveUp && key == moveDown) || (player->move == moveDown && key == moveUp) || (player->move == moveLeft && key == moveRight) || (player->move == moveRight && key == moveLeft))){
            if(key == moveUp ||key == moveLeft ||key == moveDown || key == moveRight){
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
    int posX = WIDTH/2;
    int posY = HEIGHT/2;
    Snake(board, &playerONE, COMP1, SNAKE_ONE, RIGHT, posX, posY);
    generateFood(board);
    paintBackground(board,&playerONE, NULL);
    char key = RIGHT;
    while (!gameEnded){
        key = readChar();
        UpdateMove(key, &playerONE, UP, DOWN, LEFT, RIGHT);
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
    int posX = WIDTH/2;
    int posY = HEIGHT/2;
    Snake(board, &playerONE, COMP1, SNAKE_ONE, RIGHT, posX, posY);
    posX = HEIGHT/2;
    posY = WIDTH/2;
    Snake(board, &playerTWO, COMP2, SNAKE_TWO, DOWN2, posX, posY);
    generateFood(board);
    paintBackground(board,&playerONE, &playerTWO);
    char keyONE = RIGHT;
    char keyTWO = DOWN2;
    while (!gameEnded){
        keyONE = readChar();
        UpdateMove(keyONE, &playerONE, UP, DOWN, LEFT, RIGHT);
        action(board, &playerONE, &gameEnded);
        keyTWO = readChar();
        UpdateMove(keyTWO, &playerTWO, UP2, DOWN2, LEFT2, RIGHT2);
        action(board, &playerTWO, &gameEnded);
        paintBackground(board, &playerONE, &playerTWO);
        waitSec();
    }
    backToTerm();
}