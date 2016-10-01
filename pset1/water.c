#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
double potracheno=1.5, razmerButulki=16;
double ounces, butulokZaMin;
int butulokPot, minut;
 printf("Minutes: ");
 scanf("%d", &minut);
 ounces=potracheno*128;
 butulokZaMin= ounces/razmerButulki;
 butulokPot=butulokZaMin*minut;
 printf("Buttles: %d \n",butulokPot);

}

