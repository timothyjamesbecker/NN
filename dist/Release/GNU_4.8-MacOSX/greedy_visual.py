import sys
import os
import numpy as np
import scipy as sp
import random as r
import subprocess as s
import cv  #old bindings
import cv2 #newer bindings

import sources #windowing and video utils
import filters #modifiers
import shapes  #shape processing/masking
import perform #performance measures

for arg in sys.argv: print(arg)

#start of functions============================================
def get_color():
    color = (r.randrange(0,255),r.randrange(0,255),
             r.randrange(0,255),0.5)
    return color

#setup the args to pass the nn.exe...
def next_points(new,points):
    for i in range(0,new):
        row = [0.0,0.0]
        row[0] = r.gauss((x_h-x_l)/2,(x_h-x_l)/10)
        row[1] = r.gauss((y_h-y_l)/2,(x_h-x_l)/10)
        points.append(row)
    

#adds new data elements to args
#1, 0, 10, first 10 points, header only        
def next_args(k,n,new,points,args):
    h = args[0:4]
    h[1] = str(k)
    h[3] = str(len(points))
    for i in range(n-new,n):
        args.append(str(points[i][0]))
        args.append(str(points[i][1]))
    args[0:4] = h #hack up the start
    

#wrapper for sending out a program with args
#and grabbing back its output
def greedy_sample(args):
    return s.check_output(args)

#get one new random color (RGB)
def rcolor():
    color = (r.randrange(0,255),
             r.randrange(0,255),
             r.randrange(0,255),1.0)
    return color

#get one new random color (RGB)
def rblue():
    color = (r.randrange(0,255),
             r.randrange(0,155),
             r.randrange(0,55),0.5)
    return color

#get one new random color (RGB)
def rred():
    color = (r.randrange(0,25),
             r.randrange(0,25),
             r.randrange(0,255),0.5)
    return color

#get one new random color (RGB)
def ryellow():
    y = r.randrange(75,255)
    return (r.randrange(0,55),y,y,0.5)

#get one new random color (RGB)
def rwhite():
    w = r.randrange(155,255)
    return (w,w,w,0.5)

def rsize(m): return int(round(r.triangular(0,m)))

def rthick(t): return r.randrange(0,t)

#end of functions============================================
k,n = 1,0
#----------------------------------------------------
#starting arguments are the maximums
#starting data is for max dimension but with zeros...
args = ['./greedy_perm',str(k),'2',str(n)] #just intial
points = []
#----------------------------------------------------
#video params for setting up display
height,width = 720,1280 #screen dimensions desired
x_l,x_h = 0, width  #fixed to screen dimension
y_l,y_h = 0, height #fixes to screen dimension

#####################################################################


#base colors, randomize point colors
red,green,blue,black     = (0,0,255),(0,255,0),(255,0,0),(255,255,255)
yellow,purple,gray,white = (0,255,255),(200,0,200),(100,100,100),(0,0,0)

#RT control keys:
#esc key exits the RT loop (with a variable pause in seconds)
KEY_ESC,KEY_W,KEY_1,KEY_2,KEY_R = 27,119,49,50,114
KEY_C,KEY_L,KEY_P = 99,108,112
#new video source object (makes windows, opens videos, camera,ect)
source = sources.Sources()
#new window to view video streams
source.win_start('video_input')
p = perform.CPU()
#captures video files or default webcam = 0
f,M = 1,10 #n=number of max frames, m= a divsor for output
RT,IM,frame,diag = True,True,0,white
CL,LIN,PO = False,False,True # for display of clusters and lines
p_colors,c_colors,clust,c_map = [],[],[],{}
c_colors.append(rwhite()) #clusters draw white/grey?
c_map = {} #color map
while RT and (frame < f): #Real-Time Loop=> 'esc' key turns off
    p.stop()
    imc = np.zeros((height,width,4), np.uint8)
    ims = filters.invert(imc)
    #check for background toggle
    if(IM): draw,diag = imc,black #toggles viewing mode
    else:   draw,diag = ims,white #between input+overlay && overlay
    
    #draw points here)))))))))))))))))))))))))))))))))))))))))))))))
    if(PO):
        for z in range(0,n):
           #shapes.draw_point(im,  (x,y)    ,c  ,size), c_map[z] -> cluster,dist
           #print("color map entry z: "+str(c_map[z]))
           #print("c_colors: "+str(c_colors))
           shapes.draw_point(draw,points[z],p_colors[z],2,2)

    #draw points here)))))))))))))))))))))))))))))))))))))))))))))))

    #check for cluster & line toggles__________________________
    if(CL):
        for z in range(0,n):
            shapes.draw_point(draw,points[z],
                              c_colors[clust.index(c_map[z])],
                              rsize(20),rthick(1))
        for cl in clust:
            shapes.draw_point(draw,points[cl],
                              c_colors[clust.index(c_map[cl])],
                              rsize(50),rthick(6))
    if(LIN):
        for z in range(0,n):
            shapes.draw_line(draw,points[z],points[c_map[z]],
                             c_colors[clust.index(c_map[z])],1) 
    #check for cluster & line toggles__________________________
            
    source.win_diag(draw,n,p.diff(),k,diag)
    p.start()
    #.......................drawing................................
    
    #Sentel Loop Control Logic============================
    K = cv2.waitKey(60)           #wait period => FPS requested
    if K == KEY_ESC: break        #'esc' key exit
    if K == KEY_W: IM = not IM    #toggle viewing mode
    if K == KEY_R:
        #general data and args calls---------------------------------
        next_points(10,points)               #offset keeps your place
        n = n + 10
        for i in range(0,10): p_colors.append(rred())
        #print(points)
        next_args(k,n,10,points,args) #in the max nxd space
        #print(args)
        out = greedy_sample(args) #pass to program here
        out = out[:-1] #trim one extra blank
        labels = out.split('\n')       #split tokens for each p
        data = []
        for g in labels: data.append(g.split(' '))
        clust = [int(j) for j in data[0][:-1]] #trim one extra blank
        #print(clust)
        data = data[1:]
        #print(data)
        #print(str(n)+", data returned: "+str(len(data)))
        for j in range(0,n):
            pp,cc = int(data[j][0]),int(data[j][1])
            c_map.update({pp:cc})
        #print(c_map)
        
        #general data and args calls---------------------------------
    if K == KEY_L: LIN = not LIN
    if K == KEY_C: CL  = not CL
    if K == KEY_P: PO  = not PO
    #if K == KEY_1:
        
    if K == KEY_2:
        if k < 25:
            k = k + 1
            c_colors.append(rcolor())
            #print(c_colors)
    
    source.win_print('video_input',draw) #display output
    frame = (frame+1)%61          #update the frame counter
    if(source.mode == 0): f+=1    #take out frame + n for video
    #Sentel Loop Control Logic============================
    
source.win_stop('video_input',1) #close up window thread, pause 1 sec



