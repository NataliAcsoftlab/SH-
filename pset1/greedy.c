#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <cs50.h>


//using namespace std;

int main (void)
{
float sumaFloat=0;
int suma;
int moneta25=0, moneta10=0, moneta5=0, moneta1=0;

float str=0.0;
bool stroka=true;
printf("O hai! ");
do {                                // proverka stroki 
    if (str<=0) //esli <0 chislo
    {
         printf("How much change is owed?\n");
         stroka=false;  
    }
    else    //esli simvolu vveli
         printf("Retry: ");
         
   str=GetFloat();
    if (str>0)
         stroka=true;
}while(!stroka);
 


sumaFloat=str*100;

suma=round(sumaFloat);

   if(suma/25>0)
   {
    	moneta25=(int) (suma/25);
	    suma=suma-moneta25*25;
   }
   if(suma/10>0)
   {
     	moneta10=ceil(suma/10);
	     suma=suma-moneta10*10;
   }
   if(suma/5>0)
   {
    	moneta5=ceil(suma/5);
	    suma=suma-moneta5*5;
   }
  
   moneta1=suma;

printf("%d\n",moneta1+moneta5+moneta10+moneta25);

}