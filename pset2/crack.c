#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <stdlib.h>
#define _XOPEN_SOURCE
#include <unistd.h>

int main (int argc, char** argv)
{
 char parol[5];
 char maska[2];
 char bukva1='A';
 char bukva2='A';
 char bukva3='A';
 char bukva4='A';
 char Zbukva='z';
 
 string kod=argv[1];//zashufrovanuy parol ->kod
 strncpy(maska,kod,2);//pervuh 2 simvola so stroki ->maska
 
 if (argc!=2) //proverka na k-vo argv
 {
   printf("Usage: ./crack hash\n");
   return 1;
 }

memset(parol, 0, sizeof(parol)); //obnulenie
 
  do
   {
     bukva2='A';
     do
      {
        bukva3='A';
        do
         {
            bukva4='A';
            do
             {
                parol[0]=bukva1;
                parol[1]=bukva2;
                parol[2]=bukva3;
                parol[3]=bukva4;
                parol[4]='\0';
                string Cript=crypt(parol, maska);//zashufrovka parolya

                           if (strcmp(Cript,kod)==0) //zashufrovani paroli spivpadaut?
                              {
                               printf("Password:  %s\n",parol);
                               return 0;
                              }
               bukva4++;
              }while(bukva4<=Zbukva);
          bukva3++;
         }while(bukva3<=Zbukva);
       bukva2++;
      }while(bukva2<=Zbukva);   
    bukva1++;
   }while(bukva1<=Zbukva);


printf("Parol ne nayden!\n");
return 0;
}