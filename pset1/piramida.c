#include <stdio.h>
#include <stdlib.h>
int main (void)
{
int vusota=0;
 while ((vusota<1)||(vusota>23))
 {
 printf("Vvedite vusotu piramidu ot 1 do 23: ");
 scanf("%d", &vusota);
  }
 for (int i=1; i<=vusota; i++)
 {
	for(int j=vusota;j>i;j--)  printf(" ");
	for (int s=0;s<2;s++)
	{
		for (int a=0;a<i;a++)	printf("#");
		printf(" ");
	}
	printf("\n");
 }

}