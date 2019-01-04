import cv2
import time
import json
import demjson
import base64
import requests 
import subprocess 
import tkinter as tk
import _thread

Doorsta = False
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 360)
fourcc = cv2.VideoWriter_fourcc(*'a\0\0\0')
out = cv2.VideoWriter("./CarImage/Video.mp4", fourcc, 20.0, (640, 360))

def button(): 
    window = tk.Tk()
    window.title('Door Status Window')
    window.geometry('200x100')

    var = tk.StringVar()    # 这时文字变量储存器
    var.set('Door Close')
    color = 'red'
    def hit_me():
        global Doorsta
        global color
        if Doorsta == False:     # 从 False 状态变成 True 状态
            Doorsta = True
            color = 'green'
            l.configure(bg=color)
            var.set('Door Open')   # 设置标签的文字为 'you hit me'
        else:       # 从 True 状态变成 False 状态
            Doorsta = False
            color = 'red'
            l.configure(bg=color)
            var.set('Door Close') # 设置 文字为空

    l = tk.Label(window, 
        textvariable=var,   # 使用 textvariable 替换 text, 因为这个可以变化
        bg=color, font=('Arial', 12), width=15, height=2)
    l.pack() 

    b = tk.Button(window, 
        text='Press',      # 显示在按钮上的文字
        width=15, height=2, 
        command=hit_me)     # 点击按钮式执行的命令
    b.pack()    # 按钮位置
  
    window.mainloop()

def camera():
    var = 150
    count = 0
    camchk = 0
    num = 1
    fp = open("./businfo.txt","r")
    decodejson = demjson.decode(fp.read())
    fp.close()
    Stopsta = decodejson['A2EventType']
    while(True):   
        global Doorsta
        global out
        ret, frame = cap.read()
        if ret == True :
            cv2.imshow('frame', frame)
            if Stopsta == 1 and Doorsta == True :
                camchk = 1
                out.write(frame)  
                if var == 150:
                    cv2.imwrite( "./CarImage/CarImage.jpg", frame )
                    var = 0
                    count+=1
                    subprocess.call(["php","/home/pi/EmbeddedSystem_Topic/Server/VehicleLicense/vehicleLicense.php","/home/pi/EmbeddedSystem_Topic/Server/ImageCapture/CarImage/CarImage.jpg"])
                    fp1 = open("/home/pi/EmbeddedSystem_Topic/Server/VehicleLicense/vehicle.txt","r")
                    djson = demjson.decode(fp1.read())
                    fp1.close()
                    Status = djson['isVehicle']
                var+=1
            
            if camchk == 1 and Doorsta == False  :
                camchk = 0
                var = 150
                out.release()
                if Status == True  :
                    fp2 = open("./CarImage/CarLicense.txt","w")
                    fp2.write(str(djson['Vehicle']))
                    fp2.close()
                    subprocess.call(["tar","-czvf","sendfile_" + str(num) + ".tgz","./CarImage/CarLicense.txt","./CarImage/CarImage.jpg","./CarImage/Video.mp4"]) 
                    subprocess.call(["./client","/home/pi/EmbeddedSystem_Topic/Server/ImageCapture/sendfile_" + str(num) + ".tgz"])   
                    num+=1
                out = cv2.VideoWriter("./CarImage/Video.mp4", fourcc, 20.0, (640, 360))
        cv2.waitKey(1)

_thread.start_new_thread( camera, ( ) )
_thread.start_new_thread( button, ( ) )

while 1:
   pass

# 釋放攝影機
cap.release()

# 關閉所有 OpenCV 視窗
cv2.destroyAllWindows()
