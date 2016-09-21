#!/usr/bin/env python
'''
Assignment 1 - Intelligent Interactive Systems
Spring 2016

@author Jimmy Holm
'''

import numpy as np
import cv2
import os.path

class Assignment1:
    def __init__(self):
        self.cap = cv2.VideoCapture(0)
        self.font = cv2.FONT_HERSHEY_COMPLEX_SMALL
        self.fscale = 1
        self.fthick = 1
        self.hist = 0
        
    def printText(self, frame, text, color):
        baseline = 0
        (w,h), baseline = cv2.getTextSize(text, self.font, self.fscale, self.fthick)
        cv2.rectangle(frame, (8,8), (w+12,h+12), (0,0,0),-1)
        cv2.putText(frame, text, (10,10+h), self.font, self.fscale, color, self.fthick)

    def show_hist(self):
        bin_count = self.hist.shape[0]
        bin_w = 24
        img = np.zeros((256, bin_count*bin_w, 3), np.uint8)
        for i in xrange(bin_count):
            h = int(self.hist[i])
            cv2.rectangle(img, (i*bin_w+2, 255), ((i+1)*bin_w-2, 255-h), (int(180.0*i/bin_count), 255, 255), -1)
        img = cv2.cvtColor(img, cv2.COLOR_HSV2BGR)
        cv2.imshow('hist', img)

        
    def run(self):
        # Declare paths to cascade masks.
        cascades_path = "/usr/local/share/OpenCV/haarcascades/"
        face_path = os.path.join(cascades_path, "haarcascade_frontalface_default.xml")

        #Setup cascades.
        face_cascade = cv2.CascadeClassifier(face_path)
        
        # State variable either -1, 0 or 1. -1 means idle.
        # 0 means no face detected, keep looking.
        # 1 means face detected, perform camshift operation to track.
        face_roi = None
        state = -1 # Initially, idle.
        (ow, oh, wt, ht) = (0, 0, 0,0)
        while True:
            # Read frame from webcamera
            ret, frame = self.cap.read()
            if state is -1:
                self.printText(frame, "Idle ('D' to detect.)", (0,0,255))
                ch = 0xFF & cv2.waitKey(1)
                if ch is 68 or ch is 100:
                    state = 0
            elif state is 0:
                face_roi = None
                # Cascades trained on gray scale data so desaturise captured frames.
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                faces = face_cascade.detectMultiScale(gray, 1.3,5)
                # Detect faces, pick first one detected and set to track..
                # Draw return oi of found face.
                if len(faces) > 0:
                    face_roi = faces[0]
                    (x,y,w,h) = face_roi
                    state = 1
                    continue
                self.printText(frame, "Detecting", (0,255,255))
            elif state is 1:
                # Convert frame to HSV color space.
                hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
                hsv_roi = hsv[y+20:y+h-40, x+20:x+w-40] # Tighten the roi to backproject
                # Grab histogram from  roi.
                mask = cv2.inRange(hsv, np.array((0., 60., 32.)), np.array((180., 255., 255.)))
                mask_roi = mask[y+20:y+h-40, x+20:x+w-40]
                self.hist = cv2.calcHist( [hsv_roi], [0], mask_roi, [16], [0, 180])
                cv2.normalize(self.hist, self.hist, 0, 255, cv2.NORM_MINMAX)
                self.hist = self.hist.reshape(-1)
                # Calculate back projection
                proj = cv2.calcBackProject([hsv], [0], self.hist, [0, 180], 1);
                proj &= mask
                term_criteria = (cv2.TERM_CRITERIA_COUNT | cv2.TERM_CRITERIA_EPS, 1, 10)
                track_box, face_roi = cv2.CamShift(proj, (x,y,w,h), term_criteria)
                (rx,ry,rw,rh) = face_roi
                cv2.rectangle(frame, (rx,ry), (rx+rw, ry+rh), (255,0,0), 2)
                self.printText(frame, "Tracking", (0,255,0))
            # Display frame to window
            cv2.imshow('camwindow', frame)
            ch = 0xFF & cv2.waitKey(1)
            if ch == 27:
                break
        cv2.destroyAllWindows()

if __name__ == "__main__":
    run = Assignment1()
    run.run()
    
