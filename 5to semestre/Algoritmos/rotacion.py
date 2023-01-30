import numpy as np
import cv2 as cv
import sys
import math

def rotate(img, x, y, width):
    cont=0
    width = width // 2
    cont=cont+1
        
    #divide la imagen en 4 y las mueve en sentido de las manecillas del reloj
    temp = np.copy(img[y:y + width, x:x + width])
    cont=cont+1
    
    img[y:y + width, x:x + width] = img[y + width:y + 2 * width, x:x + width]
    img[y + width:y + 2 * width, x:x + width] = img[y + width:y + 2 * width, x + width:x + 2 * width]
    img[y + width:y + 2 * width, x + width:x + 2 * width] = img[y:y + width, x + width:x + 2 * width]
    img[y:y + width, x + width:x + 2 * width] = temp
    cont=cont+1
    if width > 1:
        rotate(img, x, y, width)
        cont=cont+1
        rotate(img, x + width, y, width)
        cont=cont+1
        rotate(img, x + width, y + width, width)
        cont=cont+1
        rotate(img, x, y + width, width)
        cont=cont+1
        

def rotate_with_steps(img, output, x, y, width, shift):
    
    temp = np.copy(img[y:y + width, x:x + width])
    
    output[y + width - shift:y + 2 * width - shift, x:x + width] = img[y + width:y + 2 * width, x:x + width]
    output[y + width:y + 2 * width, x + width - shift:x + 2 * width - shift] = img[y + width:y + 2 * width, x + width:x + 2 * width]
    output[y + shift:y + width + shift, x + width:x + 2 * width] = img[y:y + width, x + width:x + 2 * width]
    output[y:y + width, x + shift:x + width + shift] = temp

def is_power_of_two(n):
    return (n != 0) and (n & (n-1) == 0)

def yes_or_no(question):
    while True:
        try:
            reply = str(input(question+' (y/n): ')).lower().strip()
            if reply[0] == 'y':
                return True
            if reply[0] == 'n':
                return False
        except:
            pass

if len(sys.argv) != 3:
    print("Tenemos: rotate.py <unnamed.jpg> <connme.jpg>")
    print("Formatos permitidos:  .m4a .mp4 .mov .avi")
    print("La imagen debe ser NxN, N debe ser potencia de 2")
    sys.exit()


#lee la imagen
file_name = sys.argv[1]
image = cv.imread(file_name)

#checa el peso de la imagen
if not (is_power_of_two(image.shape[0]) and image.shape[0] == image.shape[1]):
    print("La imagen no es NxN o potencia de 2")
    closest_valid_dimension = 2**round(math.log(min(image.shape[0], image.shape[1]), 2))
    #prompt user to either resize image to closest NxN where N is a power of 2
    if yes_or_no("Le gustaria cambiar las dimensiones de la imagen?: {}x{}?".format(closest_valid_dimension, closest_valid_dimension)):
        image = cv.resize(image, (closest_valid_dimension, closest_valid_dimension))
    else:
        #si no quiere cambiar el tamaño
        #sale porque el programa no puede trabajar asi
        print("Saliendo...")
        sys.exit()

img_dim = image.shape[0]

out_file_name = sys.argv[2]
out = cv.VideoWriter(out_file_name, cv.VideoWriter_fourcc('m','p','4','v'), 30, (img_dim, img_dim))

#rota 4 veces
for rotations in range(4):

    width = img_dim // 2
    number_of_frames = 2 * int(math.log2(img_dim))

    while width > 0:
        
        number_of_frames -= 2
        number_of_frames = max(1, number_of_frames)

        #mueve los mosaicos
        for i in range(0, number_of_frames):
        
            output_canvas = np.copy(image)
            shift = (width * (i + 1)) // number_of_frames
        
            for x in range(0, img_dim, 2 * width):
                for y in range(0, img_dim, 2 * width):
                    rotate_with_steps(image, output_canvas, x, y, width, shift)
                    
            cv.imshow('output', output_canvas)
            cv.waitKey(1)
            
            out.write(output_canvas)
        
        image = np.copy(output_canvas)
        width = width // 2
    
out.release()


