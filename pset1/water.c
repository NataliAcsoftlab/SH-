#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main (void)
{
double potracheno=1.5, razmerButulki=16;
double ounces, butulokZaMin;
int butulokPot, minut;
bool chislo=true;
  do{
     printf("Minutes: ");
     minut=GetInt();
     if (isdigit(minut))
       chislo=true;
      else chislo = false;
  }while(chislo);
 
 ounces=potracheno*128;
 butulokZaMin= ounces/razmerButulki;
 butulokPot=butulokZaMin*minut;

 printf("Buttles: %d \n",butulokPot);

}

