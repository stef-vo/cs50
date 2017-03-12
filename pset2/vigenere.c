#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// main function with parameters
int main(int argc, string argv[])
{
    // checking if two arguments were input
        while (argc != 2)
        {
            printf("Try once more. Enter a secret word for encyfering\n");
            return 1;
        }
    
    // getting a secret word
        string s = argv[1];
    
    // checking if secret code s consists only of letters
        for (int  i = 0, n=strlen(s); i<n; i++)
            if ( ! ( isupper(s[i]) || islower(s[i] ) ) )
            {
                printf("Try once more. Enter a secret word consisting only of letters\n");
                return 1;
            }
     
    // input of plain text to be encyfered
        string p = GetString();
    
    
    char c;
    int k, shift = 0;
    
    // encyfering
    for (int i = 0, n = strlen(p); i < n; i++)
        {
            // defining of key k
            c = s[(i-shift) % (strlen(s))];
            if (islower(c))
                k = (int) (c - 'a');
                else
                if (isupper(c))
                    k = (int) (c - 'A');
            
            if (isupper(p[i]))
                c=((p[i]+(k%26))%('Z'+1)%('A')+'A');
                    else
                    if (islower(p[i]))
                        c=((p[i]+(k%26))%('z'+1)%('a')+'a');
                            else
                            {
                                c=p[i];
                                shift++;
                            }
            printf("%c", c);
        }
    
    //make a new line
    printf("\n");
    return 0;
}
