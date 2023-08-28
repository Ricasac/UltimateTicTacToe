#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

char board[3][3];

void choosePriority(char *player, char *AI);
void resetBoard();
void printBoard();

int main() {
    char player, AI;

    choosePriority(&player, &AI);
    resetBoard();
    printBoard();
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