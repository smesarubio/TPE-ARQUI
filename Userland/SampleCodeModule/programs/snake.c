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
<<<<<<< HEAD
    for (int i = 0; i<32; i++){
        for(int j = 0; j<24; j++){
=======
    int i,j;
    for (i = 0; i<32; i++){
        for(j = 0; j<24; j++){
>>>>>>> 1c57567c4713d3577d6092910f34636e77dd2178
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
<<<<<<< HEAD
    char board[16][12];
    gameFunction(board);
    gameEnded = 0;
    paintBackground(board);

=======
    char board[32][24];
    gameFunction(board);
    gameEnded = 0;
    paintBackground(board);
    
>>>>>>> 1c57567c4713d3577d6092910f34636e77dd2178
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
