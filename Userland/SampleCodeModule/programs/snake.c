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
            if (board[i][j] == SNAKE_HEAD || board[i][j] == SNAKE_TAIL){
                colorToPrint = player->gender;
            }
            else if (board[i][j] == FOOD){
                 colorToPrint = COMP2;
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

void clearPixel(char board[HEIGHT][WIDTH], int i, int j){
    board[i][j] = ' ';
}

void singlePlayer(){
    char board[HEIGHT][WIDTH];
    gameEnded = 0;

    player playerONE;
    
    gameFunction(board, &playerONE);
    generateFood(board);
    paintBackground(board,&playerONE);
    char key = RIGHT;
    while (!gameEnded){
        key = readChar();
        if(key ==  'q' ){
            gameEnded = 1;
        }
        if(!((playerONE.move == UP && key == DOWN) || (playerONE.move == DOWN && key == UP) || (playerONE.move == LEFT && key == RIGHT) || (playerONE.move == RIGHT && key == LEFT))){
            if(key == UP ||key == LEFT ||key == DOWN || key == RIGHT){
                playerONE.move = key;
            }
        }
        action(board, &playerONE, &gameEnded);
        waitSec();
    }
    backToTerm();
    
}

void move(char board[HEIGHT][WIDTH], player * playerOne){
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

void action(char board[HEIGHT][WIDTH], player* playerONE, int *gameEnded){
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
    if (playerONE->head.x == - 1 || playerONE->head.x == WIDTH || playerONE->head.y == - 1 || playerONE->head.x == HEIGHT ){
        *gameEnded = 1;
        playerONE->flag = 0;
    }
     if (board[playerONE->head.x][playerONE->head.y] == FOOD){
        playerONE->lenght++; 
        generateFood(board);
    }
    //actualizo el cuerpo mientras se mueve
    for (int i = playerONE->lenght - 1; i >= 0; i--) {
        playerONE->body[i + 1] = playerONE->body[i];
    }
    // muevo la cabeza
    playerONE->body[0] = prevHead;
    // Update board with new positions
    board[playerONE->head.x][playerONE->head.y] = playerONE->character;
    for (int i = 0; i < playerONE->lenght; i++) {
        board[playerONE->body[i].x][playerONE->body[i].y] = SNAKE_TAIL;
    }
    //borro la ultima posicion de la cola
    Point lastMove = playerONE->body[playerONE->lenght];
    board[lastMove.x][lastMove.y] = ' ';
    paintBackground(board, playerONE);
}


void gameFunction(char board[HEIGHT][WIDTH], player * player){

    player->head.x = WIDTH/2;
    player->head.y = HEIGHT/2;
    player->move = RIGHT;
    player->gender = COMP1;
    player->character = SNAKE_HEAD;
    player->lenght = 1;
    player->flag = 1;
    for (int i = 0; i< HEIGHT; i++){
        for (int j=0; j<WIDTH; j++)
            board[i][j] = ' ';
    }

    for (int i = 0; i<player->lenght; i++){
        player->body[i].x = player->head.x;
        player->body[i].y = player->head.y - (i + 1);
        board[player->body[i].x][player->body[i].y] = SNAKE_TAIL;
    }
    board[player->head.x][player->head.y] = player->character;
}

void generateFood(char board[HEIGHT][WIDTH]){
    int randy = randInt(0, WIDTH - 1);
    int randx = randInt(0, HEIGHT - 1);
    board[randx][randy] = FOOD;
}


