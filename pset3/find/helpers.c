/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#include <stdlib.h>
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values [], int n)
{
    // esli element = iskomomy
    if (values[n/2]==value)
    return true;
    
    if (n<2)
    return false;
    
    //esli element bolshe iskomogo ->pravyu chast' smotrim
    if (values[n/2]>value)
    return search(value,values, n/2);
    
    //esli element menshe iskomogo ->levyu chast smotrim
    if (values[n/2]<value)
    return search(value,&values[n/2+1], n/2-1);

    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
 int x;
 for (int i=1; i<n; i++)
    {
        for (int j=n-1; j>=i; j--)
        {
            if (values[j]<values[j-1]) //tekyshiy element menshe predidushego ->menyaem mestami
            {
                x = values[j-1] ; //bolshee znachenie sohranyaem
                values[j-1] =values[j] ; //menshuy element vlevo
                values[j] = x ; //bolshuy el. vpravo
            }
        }
    }
 
 
}
