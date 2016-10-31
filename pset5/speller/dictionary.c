/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
 #include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>

#include "dictionary.h"


 typedef struct Node{
    char data[46];
    struct Node *next;
}Node;

 Node *Head=NULL;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
        Node *root = Head;
        char temp[46];
        int len = strlen(word);
        int lenSp=0;
        
        for(int i = 0; i < len; i++)
                 temp[i] = tolower(word[i]);
        temp[len] = '\0';

         while (root!=NULL)
         {   //переводим слово со списка в масив исключая перевод строки 
             char wordSpis[46]={0};
             lenSp=strlen(root->data);
             
             for(int i=0;i<(lenSp-1);i++)
                     wordSpis[i]=root->data[i];
                     
             //ищем слово в словаре, если встретили - возвращаем истину
            if (strcmp(temp, wordSpis) == 0)
            {
                return true;
            }
            root=root->next;
         }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *file;
    Node *root=0;
 
	//Открываем текстовый файл для чтения
	file = fopen(dictionary, "r");
	 if (file == NULL)
        return false;
	  
         while (!feof(file))
         {   //устанавливаем голову списка
             char buff[LENGTH+5]={0};
             if (Head==NULL)
             {    //выделяем память для нового нода
                  root=malloc(sizeof(Node));
                      //переписываем с файла в список
                  fgets (buff, 100, file);
                   for(int i=0;i<strlen(buff);i++)
                        root->data[i]=buff[i];
                  
                 Head=root;
             }
             else
             {   
                     //переписываем с файла в список
              fgets (buff, 100, file);
             
               if (strcmp(buff,"")!= 0)
              {       //выделяем память для нового нода
                    root->next=malloc(sizeof(Node));
                    root=root->next;
                    
                  for(int i=0;i<strlen(buff)+1;i++)
                        root->data[i]=buff[i];
           
              root->next=NULL;
              }
             }
         }

	fclose(file);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
     Node *root;
     root=Head;
     int count=0;
         while (root!=NULL)
         {   
               count++;
               root=root->next;
         }
      //   printf("%d",count);
         if (root==NULL)
            return count;
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    Node *root=Head;

    int COUNT=0, sizeST=0;
         while (root!=NULL)
         {   
           free(root);
            COUNT++;
            root=root->next;
         }
        sizeST=size(); 
        if (COUNT==sizeST)
            return true;
    return false;
}
