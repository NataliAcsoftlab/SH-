#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
int main (void)
{
float suma=0;
int moneta25=0, moneta10=0, moneta5=0, moneta1=0;
char str[100];
bool stroka=true;

do {                                // vvod stroki 
    printf("Vvedite sumu: ");
    scanf("%s", str);
    for(int r=0; r<strlen(str); r++) //proverka - stroka chislo?
    {
       if (isdigit(str[r])||(str[r]=='.'))
        {
           stroka=false;
        }
        else
        {
           stroka=true;
           r=strlen(str);
        }
    }
}while(stroka);
 
suma=strtof(str,NULL);//perevod stroki v chislo
suma=suma*100;
  
   if(suma/25>0)
   {
    	moneta25=suma/25;
	    suma=suma-moneta25*25;
   }
   if(suma/10>0)
   {
     	moneta10=suma/10;
	     suma=suma-moneta10*10;
   }
   if(suma/5>0)
   {
    	moneta5=suma/5;
	    suma=suma-moneta5*5;
   }
   moneta1=suma;
printf("Monet po 25 kop: %d\n",moneta25);
printf("Monet po 10 kop: %d\n",moneta10);
printf("Monet po 5 kop: %d\n",moneta5);
printf("Monet po 1 kop: %d\n",moneta1);
printf("Vsego monet: %d\n",moneta1+moneta5+moneta10+moneta25);

}