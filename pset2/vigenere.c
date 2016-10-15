#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main (int argc, char** argv)
{
 int k,r=0;
 const int ascii_a=97;
 const int ascii_A=65;
 
 if (argc!=2) //proverka na k-vo argv
 {
   printf("Usage: ./viginere k\n");
   return 1;
 }
 
string kod=argv[1];
for(int i=0;i<strlen(kod);i++)//proverka argumenta na nalichie drygih simvolov krome alfavita
{
  if (((kod[i]>='a')&&(kod[i]<='z'))||((kod[i]>='A')&&(kod[i]<='Z')))
 {}   else
  {
        printf("Usage: ./caesar k\n");
        return 1;
   }
}


printf("plaintext:   ");
string str=get_string();

for(int i=0;i<strlen(str);i++)
{
  
  if ((kod[r]>='a')&&(kod[r]<='z'))
      k=kod[r]-ascii_a;
      else
         k=kod[r]-ascii_A;
      
      
      if ((str[i]>='a')&&(str[i]<='z'))
        {   
            
        //    k=kod[r]-ascii_a;
         if ((str[i]+k)>'z')
             str[i]=(int)('a')+(k-((int)('z')-str[i]))-1; //esli zakonchilsya alfavit -> nachinaem snachala shitat'
         else   
             str[i]+=k;
             r++;
        } 
      else
        {
               if ((str[i]>='A')&&(str[i]<='Z'))
              {
               //   k=kod[r]-ascii_A;
                 if ((str[i]+k)>'Z')
                     str[i]=(int)('A')+(k-((int)('Z')-str[i]))-1;//esli zakonchilsya alfavit -> nachinaem snachala shitat'
                 else
                     str[i]+=k;
                     r++;
              }
        }
   
     if (r==strlen(kod)) 
      r=0;
 }
 
printf("ciphertext:  %s\n",str);
return 0;
}