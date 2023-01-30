
def ispoint(a, b, p):
    for i in range(p):
        for j in range(p):
            X =j**2 % p
            Y=(i**3 + a*i + b)% p
            if X == Y:
                print("[",i,",", j,"] es un punto en la curva")
                


def main():
    a=23
    b=67
    p=29
    ispoint(a, b, p)
    
if __name__== '__main__':
    try:
        main()
    except KeyboardInterrupt:
        exit()