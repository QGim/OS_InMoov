# Python program to check
# whether the camera is opened 
# or not
  
  
import numpy as np
import time
import cv2
  
  
cap = cv2.VideoCapture(0,cv2.CAP_V4L2)

cap.set(cv2.CAP_PROP_FPS, 30)
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('m','j','p','g'))
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M','J','P','G'))
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 800)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 600)

frame_size = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
              int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))

print(frame_size)
print(cv2.CAP_PROP_FPS,30)

prevTime = 0


while True:
    ret, img = cap.read()
    if not ret:
        break


    curTime = time.time()
    sec = curTime - prevTime
    prevTime = curTime

    fps = 1/(sec)

    str = "FPS : %0.1f" % fps

    cv2.putText(img, str, (0, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0))

    cv2.imshow('img', img)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break
              
cap.release()
cv2.destroyAllWindows()

