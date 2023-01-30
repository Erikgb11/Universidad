
import math
def gene(prim):
    list=[]
    res=""
    for i in range(1, prim, 1):
        list.append(i)
    for j in list:
        listchi=[]
        for i in list:
            result=j**i%prim
            listchi.append(result)
        if len(listchi)==len(set(listchi)): # False porque hay dos '1'
            print(res)
            res=res+" "+str(j)
    print(res)
    file = open('generadores.txt', 'w')    #se guarda
    file.write(res)                                      
    file.close
    return res
    
def romperpld(p,g,y):
    r=1
    c=2
    while r==1:
        res=g**c%p
        if res==y:
            print(str(g)+"^"+str(c)+"mod "+str(p)+"= "+str(y))
            r=2
        elif res>y:
            r=2
        else:
            c=c+1

def main():
    ''' prim = int(input("ingrese el numero primo: "))
    res=gene(prim)
    respue=res.split()
    for i in respue:
        for j in range(1, prim, 1):
            romperpld(prim,int(i),j) '''
    #con esto comentado se puede hacer el de todos los generadores, solo que tarda mucho tiempo
    prim = int(input("ingrese el numero primo: "))
    i= int(input("ingrese el generador: "))
    for j in range(1, prim, 1):
        romperpld(prim,i,j)
main()
        