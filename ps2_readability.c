#include <stdio.h>
#include "cs50.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

int main (void)
{
    string input= get_string("Enter your text here (and find out its complexity) - \n");

    char phrase[10000];

    strcpy (phrase, input);

    int i = 0;
    int words = 1;  //beginning words var with 1 since last word would not end with a space
    int letters = 0;
    int sentences = 0;

    while (phrase[i] != '\0')
    {
        if (phrase[i] == ' ')  //counting the number of "words"
        {
            words +=1;
        }

        else if ((phrase[i] >= 'a' && phrase[i] <= 'z') || (phrase[i] >= 'A' && phrase[i] <= 'Z'))  //counting the number of "letters"
        {
            letters +=1;
        }

        else if ((phrase[i] == '.') || (phrase[i] == '!') || (phrase[i] == '?'))  //counting the number of "sentences"
        {
            sentences +=1;
        }

        i++;
    }

    float L = (( (float) letters / words) * 100);  //casting letters, words and sentences to float so that L and S have accurate decimals
    float S = (( (float) sentences / words) * 100); 

    float CL_Index = 0.0588 * L - 0.296 * S - 15.8;  //printing the coleman-liau index

    if (CL_Index < 1)
    {
        printf ("Before Grade 1\n");
    }

    else if (CL_Index >= 1 && CL_Index <= 16)
    {
        CL_Index = roundf(CL_Index);  //using the roundfloat function from math.c stdlib

        printf ("Grade %i\n", (int) CL_Index);  //typecasting for clean output
    }

    else
    {
        printf("Grade 16+\n");
    }
}
