/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // binary search
    if (n <= 0) return false;
    
    int left = 0; // position of left bounce
    int right = n-1; // position of right bounce
    
    while (left <= right)
    {
       int middle = (left + right)/2; // middle element
    
    if (value < values[middle]) // search in the left half
        right = middle - 1; // change the right bounce 
    else
        if (value > values[middle]) // search in the right half
            left = middle + 1; // change the left bounce
        else return true; // the value found 
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i = 1, j = 2;
    while (i < n)
    {
        if (values[i - 1] <= values[i])
            i = j++;
        else
        {
            // swapping
            int b = values[i - 1];
            values[i - 1] = values[i];
            values[i--] = b;
            if (!i) i = 1;
        }
    }
}