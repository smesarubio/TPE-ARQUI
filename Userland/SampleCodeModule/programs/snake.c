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

void paintBackground(char board[HEIGHT][WIDTH]){
    int colorToPrint;
    int i,j;
    for (i = 0; i<32; i++){
        for(j = 0; j<24; j++){
            if (1){
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

void singlePlayer(){
    char board[32][24];
    gameFunction(board);
    gameEnded = 0;
    paintBackground(board);
    
    while (1){
        continue;
    }
    clearSc();
}

void gameFunction(char board[HEIGHT][WIDTH]){ //se tira unos trucos con player
    for (int i = 0; i< HEIGHT; i++){
        for (int j=0; j<WIDTH; j++)
            board[i][j] = ' ';
    }
}
