#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // input height of the half-pyramid
    do
    {
        printf ("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23); // end of the loop
    
    // printing out spaces and hashes using loops
    for (int i = 0; i < height; i++)
    {
        for (int j = height - i -1; j > 0; j--)
            printf (" ");
        for (int j = 0; j < i+2; j++)
            printf ("#");
        printf ("\n");
    }
}
