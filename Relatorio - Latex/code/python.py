# sudo chmod 0777 /dev/ttyACM0
# phyton main.py
# sudo chmod 0777 /dev/ttyACM0 && clear && python main.py

import serial
import string
import matplotlib.pyplot as plt

fig=plt.figure()
plt.axis([0,10000,0,12000])

i=0
x=list()
y=list()

plt.ion()
plt.show()

USB = serial.Serial("/dev/ttyACM0",9600)

USB.write("3") 

hex_digits = set(string.hexdigits)

while True:
 if USB.inWaiting():
  leitura = USB.read(14)
  proximidade = leitura[2:6]
  frequencia = leitura[9:12]
  
  
  if all(c in hex_digits for c in proximidade): # verifica se e hexadecimal

   prox_int = int(proximidade,16)
   freq_int = int(frequencia,16)


   print("Proximidade: {} Frequencia: {}".format(prox_int,freq_int))	
    	
   x.append(i)
   y.append(prox_int)
   plt.scatter(x,y)
   i+=200
   plt.draw()   

    
USB.close()