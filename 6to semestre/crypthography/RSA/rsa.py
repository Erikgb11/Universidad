from tkinter import *
import tkinter as tki
from tkinter import ttk
from Crypto.PublicKey import RSA
import base64
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
from tkinter import filedialog
from tkinter import messagebox
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA3_256


def padding(s):
    return s + b"\0" * (4 - len(s) %4)#hace el padding por si faltan cadenas de 32 bits

def hashchi(file): 
    carac = []
    file = padding(file)#se hace el padding con el texto recuperado
    for i in range(0, len(file), 4):
        carac.append(file[i:i+4])#se separan los caracteres en 4 y se guardan en la lista carac
    elxor = int.from_bytes(carac[0], "big")#se guarda el primer valor en la variable de resultados
    for i in range(1,len(carac), 1):
        elxor = elxor^int.from_bytes(carac[i], "big")#se hace el xor con toda la lista
    elxor = int.to_bytes(elxor,4,"big")#nos ayuda a mostrar el byte mas significativo al principio
    xor64 = base64.b64encode(elxor)#se guarda en base64
    return xor64#se retorna

    
def keypublicypriv(name):
    key = RSA.generate(2048)#se genera la llave privada
    privada = key.export_key()
    archivin = open("key_privada"+name+".pem", "wb")#se guarda
    archivin.write(privada)
    archivin.close()

    publica = key.publickey()#se genera la llave publica
    pubkey = publica.export_key()
    archivon = open("key_publi"+name+".pem", "wb")#se guarda
    archivon.write(pubkey)
    archivon.close()
    return key#se retorna key
    
    
def hashing(file):
    hash = SHA3_256.new(file)#se hace el hash del texto con sha256
    hash = hash.hexdigest()#funcion para que solo use numeros hexadecimales
    archivohash = open("hash_sha256.txt", "w")#se guarda en un nuevo archivo
    archivohash.write(hash)
    archivohash.close


def encript(plaintext,key,name):
    public_key = key.publickey()
    encryptor = PKCS1_OAEP.new(public_key)
    encrypted = encryptor.encrypt(plaintext)#se lleva a cabo la encriptacion
    ciphertext = base64.b64encode(encrypted)#se pasa a base64
    file = open('Hash_rsa_cifrado'+name+'.txt', 'wb')    #se guarda
    file.write(ciphertext)                                      
    file.close



def decript(ciphertext ,key,name):
    ciphertext = base64.b64decode(ciphertext)#se convierte de base64
    decryptor = PKCS1_OAEP.new(key)
    plaintext = decryptor.decrypt(ciphertext)#se decripta
    file = open('hash_rsa_descifrado_'+name+'.txt', 'wb')  #se guarda el archivo  
    file.write(plaintext)                                      
    file.close

def comenzar():
    if file == "ningun archivo seleccionado":
        print("No se selecciono archivo")
        messagebox.showerror(title="Error", message="Ingrese y seleccione los campos necesarios\n")
    else:
        print("La opcion es " + mod.get())
        print("El path del archivo es: " + file)

        with open(file, "rb") as archivo:
            bytesArchivo = archivo.read()
        if mod.get()=="Hash con elxor":
            print("El hash con xor queda : ", hashchi(bytesArchivo))
        elif mod.get()=="Hash SHA256":
            hashing(bytesArchivo)
        elif mod.get()=="Cifrado RSA":
            nombre=name.get()
            base644=hashchi(bytesArchivo)
            print(base644)
            key=keypublicypriv(nombre)
            encript(base644,key,nombre)
        else:
            nombre=name.get()
            key_file = open("key_privada"+nombre+".pem", "rb")
            key_file = key_file.read()
            key = RSA.import_key(key_file)
            decript(bytesArchivo,key,nombre)

file = ""
def choose():
    global file
    file = filedialog.askopenfilename()
    fileLabel.configure(text=file)


window = Tk()
window.title("Lab 6: Cryptographic hash functions and RSA")
image = tki.PhotoImage(file="IPN.png")
imageS = image.subsample(6)
widget = tki.Label(image=imageS)
widget.place(x=-45,y=-4)

image2 = tki.PhotoImage(file="ESCOM.png")
imageS2 = image2.subsample(14)
widget2 = tki.Label(image=imageS2)
widget2.place(x=440,y=5)
window.geometry("600x500")

lbl = Label(window, text=" ESCOM - IPN\n Hash functions and RSA", font=("Arial", 15))
lbl.place(x=160, y=20)

mod = ttk.Combobox(window, values=["Hash con elxor","Hash SHA256","Cifrado RSA","Descifrado RSA"],state="readonly")
mod.current(0)
mod.place(x =225,y = 120)

fileButton = Button(window, text="Select file", command=choose)
fileButton.place(x=260, y=320)
fileButton["bg"] = "#d43737"
fileLabel = Label(window, text=file, font=("Arial", 9), width=70)
fileLabel.place(x=55, y=370)
fileLabel.config(anchor=CENTER)

messi = Label(window, text="Ingrese el nombre, solo en caso de cifrado/descifrado RSA", font=("Arial", 12),width=60)
messi.place(x=20, y=210)
name = ttk.Entry(window)
name.place(x=225, y=260)
nameLabel = Label(window, text="Nombre", font=("Arial", 9))
nameLabel.place(x=170, y=260)


btn = Button(window, text="Start", command=comenzar)
btn["bg"] = "#d43737"
btn.place(x=275, y=420)

result = Label(window, text="", font=("Arial", 12),width=60)
result.place(x=20, y=385)
result.config(anchor=CENTER)
window.mainloop() 