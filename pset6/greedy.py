from math import *
moneta25=0; moneta10=0; moneta5=0; moneta1=0;
stroka=1 #false
import re
str=0

print("O hai! ",end="")
while(stroka==1):
    if (str<=0):
        print("How much change is owed?")
        stroka=1

    chislo=input()
    
    try:
        st = float(chislo)
    except ValueError:
        print ("Retry:")
        str=1
    else:
        str=float(chislo)
        if (str>0):
            stroka=0

suma=ceil(str*100)      

if ((suma/25)>0):
    moneta25=int(suma/25)
    suma=suma-moneta25*25

if((suma/10)>0):
    moneta10=int(suma/10)
    suma=suma-moneta10*10

if((suma/5)>0):
    moneta5=int(suma/5)
    suma=suma-moneta5*5
    
moneta1=suma
print(moneta1+moneta5+moneta10+moneta25)
