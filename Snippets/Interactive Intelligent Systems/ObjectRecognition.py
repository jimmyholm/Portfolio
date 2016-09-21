# -*- coding: utf-8 -*-
"""
Created on Tue May  3 08:44:03 2016

Object recognition module, to be used to identify objects of interest from
live camera feed.

@author: Robot Programming 2
"""
from multiprocessing.connection import Client
import numpy as np
import cv2
from time import time
class ObjData:
    def __init__(self, targets):
        self.targets = targets
        
def _quantize(A, B):
    return float("inf") if B == 0 else abs((float(A)/float(B))-1.0)
class ObjectRecognition:
    
    def __init__(self, debug = False):
        """
        Initialize module members
        """
        REMOTE_IP = "127.0.0.1"
        REMOTE_PORT = 25000
        self.CAMSHOW = debug
        self.DEBUG = debug
        if self.DEBUG:
            # Prepare socket to send image data to debug-monitor
            self.sock = Client((REMOTE_IP, REMOTE_PORT), authkey=b"RobProg2")
        
        def close(self):
            if self.DEBUG:
                self.sock.close()
        self.lastSend = 0
    def close(self):
        if self.DEBUG:
            self.sock.close()
    def performObjectRecognition(self, frames, obj):
        """
        perform object recognition, returns centroid of detected object or 
        None if object not found.
        
        """
        MINMATCH = 10
        MINRATIO = 0.3
        sift = cv2.SIFT()
        targets = []
        queries = []          
        for t in obj.targets:
            kp, des = sift.detectAndCompute(t, None)
            targets.append((kp,des))
        for q in frames:
            kp, des = sift.detectAndCompute(q, None)
            queries.append((kp,des))
        t = time()
        img = None            
        if self.DEBUG and t-self.lastSend > 1.5:
                # Render an image.
                img = frames[0].copy()
                img = cv2.drawKeypoints(img, queries[0][0], None, (255,0,0))
                
        matcher = cv2.BFMatcher()
        for kp1, des1 in targets:
            good = []
            matches = []
            for kp2, des2 in queries:              
                if des1 is not None and des2 is not None:
                    matches += matcher.knnMatch(des1, des2, k=2)
                    for x in matches:
                        if len(x) < 2:
                            continue
                        m,n = x
                        if m.distance < 0.75*n.distance:
                            good.append(m)
            ratio = 0.0 if len(kp1) == 0 else float(len(good))/float(len(kp1))
            if len(good) > MINMATCH or ratio > MINRATIO:
                dst_pts = np.float32([ kp2[i.trainIdx].pt for i in good ]).reshape(-1,1,2)
                x,y,w,h = cv2.boundingRect(np.int32(dst_pts))
                hw = w/2
                hh = h/2
                posx = x+hw
                posy = y+hh
                if self.DEBUG and t-self.lastSend > 1.5:
                    cv2.rectangle(img, (x,y), (x+w,y+h), (70,255,125), 3)
                    cv2.circle(img,(posx,posy), 5, (70,255,125), -1)
                    self.sock.send(img)
                return (posx,posy)
            else:
                if self.DEBUG and t-self.lastSend > 1.5:
                    self.sock.send(img)
        return None
        