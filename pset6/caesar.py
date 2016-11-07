import sys

num=0
if __name__ == "__main__":
    for param in sys.argv:
        num+=1

    if len(sys.argv)!=2:
        print("Usage: ./caesar k");
        sys.exit(1)
   
    if ((int(sys.argv[1]))<0):
        print("Vedene vid'emne chislo") 
    
    if (int(sys.argv[1])>26): 
        k=int(sys.argv[1])%26;
    else:
        k = int(sys.argv[1])
  
str=list(input("plaintext:  "))
i=0

while i<len(str):
    if ((ord(str[i])>=ord('a'))and(ord(str[i])<=ord('z'))):
        if ((ord(str[i])+k)>ord('z')):
            str[i]=chr(ord('a')+(k-(ord('z')-ord(str[i])))-1)
        else:   
            str[i]=chr(ord(str[i])+k)
 
  
    if ((ord(str[i])>=ord('A'))and(ord(str[i])<=ord('Z'))):
        if ((ord(str[i])+k)>ord('Z')):
            str[i]=chr(ord('A')+(k-(ord('Z')-ord(str[i])))-1)
        else:
            str[i]=chr(ord(str[i])+k)
    i+=1
str1="".join(str)
print("ciphertext:",str1);