#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
string str=get_string();

    for(int r=0; r<strlen(str); r++) 
    {
      if(((str[r-1]==' ')||(r==0))&&(str[r]!=' '))
      {
          if(str[r]>='a'&&str[r]<='z')
        printf("%c",str[r]-=32); //po kody ASCII tabl otnimau esli malenkaya bykva
        else 
        printf("%c",str[r]);
      }
   }
   printf("\n");
}