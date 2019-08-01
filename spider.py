% cd /content
! pip3 install tqdm
! git clone https://github.com/HsimWong/cv.git
% cd cv

import numpy as np
import cv2
import os
from tqdm import tqdm
# import cv2_imshow
from google.colab.patches import cv2_imshow
def cast2int(lst):
  return [list(map(np.uint8, x)) for x in lst]

counted = []

class Video(object):
  def __init__(self, vid_dir):
    print(vid_dir)
    gray_frames_list = []
#     frames_list = []
    self.cap = cv2.VideoCapture(vid_dir)
#     self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)   # Setting the video frame to be 256 * 144
#     self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    if not self.cap.isOpened():
      raise Exception("The video is not properly opened" % vid_dir)
      return
    else:
      frame_rendered = 0
      avg_frame = []
      count = 0
      p = 1
      for i in (range(2000)):
        p += 1
#         if p < 580:
# #           print(p)
#           continue
        success, raw_frame = self.cap.read()
        push = 0
        if not success:
          break
        cur_frame = cv2.resize(raw_frame, (32, 24))
        gray_frame = cast2int(self.rgb2gray(cur_frame))
        avg_light = self.get_average_illumination(gray_frame)
#         cv2_imshow(cur_frame)
#         print(len(cur_frame))
        if avg_light >= 70:
          push = 1
          
#           cv2_imshow(cur_frame)
#           count += 1
#           if count >= 40:
#             break
          if p < 400:
            gray_frames_list.append(gray_frame)
          else:
            push = 0
        else:
          i = 0
          push = 0
        avg_frame.append(push)
      import matplotlib.pyplot as plt
      plt.plot(avg_frame)
      plt.show()
#           frames_list.append(cur_frame)
    self.gray_frames = (gray_frames_list)
    self.cap.release()
  
  def rgb2gray(self, cur_frame):
    r, g, b = cur_frame[:, :, 0], cur_frame[:, :, 1], cur_frame[:, :, 2]
    gray = (1/3) * r + (1/3) * g + (1/3) * b
#     print(np.shape(gray))
# #     equ = cv2.equalizeHist(cv2.resize(gray, (48, 64)))
#     res = 
#     return res
    img = np.uint8((0.3333* cur_frame[:,:,0]) + \
  		np.uint8(0.3333 * cur_frame[:,:,1]) +\
			 np.uint8(0.3333 * cur_frame[:,:,2]))
#     equ = cv2.equalizeHist(img)
#     res = np.hstack((img, equ))
    
    return img

  # Only support grayscale images
  def get_average_illumination(self, frame):
    sum_val = 0
    for row in frame:
      sum_val += (sum(row) / len(row))
    sum_val /= len(frame)
    return sum_val

v = Video('spider.mp4')

def get_deviation(frames):
  temp_frame = []
  dev_frames = []
  for frame in (frames):
    if len(temp_frame) == 0:
      temp_frame = frame
      continue
    else:
#       print("enterd")
      dev_frame = np.absolute(np.subtract(frame, temp_frame))
      temp_frame = frame
      dev_frames.append(dev_frame)
  ret = np.asarray(dev_frames)
  return ret

dev_frames = get_deviation(v.gray_frames)
print(len(dev_frames))

overall_fluc = []
for frame in dev_frames:
  overall_fluc.append(np.sum(frame))

import matplotlib.pyplot as plt
plt.plot(overall_fluc)
with open("overall.txt", 'w') as f:
  f.write(str(overall_fluc))
plt.xlabel("frame index")
plt.ylabel("fluctuation")
plt.show()
plt.savefig("file.jpeg", dpi=720)