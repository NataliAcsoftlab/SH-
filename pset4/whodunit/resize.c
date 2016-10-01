#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main (int argc, char** argv)
{
    int k;
 if (argc!=2) //proverka na k-vo argv
 {
   printf("Usage: ./caesar k\n");
   return 1;
 }
 
if (((int)(argv[1]))<0)
{
  printf("Vedene vid'emne chislo"); 
  return 1;
}
return 0;
}