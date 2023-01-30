from tkinter import *
from Crypto import Random
from Crypto.Random import get_random_bytes
import tkinter as tki
from tkinter import ttk
import base64
from tkinter import filedialog
from tkinter import messagebox
from Crypto.Cipher import AES
from Crypto.Cipher import DES3


def padAES(s):
    return s + b"\0" * (AES.block_size - len(s) % AES.block_size)   #Se lleva a cabo el padding para AES
def pad3DES(s):
    return s + b"\0" * (DES3.block_size - len(s) % DES3.block_size)   #Se lleva a cabo el padding para 3DES

def cifrarCBCAES(bytesArchivo, llave):
    print("Cifrado CBC AES")
    bytesArchivo = padAES(bytesArchivo)    #hacemos uso de la funcion de padding para el texto recuperado
    iv = Random.new().read(AES.block_size) #generamos un vector de inicializacion random para AES
    cipher = AES.new(llave,AES.MODE_CBC, iv) #Se especifica la llave y el modo
    textCifrada = cipher.encrypt(bytesArchivo) #Se cifra
    guoy=base64.b64encode(iv + textCifrada) #se pasa a base 64 el iv+el texto cifrado
    with open(file+"_AESeCBC.txt", "wb") as archivo: #Se escribe el texto
        archivo.write(guoy)
    result.config(text="Text encrypted in CBC (AES)")#se imprime eso en la interfaz

def descifrarCBCAES(bytesArchivo, llave):
    print("descifrado CBC")
    llave=base64.b64decode(llave)   #decodificamos el base 64 de la llave
    bytesArchivo=base64.b64decode(bytesArchivo) #Decodificamos lo que hay en el archivo
    iv = bytesArchivo[:AES.block_size]#separamos el vector 
    cipher = AES.new(llave,AES.MODE_CBC, iv) #Se especifica la llave y el modo de descifrar
    textDescifrada = cipher.decrypt(bytesArchivo[AES.block_size:]) #Se descifra
    with open(file+"_AESdCBC.txt", "wb") as archivo: #Se escribe la texto descifrado
        archivo.write(textDescifrada)
    result.config(text="Text decrypted in CBC (AES)")


def cifrarCBCdes(bytesArchivo,llave):
    print("Cifrado CBC in 3DES")
    bytesArchivo=pad3DES(bytesArchivo) #padding
    iv = Random.new().read(DES3.block_size) #se genera vector de inicialiacion random
    cipher = DES3.new(llave, DES3.MODE_CBC,iv)#Se especifica la llave y el modo de cifrar
    plaintext = cipher.encrypt(bytesArchivo)#Se cifra
    guoy=base64.b64encode(iv+plaintext) #se pasa a base64 la concatenacion del vector y el cifrado
    with open(file+"_3desCBC.txt", "wb") as archivo: #Se escribe el texto
        archivo.write(guoy)
    result.config(text="Text encrypted in CBC (3DES)")

def descifrarCBCdes(bytesArchivo,llave):
    print("Descifrado CBC in 3DES")
    llave=base64.b64decode(llave)#se descifra la llave de base 64
    bytesArchivo=base64.b64decode(bytesArchivo)#se descifra lo recuperado del archivo de base64
    iv=bytesArchivo[:DES3.block_size]# se separa el vector del texto recuperado
    cipher=DES3.new(llave, DES3.MODE_CBC,iv)#Se especifica la llave y el modo de descifrar
    textDescifrada=cipher.decrypt(bytesArchivo[DES3.block_size:])#Se descifra
    with open(file+"_D3desdCBC.txt", "wb") as archivo: #Se escribe el texto descifrado
        archivo.write(textDescifrada)
    result.config(text="Text decrypted in CBC (3DES)")


def comenzar():
    if file == "ningun archivo seleccionado":#no se lleva a cabo el programa si no se ingresa el archivo
        print("No se selecciono archivo")
        messagebox.showerror(title="Error", message="Ingrese y seleccione los campos necesarios\n")
    else:
        print("La opcion es " + combo.get())
        print("El path del archivo es: " + file)

        #El texto se pasa a bytes
        with open(file, "rb") as archivo: #Se abre en modo lectura
            bytesArchivo = archivo.read()

        llaveBytes = str.encode(llave.get()) #La llave se convierte a bytes

        if mod.get()=="AES":#si se elige AES
            if combo.get() == "Encrypt": #Se cifra
                try:
                    if modoa.get()=="128(AES)": #Si se elige llave de 128 bits
                        key=get_random_bytes(16)#se genera la llave de manera random
                        encoded = base64.b64encode(key)#se pasa a base 64
                        with open(file+"keysAES128_eCBC.txt", "wb") as archivo:#se guarda en un archivo
                            archivo.write(encoded)
                    if modoa.get()=="192(AES/3DES)":#Si se elige llave de 192 bits
                        key=get_random_bytes(24)#se genera la llave de manera random
                        encoded = base64.b64encode(key)#se pasa a base 64
                        with open(file+"keysAES192_eCBC.txt", "wb") as archivo: #se guarda en un archivo
                            archivo.write(encoded)
                    if modoa.get()=="256(AES)":#Si se elige llave de 256 bits
                        key=get_random_bytes(32)#se genera la llave de manera random
                        encoded = base64.b64encode(key)#se pasa a base 64
                        with open(file+"keysAES256_eCBC.txt", "wb") as archivo:#se guarda en un archivo
                            archivo.write(encoded)
                    cifrarCBCAES(bytesArchivo, key)#se llama a la funcion de cifrar con AES
                except:#si no se lleva a cabo da error
                    result.config(text="Un error ocurrio al cifrar")
                    print("Error al cifrar")
            else: #Se descifra
                try:
                    descifrarCBCAES(bytesArchivo, llaveBytes)#se llama a la función de cifrar con AES
                except:#si no se lleva a cabo da error
                    result.config(text="Un error ocurrio al descifrar")
                    print("Error al descifrar")
        else:
            if combo.get() == "Encrypt": #Se cifra pero con 3DES
                try:
                    if modoa.get()=="192(AES/3DES)":#si la llave es de 192 bits
                        key = get_random_bytes(24)#se genera la llave de manera random
                        encoded = base64.b64encode(key)#se pasa a base 64
                        with open(file+"keys3DES192_eCBC.txt", "wb") as archivo:#se guarda en un archivo
                            archivo.write(encoded)
                    cifrarCBCdes(bytesArchivo, key)#se cifra con 3des
                    if modoa.get()=="128(AES)" or modoa.get()=="256(AES)":#si no marca error
                        messagebox.showerror(title="Error", message="Sabes que en AES no se pueden llaves asi >:(")
                        result.config(text="Un error ocurrio al cifrar")
                        print("Error al cifrar")
                except:#si no se lleva a cabo da error
                    result.config(text="Un error ocurrio al cifrar")
                    print("Error al cifrar")
            else: #Se descifra
                try:
                    descifrarCBCdes(bytesArchivo, llaveBytes)#se descifra con 3des
                except:#si no se lleva a cabo da error
                    result.config(text="Un error ocurrio al descifrar")
                    print("Error al descifrar")


file = ""
def choose():
    global file
    file = filedialog.askopenfilename()
    fileLabel.configure(text=file)


window = Tk()
window.title("Lab 5- Block ciphers and modes of operation")
image = tki.PhotoImage(file="IPN.png")
imageS = image.subsample(6)
widget = tki.Label(image=imageS)
widget.place(x=-45,y=-4)

image2 = tki.PhotoImage(file="ESCOM.png")
imageS2 = image2.subsample(14)
widget2 = tki.Label(image=imageS2)
widget2.place(x=440,y=5)
window.geometry("600x500")

lbl = Label(window, text="ESCOM - IPN\n Modes of operation with CBC\nSelect the option", font=("Arial", 15))
lbl.place(x=160, y=20)

mod = ttk.Combobox(window, values=["AES","3DES"],state="readonly")
mod.current(0)
mod.place(x =225,y = 120)

combo = ttk.Combobox(window, values=["Encrypt","Decrypt"],state="readonly")
combo.current(0)
combo.place(x =225,y = 150)

modoa = ttk.Combobox(window, values=["128(AES)","192(AES/3DES)","256(AES)"],state="readonly")
modoa.current(0)
modoa.place(x =225,y = 180)

fileButton = Button(window, text="Select file", command=choose)
fileButton.place(x=260, y=320)
fileButton["bg"] = "#d43737"
fileLabel = Label(window, text=file, font=("Arial", 9), width=70)
fileLabel.place(x=55, y=370)
fileLabel.config(anchor=CENTER)

messi = Label(window, text="Ingrese la key para descifrar\n en caso contrario si ingresa una key no se usara", font=("Arial", 12),width=60)
messi.place(x=20, y=210)
llave = ttk.Entry(window)
llave.place(x=225, y=260)
llaveLabel = Label(window, text="Key", font=("Arial", 9))
llaveLabel.place(x=200, y=260)


btn = Button(window, text="Start", command=comenzar)
btn["bg"] = "#d43737"
btn.place(x=275, y=420)

result = Label(window, text="", font=("Arial", 12),width=60)
result.place(x=20, y=385)
result.config(anchor=CENTER)
window.mainloop()