#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#define TABLESIZE 3

void main() {
    srand(time(NULL));
    int correction = 0, flag = 1, spot = 0, who_plays = 0, scenario = 0;
    double turn = 0, picking = 0;
    char ch, picked_value = 'N', computer_value = 'A', real_spot = '\n', table[TABLESIZE][TABLESIZE] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    system("cls");
    system("color b");
    while (flag == 1) {     //Leting player choose to start or not
        printf("Please write down if you want to start first ot let the computer start the match\n");
        printf("(write a possitive number if you want to start, negative number for the computer to start)\nAnswer: ");
        correction = scanf("%lf", &turn);
        if (correction != 1) {
            printf("\nPlease type down only numbers.\nPlease wait for auto restart.");
            while (ch = getchar() != '\n' && ch != EOF) {};
            Sleep(3000);
            system("cls");
        }
        else
            flag = 0;
    }
    if (turn >= 0)      //Pick starter
        who_plays = 1;
    else
        who_plays = 0;
    flag = 1;
    system("cls");
    while (flag == 1) {
        printf("What do you want to play as O/X?\n");   //Player choose from X or O which he wants to play as
        printf("(write a possitive number for \"X\", write a negative number for \"O\"\nAnswer: ");
        correction = scanf("%lf", &picking);
        if (correction != 1) {
            printf("\nPlease type down only numbers.\nPlease wait for auto restart.");
            while (ch = getchar() != '\n' && ch != EOF) {};
            Sleep(3000);
            system("cls");
        }
        if ((correction == 1) && (picking >= 0)) {
            picked_value = 'X';
            computer_value = 'O';
            flag = 0;
        }
        else if ((correction == 1) && (picking < 0)) {
            picked_value = 'O';
            computer_value = 'X';
            flag = 0;
        }
    }
    system("cls");
    system("color d");
    for (int match_turns = 0; match_turns < TABLESIZE * TABLESIZE; match_turns++) {
        system("cls");
        printf("Turn number %d: \n\n", match_turns + 1);
        for (unsigned int rows = 0; rows < TABLESIZE; rows -= -1) {     //Shows the table on screen
            for (unsigned int columns = 0; columns < TABLESIZE; columns -= -1)
                printf("| %c ", table[rows][columns]);
            printf("|\n");
        }
        if (who_plays == 1) {
            printf("\nPlayers turn\nPick a spot: ");    //Player choose where to put his mark in
            correction = scanf("%d", &spot);
            if ((correction != 1) || (spot > 9) || (spot < 1)) {
                printf("Please type down only numbers between 1-9\nPlease wait for auto restart.");
                while (ch = getchar() != '\n' && ch != EOF) {};
                --match_turns;
                Sleep(3000);
                system("cls");
                continue;
            }
        }
        else                                             //computer choose where to put his mark in
            spot = rand() % 9 + 1;
        if ((spot == 1) && (table[0][0] == '1'))
            real_spot = '1';
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
            for(int dots = 0; dots < 4; dots++){
                Sleep(500);
                printf(". ");
            }
            Sleep(500);
            --match_turns;
            system("cls");
            continue;
        }
        for (int scan_rows = 0; scan_rows < TABLESIZE; scan_rows++) {                    //Putting mark in choosen cell in the table
            for (int scan_columns = 0; scan_columns < TABLESIZE; scan_columns++) {
                if (table[scan_rows][scan_columns] == real_spot) {
                    if (who_plays == 1) 
                        table[scan_rows][scan_columns] = picked_value;
                    else if (who_plays == 0)
                        table[scan_rows][scan_columns] = computer_value;
                }
            }
        }
        who_plays = (!who_plays);                                                   //Switching turn
        if ((table[0][0] == table[0][1]) && (table[0][0] == table[0][2])){          //breaking everything if someone won, first row break
            scenario = 1;
            break;
        }
        else if ((table[1][0] == table[1][1]) && (table[1][0] == table[1][2])){     //second row break
            scenario = 2;
            break;
        }
        else if ((table[2][0] == table[2][1]) && (table[2][0] == table[2][2])){     //third row break
            scenario = 3;
            break;
        }
        else if ((table[0][0] == table[1][0]) && (table[0][0] == table[2][0])){     //first column break
            scenario = 4;
            break;
        }
        else if ((table[0][1] == table[1][1]) && (table[0][1] == table[2][1])){     //second column break
            scenario = 5;
            break;
        }
        else if ((table[0][2] == table[1][2]) && (table[0][2] == table[2][2])){     //third column break
            scenario = 6;
            break;
        }
        else if ((table[0][0] == table[1][1]) && (table[0][0] == table[2][2])){    //main diagonal break
            scenario = 7;
            break;
        }
        else if ((table[0][2] == table[1][1]) && (table[0][2] == table[2][0])){    //antidiagonal break
            scenario = 8;
            break;
        }
    }
    system("cls");
    system("color 7");
    printf("Matched ended: \n\n");
    for (int rows = 0; rows < TABLESIZE; rows++) {
        for (int columns = 0; columns < TABLESIZE; columns++)
            printf("| %c ", table[rows][columns]);
        printf("|\n");
    }
    if ((scenario == 1) || (scenario == 4) || (scenario == 7)) {
        if (table[0][0] == picked_value)
            printf("\nYou won!.\n");
        else 
            printf("\nComputer won!.\n");
    }
    else if ((scenario == 2) || (scenario == 5) || (scenario == 8)) {
        if (table[1][1] == picked_value)
            printf("\nYour won!.\n");
        else
            printf("\nComputer won!.\n");
    }
    else if ((scenario == 3) || (scenario == 6)) {
        if (table[2][2] == picked_value)
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