#include <stdio.h>
#include "cs50.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string argv[])
{
    
    if(argc != 2)  //error case of extra or absent args
    {
        printf("Usage Direction: Give a 26 alphabet Key for your Substitution Cipher without spaces. Only input the Key with the run command \n");
        return 1;
    }


    char key[30];  //creating key
    int keylen = strlen(argv[1]);    
    key[keylen] = '\0';  //adding delimiter

    
    if(keylen != 26)  //error case where the key has more or less than 26 chars
    {
        printf("Your key should contain 26 alphabets each used exactly once\n");
        return 1;
    }
    
    
    for(int j = 0; j < 26; j++)
    {
        if(isalpha(argv[1][j]) == 0)  //error case where the key containts a non-alphabet
        {
            printf("Your key should contain 26 alphabets each used exactly once\n");
            return 1;
        }

        key[j] = toupper(argv[1][j]);  //populating the key string turning the chars in key to allcaps
    }


    for(int k = 0; k < 26; k++)  //error case where key doesn't contain each alphabet exactly once
    {
        for(int m = k + 1; m < 26; m++)
        {
                if (key[k] == key[m])
                {
                    printf("Your key should contain each alphabet exactly once. \n");
                    return 1;
                }
        }
       
    }

    string plaintext = get_string("plaintext: ");   //getting plaintext
    int ptlen = strlen(plaintext);

    char ciphertext[ptlen + 1];  //creating ciphertext

    for(int p = 0; p < ptlen; p++)
    {
        if(isalpha(plaintext[p]))
        {
            if(isupper(plaintext[p]))  //uppercase
            {
                ciphertext[p] = key[plaintext[p] - 'A'];
            }
            else  //lowercase
            {
                ciphertext[p] = tolower(key[plaintext[p] - 'a']);
            }
        }
        else  //punctuations
        {
            ciphertext[p] = plaintext[p];
        }
    }


    ciphertext[ptlen] = '\0';  //done creating ciphertext - adding delimiter

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
