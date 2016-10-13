#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    unsigned char block[512];
    int name = 0; 
    bool Start = false;
    
     if (argc != 2)
    {
        fprintf(stderr,"Usage: ./recover image");
        return 1;
    }
    
    //otkruvau file
    char* infile =argv[1];
    FILE* inptr = fopen(infile, "r");
   

    // otkruvau file 
    FILE* outptr;
    //zchituu file poka !=0
    while(fread(block, 512, 1, inptr) != 0){
    //proverka 
        if ((int) block[0] == 255 && (int) block[1] == 216 && (int) block[2] == 255 && ((int) block[3] == 224 || (int) block[3] == 225))
        {
          //esli prochitan file to zakrut'
            if (Start)
                fclose(outptr); 
            else
                Start  = true;
                
              //Zapis imeni  
            char fileName[4];
             if (name < 10)
                sprintf(fileName, "00%i.jpg", name);
            else
                sprintf(fileName, "0%i.jpg", name);
            
            // esli nelzya zipisat ->error
            outptr = fopen(fileName, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", fileName);
                return 3;
            }
      
    
            name++;
        }
        
        if (Start)
            fwrite(&block, 512, 1, outptr);

    }
    
    fclose(outptr);
    fclose(inptr);  
    return 0;
}