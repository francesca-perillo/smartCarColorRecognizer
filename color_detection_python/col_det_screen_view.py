from asyncio.windows_events import NULL
from email import message
import cv2
import urllib.request
import numpy as np
# to send color detection to arduino
import socket
from threading import Thread
# to delay the sending of messages
import timeit

#function to open socket and connection
def socket_connection(message):
    sock = socket.socket()
    host = "192.168.1.9" 
    port = 81                
    sock.connect((host, port))
    try: 
        sock.send(message.encode('utf-8'))
    except ConnectionResetError:
        print('lost connection after socket_connection call function, automatically restart!')
        sock.connect((host, port))
        sock.send(message.encode('utf-8'))
    

#url Silvio: 'http://192.168.1.13/cam-lo.jpg'
#url Francesca: http://192.168.1.11/cam-lo.jpg
url='http://192.168.1.9/cam-hi.jpg'
cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)

#------- DATA FROM color_detection.py -------#
#color detection for blue
l_h_blue, l_s_blue, l_v_blue = 14,88,175
u_h_blue, u_s_blue, u_v_blue = 165,255,255
#color detecrion for red 
l_h_red, l_s_red, l_v_red = 0, 10, 190
u_h_red, u_s_red, u_v_red = 10, 255,255

# var time to avoid continuos sending messages 
start = 1


while True:
    try:
        #get image from request (the url generated by Arduino IDE)
        img_resp=urllib.request.urlopen(url)
        imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
        frame=cv2.imdecode(imgnp,-1)
        
        # 1- convert frame from BGR to HSV
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        
        # 2- define the range of red
        l_b_blue = np.array([l_h_blue, l_s_blue, l_v_blue]) #blue
        u_b_blue = np.array([u_h_blue, u_s_blue, u_v_blue])
        l_b_red = np.array([l_h_red, l_s_red, l_v_red]) #red
        u_b_red = np.array([u_h_red, u_s_red, u_v_red])

        #check if the HSV of the frame is lower or upper blue and red
        mask_blue = cv2.inRange(hsv, l_b_blue, u_b_blue)
        mask_red = cv2.inRange(hsv, l_b_red, u_b_red)

        cnts_blue, _ = cv2.findContours(mask_blue,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        cnts_red, _ = cv2.findContours(mask_red,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    
        # draw border line on the detected blue area
        for c in cnts_blue:
            area=cv2.contourArea(c)
            if area>9000:
                cv2.drawContours(frame,[c],-1,(255,0,0),3)
                M=cv2.moments(c)
                cx=int(M["m10"]/M["m00"])
                cy=int(M["m01"]/M["m00"])

                #python send message to arduino client - wifi
                new_vision = timeit.default_timer()
                if(new_vision-start>2):
                    Thread(target=socket_connection, args=('b',)).start()
                    start = timeit.default_timer()
                    color ='blue'

                cv2.circle(frame,(cx,cy),7,(255,255,255),-1)
                cv2.putText(frame,"blue",(cx-20, cy-20),cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255),2)
        
        # draw border line on the detected red area
        for c in cnts_red:
            area=cv2.contourArea(c)
            if area>9000:
                cv2.drawContours(frame,[c],-1,(255,0,0),3)
                M=cv2.moments(c)
                cx=int(M["m10"]/M["m00"])
                cy=int(M["m01"]/M["m00"])

                #python send message to arduino client - wifi
                new_vision = timeit.default_timer()
                if(new_vision-start>2):
                    Thread(target=socket_connection, args=('r',)).start()
                    start = timeit.default_timer()
                    color = 'red'

                cv2.circle(frame,(cx,cy),7,(255,255,255),-1)
                cv2.putText(frame,"red",(cx-20, cy-20),cv2.FONT_HERSHEY_SIMPLEX, 1, (0,0,255),2)
            
        res = cv2.bitwise_and(frame, frame, mask=mask_blue)
    
        cv2.imshow("live transmission", frame)
        cv2.imshow("mask", mask_blue)
        cv2.imshow("res", res)
        key=cv2.waitKey(5)
        if key==ord('q'):
            break
    except ConnectionResetError:
        print('trovato '+ color)
 
cv2.destroyAllWindows()