#include <stdio.h>
#include "cs50.h"
#include <string.h>
#include <ctype.h>

int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};  //making the scores array outside of main

int calculate_score(string);

int main(void)
{
    string word1 = get_string("Enter your word Player 1: ");
    string word2 = get_string("Enter your word Player 2: ");  //getting the player inputs

    for (int i = 0; i < strlen(word2); i++)  //converting all inputs to upper
    {
        word1[i] = toupper(word1[i]);
    }

    for (int i = 0; i < strlen(word2); i++)
    {
        word2[i] = toupper(word2[i]);
    }


    int score1 = calculate_score(word1);  //calculating scores
    int score2 = calculate_score(word2);

    if (score1 > score2)  //outputs of the game
    {
        printf("Player 1 is the winner\n");
    }

    else if (score1 < score2)
    {
        printf("Player 2 is the winner\n");
    }

    else
    {
        printf("Its a tie\n");
    }
}


int calculate_score(string word)  //function for calculating scores
{
    int score = 0;

    for (int i = 0, len = strlen(word) ; i < len; i++)
    {
        score = score + scores[(word[i] - 'A')];
    }

    return score;
}
