#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];

//main prototypes
int choosePriority(char *player, char *computer, int order);
void play(char *player, char *computer, int order);

//auxiliary prototypes
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove(char *player);
void easyAiMove(char *computer);
char checkWinner();
void printWinner(char winner, char *player, char *computer);
void cleanBufferStdin(void);

int main(){
    char player, computer;
    int order = 0;

    //creates a seed based on current time
    srand(time(0));
    choosePriority(&player, &computer, order);
    play(&player, &computer, order);
    return 0;
}

int choosePriority(char *player, char *computer, int order){
    printf("Hello, and welcome to TicTacToe!\n");
    printf("Please select if you want to play as 'X' or as 'O'.\n");
    do {
        cleanBufferStdin();
        scanf(" %c", player);
        *player = toupper(*player);
    } while (*player != 'X' && *player != 'O');

    if(*player == 'X'){
        *computer = 'O';
    }
    else{
        *computer = 'X';
    }

    printf("Do you want to go first or second? (after choosing for the first time, it will alternate the playing order.)\n");
    printf("Choose '1' for going first or '2' for going second.\n");
    do {
        cleanBufferStdin();
        scanf("%d", &order);
    } while (order != 1 && order != 2);
    return order;
}

void resetBoard(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = ' ';
        }
    }
}

void printBoard(){
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}

int checkFreeSpaces(){
    int freeSpaces = 9;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] != ' '){
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void play(char *player, char *computer, int order){
    char answer = ' ';

    do {
        char winner = ' ';
        resetBoard();

        if(order == 1){
            while(winner == ' ' && checkFreeSpaces() != 0) {
                printBoard();
                playerMove(player);
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0){
                    break;
                }


                easyAiMove(computer);
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0){
                    break;
                }
            }
        }

        else if(order == 2){
            while(winner == ' ' && checkFreeSpaces() != 0) {
                printBoard();
                easyAiMove(computer);
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0){
                    break;
                }

                playerMove(player);
                winner = checkWinner();
                if(winner != ' ' || checkFreeSpaces() == 0){
                    break;
                }
            }
        }

        printBoard();
        printWinner(winner, player, computer);
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &answer);
        answer = toupper(answer);
    }while(answer == 'Y');
}

void playerMove(char *player){
    int x, y;

    do{
        cleanBufferStdin();
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;
        cleanBufferStdin();
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if(board[x][y] != ' '){
            printf("Invalid move!\n");
        }
        else{
            board[x][y] = *player;
            break;
        }
    } while (board[x][y] != ' ');
}

//This function chooses a square randomly
void easyAiMove(char *computer){
    int x, y;

    do{
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');

    board[x][y] = *computer;
}

char checkWinner(){
    //check rows
    for(int i = 0; i < 3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }

    //check columns
    for(int i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }

    //check diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }

    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }
    return ' ';
}

void printWinner(char winner, char *player, char *computer){
    if(winner == *player){
        printf("YOU WIN!");
    }

    else if(winner == *computer){
        printf("YOU LOSE!");
    }

    else{
        printf("IT'S A TIE!");
    }
}

void cleanBufferStdin(void){
    int chr;
    do{
        chr = getchar();
    } while (chr != '\n' && chr != EOF);
}