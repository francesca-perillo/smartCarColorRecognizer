# Python Code + Color Detection using ESP32 CAM
# Now lets learn in detail about the method for Color Detection & Tracking with ESP32 CAM using the OpenCV.
# Our main objective here is to detect color, thus we will be using HSV conversion using the OpenCV library.

# HSV (hue saturation value), also known as HSB (hue, saturation, brightness) is a conversion that is available
# in the OpenCV library. It is very widely used to detect specific colors. But a limitation to this is that there
# are some constant values related to detection, which vary from different objects and places.

# We convert the RGB image to an HSV image and then we set a lower bound of all three values i.e; hue, saturation,
# and brightness, and also an upper bound, thus whatever comes in that range is what we desire to see.

import cv2
import urllib.request
import numpy as np
 
def nothing(x):
    pass
 
#change the IP address below according to the
#IP shown in the Serial monitor of Arduino code

url='http://192.168.1.11/cam-lo.jpg'
 
cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)
 
cv2.namedWindow("Tracking")
cv2.createTrackbar("LH", "Tracking", 0, 255, nothing)
cv2.createTrackbar("LS", "Tracking", 0, 255, nothing)
cv2.createTrackbar("LV", "Tracking", 0, 255, nothing)
cv2.createTrackbar("UH", "Tracking", 255, 255, nothing)
cv2.createTrackbar("US", "Tracking", 255, 255, nothing)
cv2.createTrackbar("UV", "Tracking", 255, 255, nothing)
 
while True:
    img_resp=urllib.request.urlopen(url)
    imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    frame=cv2.imdecode(imgnp,-1)
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    #for the bar in the window named 'Tracking'
    l_h = cv2.getTrackbarPos("LH", "Tracking")
    l_s = cv2.getTrackbarPos("LS", "Tracking")
    l_v = cv2.getTrackbarPos("LV", "Tracking")
 
    u_h = cv2.getTrackbarPos("UH", "Tracking")
    u_s = cv2.getTrackbarPos("US", "Tracking")
    u_v = cv2.getTrackbarPos("UV", "Tracking")
 
    l_b = np.array([l_h, l_s, l_v])
    u_b = np.array([u_h, u_s, u_v])
    
    mask = cv2.inRange(hsv, l_b, u_b) 
    res = cv2.bitwise_and(frame, frame, mask=mask)
 
    cv2.imshow("live transmission", frame)
    cv2.imshow("mask", mask)
    cv2.imshow("res", res)
    key=cv2.waitKey(5)
    if key==ord('q'):
        break
    
cv2.destroyAllWindows()