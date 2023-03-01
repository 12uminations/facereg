import cv2
import numpy as np
import face_recognition
import os
from datetime import datetime
from pyfirmata import Arduino ,SERVO,util
import time
from pymata4 import pymata4
# from PIL import ImageGraba

triggerPin = 11
echo_Pin = 12

board = pymata4.Pymata4()
time.sleep(2.0)
def callback(data):
    print("distance",data(2))
pin=9   
#Set mode of pin
#board.digital[pin].mode=SERVO 
board.set_pin_mode_servo(pin)
board.set_pin_mode_sonar(triggerPin,echo_Pin,callback)
#### SERVO function control ####

def rservo(pin,angle):#creat function to controll servo
    board.
    time.sleep(0.015)

 #**********************************************************************************
rservo(pin,90)
path = '4horsemen'
images = []
classNames = []
myList = os.listdir(path)
print(myList)
for cl in myList:
    curImg = cv2.imread(f'{path}/{cl}')
    images.append(curImg)
    classNames.append(os.path.splitext(cl)[0])
print(classNames)
 
def findEncodings(images):
    encodeList = []
    for img in images:
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        encode = face_recognition.face_encodings(img)[0]
        encodeList.append(encode)
    return encodeList
 
def markAttendance(name):
    with open('att.csv','r+') as f:
        myDataList = f.readlines()
        nameList = []
        for line in myDataList:
            entry = line.split(',')
            nameList.append(entry[0])
        if name not in nameList:
            now = datetime.now()
            dtString = now.strftime('%H:%M:%S')
            f.writelines(f'\n{name},{dtString}')
 
#### FOR CAPTURING SCREEN RATHER THAN WEBCAM
# def captureScreen(bbox=(300,300,690+300,530+300)):
#     capScr = np.array(ImageGrab.grab(bbox))
#     capScr = cv2.cvtColor(capScr, cv2.COLOR_RGB2BGR)
#     return capScr
 
encodeListKnown = findEncodings(images)
print('Encoding Complete')
 
cap = cv2.VideoCapture(0)
 
while True:
    success, img = cap.read()
    #img = captureScreen()
    imgS = cv2.resize(img,(0,0),None,0.25,0.25)
    imgS = cv2.cvtColor(imgS, cv2.COLOR_BGR2RGB)
 
    facesCurFrame = face_recognition.face_locations(imgS)
    encodesCurFrame = face_recognition.face_encodings(imgS,facesCurFrame)
    

    for encodeFace,faceLoc in zip(encodesCurFrame,facesCurFrame):
        matches = face_recognition.compare_faces(encodeListKnown,encodeFace)
        faceDis = face_recognition.face_distance(encodeListKnown,encodeFace)
        #print(faceDis)
        matchIndex = np.argmin(faceDis)
 
        if matches[matchIndex]:
            name = classNames[matchIndex].upper()
            print(name)
            y1,x2,y2,x1 = faceLoc
            y1, x2, y2, x1 = y1*4,x2*4,y2*4,x1*4
            cv2.rectangle(img,(x1,y1),(x2,y2),(0,255,0),2)
            cv2.rectangle(img,(x1,y2-35),(x2,y2),(0,255,0),cv2.FILLED)
            cv2.putText(img,name,(x1+6,y2-6),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),2)
            markAttendance(name)
            rservo(pin,0)
            time.sleep(3)
            rservo(pin,90)


    
        while True:
            try:
                time.sleep(1)
                board.sonar_read(triggerPin)
            except Exception:
                board.shutdown()


    cv2.imshow('Webcam',img)
    cv2.waitKey(1)

    