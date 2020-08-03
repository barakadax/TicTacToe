#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#define TABLESIZE 3

void incorrectInput(char *sentence) {   //Incase if incorrect input
    char ch = '\n';
    printf("%s", sentence);
    while (ch = getchar() != '\n' && ch != EOF) {};     //Cleans the buffer from input
    Sleep(3000);
    system("cls");
}//O(N)

bool pickXO(double picking, char *pickedValue, char *computerValue) {   //Put values for each player
    if (picking >= 0) {
        *pickedValue = 'X';
        *computerValue = 'O';
    }
    else {
        *pickedValue = 'O';
        *computerValue = 'X';
    }
    return false;
}//O(1)

void printTable(char table[TABLESIZE][TABLESIZE]) {     //Prints the XO table
    for (unsigned int rows = 0; rows < TABLESIZE; rows -= -1) {
        for (unsigned int columns = 0; columns < TABLESIZE; columns -= -1)
            printf("| %c ", table[rows][columns]);
        printf("|\n");
    }
}//O(N**2)

void getWhoStart(unsigned int correction, double *turn) {    //Player pick if yo start or not
    system("cls");
    system("color b");
    while (true) {
        printf("Please write down if you want to start first or let the computer start the match\n");
        printf("(write a possitive number if you want to start, negative number for the computer to start)\nAnswer: ");
        correction = scanf("%lf", turn);
        if (correction != 1)
            incorrectInput("\nPlease type down only numbers.\nPlease wait for auto restart.");
        else
            break;
    }
    if (*turn >= 0)
        *turn = 1;
    else
        *turn = 0;
}//O(N)

void getWhoXorO(unsigned int correction, double picking, char *pickedValue, char *computerValue) {   //Picking which side is X & who is O
    system("cls");
    bool flag = true;
    while (flag) {
        printf("What do you want to play as O/X?\n");
        printf("(write a possitive number for \"X\", write a negative number for \"O\"\nAnswer: ");
        correction = scanf("%lf", &picking);
        if (correction != 1)
            incorrectInput("\nPlease type down only numbers.\nPlease wait for auto restart.");
        else
            flag = pickXO(picking, pickedValue, computerValue);
    }
    system("color d");
}//O(N)

void changeTable(char pickedValue, char computerValue, char real_spot, double *turn, char table[TABLESIZE][TABLESIZE]) {
    for (unsigned int scan_rows = 0; scan_rows < TABLESIZE; scan_rows -= -1) {                  //Checking for real_spot on the table & putting
        for (unsigned int scan_columns = 0; scan_columns < TABLESIZE; scan_columns -= -1) {     //correct value of player in that index
            if (table[scan_rows][scan_columns] == real_spot) {
                if (*turn == 1)
                    table[scan_rows][scan_columns] = pickedValue;
                else if (*turn == 0)
                    table[scan_rows][scan_columns] = computerValue;
            }
        }
    }
    *turn = (!*turn);     //Changes so the other player gets a turn
}//O(N**2)

unsigned int scenarioEvent(char table[TABLESIZE][TABLESIZE]) {
    if ((table[0][0] == table[0][1]) && (table[0][0] == table[0][2])) //breaking everything if someone won, first row break
        return 1;
    else if ((table[1][0] == table[1][1]) && (table[1][0] == table[1][2])) //second row break
        return 2;
    else if ((table[2][0] == table[2][1]) && (table[2][0] == table[2][2])) //third row break
        return 3;
    else if ((table[0][0] == table[1][0]) && (table[0][0] == table[2][0])) //first column break
        return 4;
    else if ((table[0][1] == table[1][1]) && (table[0][1] == table[2][1])) //second column break
        return 5;
    else if ((table[0][2] == table[1][2]) && (table[0][2] == table[2][2])) //third column break
        return 6;
    else if ((table[0][0] == table[1][1]) && (table[0][0] == table[2][2])) //main diagonal break
        return 7;
    else if ((table[0][2] == table[1][1]) && (table[0][2] == table[2][0])) //antidiagonal break
        return 8;
    return 0;
}//O(1)

void main() {
    srand(time(NULL));
    unsigned int correction = 0, spot = 0, scenario = 0;
    double turn = 0;
    char pickedValue = '0', computerValue = '1', real_spot = '\n', table[TABLESIZE][TABLESIZE] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    getWhoStart(0, &turn);
    getWhoXorO(0, 0, &pickedValue, &computerValue);

    for (unsigned int match_turns = 0; match_turns < TABLESIZE * TABLESIZE; match_turns -= -1) {
        system("cls");
        printf("Turn number %d: \n\n", match_turns + 1);
        printTable(table);

        if (turn == 1) {    //Player picks a spot on the board
            printf("\nPlayers turn\nPick a spot: ");
            correction = scanf("%d", &spot);
            if ((correction != 1) || (spot > 9) || (spot < 1)) {
                incorrectInput("\nPlease type down only numbers between 1-9\nPlease wait for auto restart.");
                --match_turns;
                continue;
            }
        }
        else
            spot = rand() % 9 + 1;

        if ((spot == 1) && (table[0][0] == '1'))    //Because player & computer pick with int type
            real_spot = '1';                        //if spot available & pick was valid it will cahnge the real_spot value
        else if ((spot == 2) && (table[0][1] == '2'))
            real_spot = '2';
        else if ((spot == 3) && (table[0][2] == '3'))
            real_spot = '3';
        else if ((spot == 4) && (table[1][0] == '4'))
            real_spot = '4';
        else if ((spot == 5) && (table[1][1] == '5'))
            real_spot = '5';
        else if ((spot == 6) && (table[1][2] == '6'))
            real_spot = '6';
        else if ((spot == 7) && (table[2][0] == '7'))
            real_spot = '7';
        else if ((spot == 8) && (table[2][1] == '8'))
            real_spot = '8';
        else if ((spot == 9) && (table[2][2] == '9'))
            real_spot = '9';
        else {
            printf("\nSpot is already filled, please wait for this turn to auto restart. ");
            for (int dots = 0; dots < rand() % 6 + 3; dots++) {
                Sleep(rand() % 300 + 200);
                printf(". ");
            }
            Sleep(rand() % 300 + 200);
            --match_turns;
            system("cls");
            continue;
        }
        changeTable(pickedValue, computerValue, real_spot, &turn, table);
        scenario = scenarioEvent(table);
        if (scenario != 0)
            break;
    }

    system("cls");
    system("color 7");
    printf("Matched ended:\n\n");
    printTable(table);
    if ((scenario == 1) || (scenario == 4) || (scenario == 7)) {
        if (table[0][0] == pickedValue)
            printf("\nYou won!.\n");
        else
            printf("\nComputer won!.\n");
    }
    else if ((scenario == 2) || (scenario == 5) || (scenario == 8)) {
        if (table[1][1] == pickedValue)
            printf("\nYour won!.\n");
        else
            printf("\nComputer won!.\n");
    }
    else if ((scenario == 3) || (scenario == 6)) {
        if (table[2][2] == pickedValue)
            printf("\nYour won!.\n");
        else
            printf("\nComputer won!.\n");
    }
    else
        printf("\nTie!!!\nNobody wins this match ^^\n");
/*     (\____/) 
       (•(ㅅ)•)      
   　＿ノ ヽ ノ＼＿    
  `/　`/ ⌒Ｙ⌒ Ｙ　ヽ  
  ( 　(三ヽ人　 /　　 | 
   |　ﾉ⌒＼ ￣￣ヽ　 ノ
   ヽ＿＿＿＞､＿＿_／
　　   ｜( 王 ﾉ〈 
　　   / ﾐ`ー―彡 \
　　  /  ╰    ╯  /
code by Barakadax*/
}