#include <stdio.h>
#include "cs50.h"

//make a configurable mario pyramid!

int get_height(void);
void print_pyramid(int height);

int main(void)
{
    int n = get_height();
    print_pyramid(n);   
}


//get height of pyramid
int get_height(void)
{
    int n; 
    do
    {
    n = get_int("Enter the height of your pyramid ->> ");
    } 
    while (n < 1);
    return n;
}

//print pyramid
void print_pyramid(int height)
{
    for (int h = 0; h < height ; h++)
    {
        // gaps on left 'g'
        for (int g = ((height-1) - h); g > 0; g--)
        {
            printf(" ");
        }

        //blocks on left 'l'
        for (int l = 0; l < (h+1); l++)
        {
            printf("#");
        }
        
        //gaps bw the pyramids
        printf("  ");
        
        //blocks on the right 'r'
        for (int r = 0; r < (h+1); r++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}    