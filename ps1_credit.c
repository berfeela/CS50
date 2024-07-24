#include <stdio.h>
#include "cs50.h"

int main(void)
{
    long long cnum = get_long_long("Enter your Credit/Debit Card Number -\n");

    long long cn_len = cnum;
    long long cn_typ = cnum;

    int sum = 0;
    int product = 0;

    //calculating the length of the card number
    int len = 0;
    while (cn_len != 0)
    {
        cn_len = cn_len/10;
        len++;
    }

    for (int i = 0; i < len; i++)
    {
        //isolating the ones place digit
        int alt_pick = cnum - ((cnum / 10) * 10);
        cnum = cnum / 10;

        //checking for odd/even run of the loop
        if (((i + 1) / 2) - (i / 2) == 0)
        {
            sum = sum + alt_pick;
        }

        else 
        {
            //checking if the isolated digit * 2 is more than 10
            if ((alt_pick * 2) - 10 >= 0)
            {
                int tens = (alt_pick * 2) / 10;
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
        printf ("Card is valid.\n");

        // determining whether Mastercard, Visa or Amex
        for (int j = 0; j < (len - 2); j++)
        {
            cn_typ = cn_typ/10;
        }

        //cn_typ is now equal to the last 2 digits of the card number
        if ( len == 15 && (cn_typ == 34 || cn_typ == 37))
        {
            printf ("American Express");
        }

        else if ( len == 16 && (cn_typ == 51 || cn_typ == 52 || cn_typ == 53 || cn_typ == 54 || cn_typ == 55))
        {
            printf ("MasterCard");
        }

        else if ((len == 13 || len == 16) && (cn_typ/10 == 4))
        {
            printf ("VISA");
        }

        else
        {
            printf ("Card invalid");
        }
    }

    else 
    {
        printf("Card is fake.\n");
    }
}
