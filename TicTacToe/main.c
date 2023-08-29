#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

char board[3][3];

//main prototypes
void choosePriority(char *player, char *AI);
void play(char *player, char *AI);

//auxiliary prototypes
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove(char *player);
void easyAiMove(char *AI);
char checkWinner();
void printWinner(char winner, char *player, char *AI);

int main(){
    char player, AI;

    choosePriority(&player, &AI);
    play(&player, &AI); //something is wrong here?
    return 0;
}

void choosePriority(char *player, char *AI){
    printf("Hello, and welcome to TicTacToe!\n");
    printf("Please select if you want to play as 'X' or as 'O'.");
    do {
        fflush(stdin);
        scanf(" %c", player);
        *player = toupper(*player);
    } while (*player != 'X' && *player != 'O');

    if(*player == 'X'){
        *AI = 'O';
    }
    else{
        *AI = 'X';
    }
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

void play(char *player, char *AI){
    char answer = ' ';
    char winner = ' ';

    do {
        resetBoard();
        while(winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();
            playerMove(player);
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }

            easyAiMove(AI);
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
        }
        printBoard();
        printWinner(winner, player, AI);
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &answer);
        answer = toupper(answer);
    }while(answer == 'Y');
}

void playerMove(char *player){
    int x, y;

    do{
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;
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
void easyAiMove(char *AI){
    int x, y;

    //creates a seed based on current time
    srand(time(0));
    if(checkFreeSpaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = *AI;
    }
    else{
        printWinner(" ");
    }
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

void printWinner(char winner, char *player, char *AI){
    if(winner == *player){
        printf("YOU WIN!");
    }

    else if(winner == *AI){
        printf("YOU LOSE!");
    }

    else{
        printf("IT'S A TIE!");
    }
}