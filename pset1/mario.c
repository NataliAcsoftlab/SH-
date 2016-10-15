#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <cs50.h>

int main (void)
{
  char mas[100]={0};
  int vusota=0;
  int num=0;

   do 
   {
       if (vusota <= 0 || vusota >= 24)
       {
           printf("Height ot 1 do 23: ");
           vusota=GetInt();
       }
       else
        { 
         
            vusota = GetInt();
        }  
        
         if (vusota==0)
                return 0;
                
     } while ((vusota<=0)||(vusota>23));
     


     for (int i=1; i<=vusota; i++)
     { 
        	for(int j=vusota;j>i;j--) 
        	{
        	    mas[num]=' ';
        	    num++;
        	}
    
    		for (int a=0;a<i;a++)
    		{
    		    mas[num]='#';
    		    num++;
    		}
    		
    		mas[num]=' ';
    		num++;
    		
    		mas[num]=' ';
    		num++;
    		
    		for (int a=0;a<i;a++)
    		{
    		    mas[num]='#';
    		    num++;
    		}
    
    // 		for(int i1=0;i1<strlen(mas);i1++)
    //         	printf("%c",mas[i1]);
    	        
    // 	        printf("\n");
    	puts(mas);
    	num=0;
    	
      }
   

}