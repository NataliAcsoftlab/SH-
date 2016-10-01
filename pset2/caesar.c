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

if (atoi(argv[1])>26)  //esli >26 -> vuchislayem poziciu
     k=(int)atoi(argv[1])%26;
else
     k = (int)atoi(argv[1]);
     

printf("Plaintext:   ");
string str=get_string();

for(int i=0;i<strlen(str);i++)
{
  
  if ((str[i]>='a')&&(str[i]<='z'))
  {
     if ((str[i]+k)>'z')
         str[i]=(int)('a')+(k-((int)('z')-str[i]))-1; //esli zakonchilsya alfavit -> nachinaem snachala shitat'
     else   
         str[i]+=k;
  }
  
   if ((str[i]>='A')&&(str[i]<='Z'))
  {
     if ((str[i]+k)>'Z')
         str[i]=(int)('A')+(k-((int)('Z')-str[i]))-1;//esli zakonchilsya alfavit -> nachinaem snachala shitat'
     else
         str[i]+=k;
  }
}

printf("ciphertext:  %s\n",str);
return 0;
}