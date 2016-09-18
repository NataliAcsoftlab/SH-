#include <stdio.h>
#include <stdlib.h>

int main (void)
{
system("cls");

double potracheno=1.5, razmerButulki=16;
double ounces, butulokZaMin;
int butulokPot, minut;
 printf("Vvedite skolko  minut: ");
 scanf("%d", &minut);
 ounces=potracheno*128;
 butulokZaMin= ounces/razmerButulki;
 butulokPot=butulokZaMin*minut;
 printf("Butulok potracheno: %d \n",butulokPot);

}

