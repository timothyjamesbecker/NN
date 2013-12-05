#Timothy Becker CSE5095
#basic performance metrics in msec
import cv2

class CPU:
    t1,t2 = 0,0
    def start(self):
        self.t1 = cv2.getTickCount()
        
    def stop(self):
        self.t2 = cv2.getTickCount()
        
    def diff(self):
        return 1000*(self.t2-self.t1)/cv2.getTickFrequency()

