#include <stdio.h>
#include "cs50.h"

int main(void)
{
    long long cnum = get_long_long("Enter your Credit/Debit Card Number -\n");

    int sum = 0;
    int product = 0;

    // calculating the length of the card number
    int len = 0;
    while (cnum != 0)
    {
        cnum = cnum/10;
        len++;
    }

    for (int i = 0; i < len; i++)
    {
        //isolating the ones place digit
        int alt_pick = cnum - (cnum/10);

        //checking for odd/even run of the loop
        if (((i + 1) / 2) - (i / 2) == 0)
        {
            sum = sum + alt_pick;
        }

        else 
        {
            //checking if the isolated digit*2 is more or than 10
            if ((alt_pick * 2) - 10 >= 0)
            {
                int tens = (alt_pick * 2)/10;
                int ones = (alt_pick * 2) - (tens * 10);
                product = product + tens + ones;
            }
            
            else
            {
                product = product + (alt_pick * 2);
            }
        }
    }

    //verifying validity of the card number
    int verifier = sum + product;

    if (verifier - (verifier / 10) * 10 == 0)
    {
        printf ("Card is valid");
    }

    else 
    {
        printf("Card is fake");
    }

}
