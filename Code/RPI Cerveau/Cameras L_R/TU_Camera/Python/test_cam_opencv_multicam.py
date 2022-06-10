import numpy as np
import time
import cv2
  
  
oeil_d = cv2.VideoCapture(0,cv2.CAP_V4L2)
oeil_d.set(cv2.CAP_PROP_FPS, 10.0)
oeil_d.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('m','j','p','g'))
oeil_d.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M','J','P','G'))
oeil_d.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
oeil_d.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
frame_size_right = (int(oeil_d.get(cv2.CAP_PROP_FRAME_WIDTH)),
              int(oeil_d.get(cv2.CAP_PROP_FRAME_HEIGHT)))

print("oeil_droit : " + str(frame_size_right))
print(cv2.CAP_PROP_FPS,30)


oeil_g = cv2.VideoCapture(2,cv2.CAP_V4L2)
oeil_g.set(cv2.CAP_PROP_FPS, 10.0)
oeil_g.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('m','j','p','g'))
oeil_g.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M','J','P','G'))
oeil_g.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
oeil_g.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
frame_size_left = (int(oeil_g.get(cv2.CAP_PROP_FRAME_WIDTH)),
              int(oeil_g.get(cv2.CAP_PROP_FRAME_HEIGHT)))

print("oeil_gauche : " + str(frame_size_left))
print(cv2.CAP_PROP_FPS,30)



prevTime_g = 0
prevTime_d = 0

while True:
    ret_d, img_d = oeil_d.read()
    ret_g, img_g = oeil_g.read()
    if not ret_d:
        break
    if not ret_g:
        break

    curTime_g = time.time()
    sec_g = curTime_g - prevTime_g
    prevTime_g = curTime_g
    fps_g = 1/(sec_g)
    str_g = "FPS : %0.1f" % fps_g
    cv2.putText(img_g, str_g, (0, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0))

    curTime_d = time.time()
    sec_d = curTime_d - prevTime_d
    prevTime_d = curTime_d
    fps_d = 1/(sec_d)
    str_d = "FPS : %0.1f" % fps_d
    cv2.putText(img_d, str_d, (0, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0))

    cv2.imshow('oeil_g', img_g)
    cv2.imshow('oeil_d', img_d)
    if cv2.waitKey(1) & 0xff == ord('q'):
        break
              
oeil_d.release()
oeil_g.release()
cv2.destroyAllWindows()
