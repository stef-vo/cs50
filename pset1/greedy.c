#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long long quarters=0, dimes=0, nickels=0, pennies=0;
    double change;
    do
    {
        printf ("O hai, how much change is owed: ");
        change = GetDouble();
    }
        while (change < 0);
    
    quarters = (long long)change * 4; // 1 dollar is 4 quarters
    change-=(long long)change; // not dollars, only pennies
    change = change * 100; // convert into pennies
    
    while ((long long)change - 25 >= 0) // while there are quarters
    {
    quarters++; change-=25;
    }
    
    while ((long long)change - 10 >= 0) // while there are dimes
    {
    dimes++; change-=10;
    }

    while ((long long)change - 5 >= 0) // while there are nickels
    {
    nickels++; change-=5;
    }
 
    while ((long long)change - 1 >= 0) // while there are pennies
    {
    pennies++; change-=1;
    }
 
    long long coins = quarters + dimes + nickels + pennies;
    printf ("%llu\n", coins); // output number of coins
}
