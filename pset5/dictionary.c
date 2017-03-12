/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */
#include <ctype.h>
#include <malloc.h>

#include "dictionary.h"

// declare globally a new type "node"
typedef struct node
    {
        bool is_word;
        struct node* children[27];
    }  node;

// making a pointer to a data of type "node"
node* root;


// declare globally a number of words in a dictionary
unsigned int number_of_words;

/**
 * Loads dictionary into memory.  Returns true if successful.
 */
bool load(const char* dictionary)
{
    // dynamically allocate memory for a root node
    root = (node*) malloc (sizeof(node));
    
    if (root == NULL)
    {
        return false;
    }
    
    // initialize the root node
    root->is_word = false;
    for (int i = 0; i < 27; i++)
    {
        
        root->children[i] = NULL;
    }
    
    // open a dictionary file for reading
    FILE*dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not load %s.\n", dictionary);
        return false;
    }
    
    // making two new pointers
    node* current = root;
    node* next = NULL;
    
    // c is  a character from a dictionary
    int c = fgetc(dict);
    
    // while not end of file
    while (c != EOF)
    {
        // if c is an apostrophe character change it
        if (c == '\'')
        {
            c = 'a' + 26;
        }
        
        
        // if we reached end of word in dictionary
        if (c == '\n')
        {
            // then we have written a new word to the struct
            current->is_word = true;
            
            // and number of words increases
            number_of_words++;
            
            current = root;
        }
        else // we haven't reached the end of the word yet
        {
            if (current->children[ c - 'a' ] == NULL)
            {
                // dynamically allocate memory for a new node 
                node* next = (node*) malloc (sizeof(node));
                
                if (next == NULL)
                {
                    return false;
                }
                
                // initialize a new node
                next->is_word = false;
                for (int i = 0; i < 27; i++)
                {
                    
                    next->children[i] = NULL;
                }
                
                // making a new arrow
                current->children[ c - 'a' ] = next;
                
                // tne next node becomes the current one
                current = next;
            }
            else // move to the next node
            {
                current = current->children[ c - 'a' ];
                
            }
            
        }
        
        // read a new character from the dictionary
        c = fgetc(dict);
        
    }    
    
    free(next);
    
    // close the dictionary
    fclose(dict);        
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (number_of_words > 0)
    {
        return number_of_words;
    }
    else
    {
        return 0;
    }
    
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //define word_length - a number of characters in the word
    unsigned int word_length = 0;
    
    for (int i = 0; word[i] != '\0'; i++)
    {
        word_length++;
    }
    
    // the root node becomes the current one
    node* current = root;
    
    if (current == NULL)
    {
        return false;
    }
    
    unsigned int number_of_chars = 0;
    
    // reading characters of the word given
    int i = 0;
    while (word[i] != '\0')
    {
        unsigned int c = word[i];
        
        if ( c == '\'')
        {
            c = 'a' + 26;
        }
        else
        {
            // make a lowercase letter
            c = tolower(c);
        }
        
        // going through the stuct
        if (current->children[c - 'a'] == NULL)
        {
            break; // the word is not in the dictionary
        }
        else
        {
            current = current->children[c - 'a'];
            number_of_chars++;
            i++;
        }
    } // we found number_of_chars
     
    // checking if the word is in the dictionary
    if (number_of_chars == word_length &&  current->is_word == true)    
    {
    
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * A new function
 * to unload node from memory
 */
void unload_node(node* next_node)
{
    
    for(int i = 0; i < 27; i++)
    {
        if(next_node->children[i] != NULL)
        {
            unload_node(next_node->children[i]);
        }
    }
    
    free(next_node);
}



/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // recursion
    unload_node(root);
    return true;
}
