import os
import cv2

dir1=r'F:\504'
dir2=r'F:\505'
index=1
for file in os.listdir(dir1):
    filepath=os.path.join(dir1,file)
    if os.path.isfile(filepath):
        img=cv2.imread(filepath)
        img=img[525:525+2485,1160:1160+3145]
        filename='504_{:03d}.jpg'.format(index)
        cv2.imwrite(os.path.join(dir1,filename),img)
        print(filename)
        index+=1
index=1
for file in os.listdir(dir2):
    filepath=os.path.join(dir2,file)
    if os.path.isfile(filepath):
        img=cv2.imread(filepath)
        img=img[560:560+2485,1260:1260+3145]
        filename='505_{:03d}.jpg'.format(index)
        cv2.imwrite(os.path.join(dir2,filename),img)
        print(filename)
        index+=1

