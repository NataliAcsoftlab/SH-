vusota=0
import re

while(vusota<=0) or (vusota>=24):
    if (vusota<=0) or (vusota>=24):
        str=input("Height ot 1 do 23: ")

    if re.fullmatch('[0-9]*', str) and str:
        vusota=int(str)

i=1

while i<=vusota:
    j=i

    while j<=vusota:
        print (" ",end="")
        j+=1
   
    a=0
    while a<i:
        print ("#",end="")
        a+=1
    
    print ("  ",end="")
    
    a=0
    while a<i:
        print ("#",end="")
        a+=1
    print ("")
    i+=1
        
    