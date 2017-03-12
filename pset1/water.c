#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf ("minutes: ");
    int minutes = GetInt();
    printf ("bottles: %i\n", minutes*12);
}
