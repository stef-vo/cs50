#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// main function with parameters
int main(int argc, string argv[])
{
    // check if two arguments were input
    while (argc != 2)
        {
            printf("Try once more. Enter only a secret key\n");
            return 1;
        }
    
    // getting a secret code
    int k = atoi(argv[1]);
    
    // check k
    while (k<=0)
    {
            printf("Try once more. Enter only a secret key > 0\n");
            return 1;
    }
    
    // input string p
    string p = GetString();
    
    char c;
    
    // encrypting
    for (int i = 0, n = strlen(p); i < n; i++)
        {
            if (isupper(p[i]))
                c=((p[i]+(k%26))%('Z'+1)%('A')+'A');
                    else
                    if (islower(p[i]))
                        c=((p[i]+(k%26))%('z'+1)%('a')+'a');
                            else
                            c=p[i];
            printf("%c", c);
        }
    
    //make a new line
    printf("\n");
    return 0;
}
