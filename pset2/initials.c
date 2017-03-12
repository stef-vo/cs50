#include <cs50.h>
#include <stdio.h>
#include <string.h>

// declare function to convert to upper letters
void upper(char);

// main function
int main(void)
{
    // get string
    string s = GetString();
    
    // convert the first letter of the string to upper letter
    upper(s[0]);
    
    // convert other letters
    for (int i = 1, n=strlen(s); i<n; i++)
        if (s[i-1] == ' ')
           upper(s[i]);
           
    // new line
    printf("\n");
}

// function to convert to upper letters
void upper(char c)
{
    if (c>='a' && c<='z')
        printf("%c", c + 'A' - 'a');
    else
        printf("%c", c);
}