# Contour box for video WIKI

**Have you ever seen a security footage like the one below?**

<img src="https://www.zdnet.com/a/img/resize/be1554fb8d3abd941cbc81f5485b7690bbb32d13/2017/07/28/70f94cac-cb0d-4c55-845b-0261a2464bb9/nec.jpg?auto=webp&width=1280" width="700" height="400">

Notice how the surveillance camera is able to recognize the human faces in the picture and draw a contour box outside each recognized face. In some cases, the camera is even able to label the face as a VIP or blacklisted. Now I am not here to discuss the ethics of surveillance cameras being able to tell who you are. Rather, I am here to teach you how to apply a contour box outside a desired object in a streaming video.

## What You will learn:
### how to draw a contour box outside of a mono-colored object during a live stream captured by your laptop

## What you need:
* A working laptop with a webcam 
* Anaconda installed (if you don't have anaconda installed, please visit their official website for download instructions:(https://docs.anaconda.com/anaconda/install/index.html)
* Disclaimer: the author has been a **lifelong windows user**. If you, the reader is currently operating on a MAC or linux, there might be little I can do for you. 

## Let's get right into it!

### step 1: setting up the environment, installing OpenCV2

Before we start the project, it is a good practice to create a virtual environment for the project. If you have never heard of a virtual environment before, A virtual environment is a directory that contains a specific collection of packages that you have installed. By creating an environment for each of your projects, you avoid the troubles that may arise from different installed packages having conflicting dependencies. 

To create a new environment in anaconda, open up "Anaconda power shell prompt" (The fasted way to find this is to search it in your windows search bar).

![image](https://user-images.githubusercontent.com/107218842/217170945-23e6426b-59f9-420f-a457-00ce460e9076.png)

**In the power shell prompt**, type in `conda create --name YOURNAME`.

![envcrea](https://user-images.githubusercontent.com/107218842/217171786-b8e177f8-edce-4af5-ba7b-1d47135cc52a.PNG)

In the code above, I called my environment "testenv".

Now that you have created an environment, activate it** by typing `conda activate YOURNAME`

![envact](https://user-images.githubusercontent.com/107218842/217172030-c1c83b08-c038-4607-950b-cd53bf2064de.PNG)

Notice how the (base) in front of the directory changed into (testenv). Now you are in the environment you have just created!

Now that You have created and activated your environment for the project, let's install the necessary packages for the project!

For this project, You will mainly need OpenCV. What is OpenCV? Here is a quote from their official website (https://opencv.org/about/):

"OpenCV (Open Source Computer Vision Library) is an open source computer vision and machine learning software library. OpenCV was built to provide a common infrastructure for computer vision applications and to accelerate the use of machine perception in the commercial products."

Cool. OpenCV is an open-source library with a repertory of useful functions and filters for image processing and machine vision. We will be using a few functions from it in this tutorial. Before we go into detail on that, let's first install it.

With your anaconda power prompt open and environment activated from last step, type in `conda install -c menpo opencv`.

![image](https://user-images.githubusercontent.com/107218842/217174233-57d2d747-dcde-4c28-8b0f-0962310f30dd.png)

A bunch of words should show up. You might see progress bars progressing as OpenCV is being downloaded. At one point you will be prompted:

![image](https://user-images.githubusercontent.com/107218842/217174898-b2758fe7-72e4-4b8f-be3d-eb91280fd11d.png)

Naturally, type 'y' to finish the process. Great! you are now ready to write some actual code.

### Step2: Changing the color space of a frame and selecting a color to capture

Before we jump into a video stream, let's begin by thinking about one frame in the video, or a picture. 

The very first step in recognizing the mono-colored object is to transform the color space of the picture. You can do this by using the `cv.cvtColor` function in OpenCV (https://docs.opencv.org/3.4/d8/d01/group__imgproc__color__conversions.html#gga4e0972be5de079fed4e3a10e24ef5ef0aa4a7f0ecf2e94150699e48c79139ee12)

``` python
hsv_picture = cv.cvtColor(picture, cv.COLOR_BGR2HSV)
```

What the line above does is it transform the picture stored in "picture" from GBR color space to HSV color space. Why do we this? 

Here is a concise answer: OpenCV usually reads picture in a GBR format. The GBR format register color by breaking the color of every single pixel down into a combination of red, green and blue colors. However, this format does not facilitate the recognition and separation of a particular color very well. Such an operation is better performed in the HSV color space. HSV stands for "Hue", "Saturation" and "Value". Here is quote from a quora forum (https://www.quora.com/Why-do-we-convert-RGB-to-HSV) that explains the concept better than I will ever be able to:

"'Hue' represents the color, 'Saturation' represents the amount to which that respective color is mixed with white and 'Value' represents the amount to which that respective color is mixed with black (Gray level)."

In the HSV space, color is represented by the "Hue" value. "Saturation" and "Value" of a color are influenced by the lighting conditions and reflecting properties of the objects in the picture. Below is a list of useful "Hue" ranges for typical colors, provided by a in depth article on color space transformation published by OpenCV (https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html)

* Orange  0-22
* Yellow 22- 38
* Green 38-75
* Blue 75-130
* Violet 130-160
* Red 160-179

Ok. let's define a range of HSV values that our desired object will fall between:

``` python
lower_blue = np.array([80,50,50]) 
upper_blue = np.array([130,255,255])
```

lower_blue is the lower range of the blue color I want capture, upper_blue is the upper limit to the blue color I want to capture. The values are listed in the order of Hue, Saturation and Value. Using the table above, the Hue value for blue lies somewhere between 75 and 130. Here I used a lower hue limit of 80 and upper hue limit of 130. So that loosely encompasses the entire range of blue colors. As with Saturation and Value, I derived above values by intuition, as well as trial and error. It is worth noting that trial and error is probably the best way to find a desirable range for the color you want to capture. 

### Step 3: Masking the image, finding contours

At his point of the project. let's experiment with a single picture.

<img src="https://user-images.githubusercontent.com/107218842/217353606-087d7b8d-4417-4237-9e29-d7299fcd1387.jpeg" width="500" height="300">

I want to draw a contour box around the blue flower in the picture. Let's start with the steps just introduced above 

``` python
# read in image
blu = cv2.imread('blu.jpeg', 1)
# change color domain from BGR to HSV
hsv = cv2.cvtColor(blu, cv2.COLOR_BGR2HSV)
```
I have named the picture of blue flower 'blu.jpeg'. And I have placed it in the same directory (folder) with my python (.py or .ipynb) file. `cv2.imread` reads in an image file into a BGR format. 

Now I define my color ranges as the step above:

``` python
# define blue color
lower_blue = np.array([110,50,50])
upper_blue = np.array([130,255,255])
```

now lets filter out the image and keep the part we want:

``` python
mask = cv.inRange(hsv, lower_blue, upper_blue)
```

`cv.inrange(src, lowerb, upperb)` takes in 3 arguments. It searches through each index in the arrays of src. If at a certain index the values of src is between the lower and upper boundries (lowerb and upperb), the value at that index is pulled up to 255. All other entries in src are set to 0. (https://docs.opencv.org/3.4/d2/de8/group__core__array.html#ga48af0ab51e36436c5d04340e036ce981)

Let's see what our mask looks like. We can graph things with OpenCV with the following syntax:

``` python
cv2.imshow('mask', mask)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

`cv2.imshow( winname, mat )` displays an image stored in mat in a new window with name winname. This function always assume BGR format. (https://docs.opencv.org/4.x/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563)

`cv2.waitKey(0)` display the window infinitely until a key is pressed.

`cv2.destroyAllWindows()` then destroys the window.

It is worth noting that `cv2.waitkey()` and `cv2.destroyAllWindows()` should always accompany `cv2.imshow()`. Otherwise you will get some trouble with the display window and python might stop responding. 

Here is the output image:

<img src="https://user-images.githubusercontent.com/107218842/217359694-aeb00156-532e-461e-83ba-0f0f8ff77739.png" width="500" height="350">

As you can see, the `inrange` function has filtered image. The blue color in the original image that was between the defined upper and lower bound for blue color has become white. In GBR, 255 indicates maximum light, which would be white; and 0 indicates minimum light, which would be black. 

We have now generated a binary mask. It is binary since every value in the mask can only have 1 of 2 values (0 or 255), making it binary. 

With this binary image, we are ready to find the contours in the image. Use the functions below:

``` python
contours, hierarchy = cv2.findContours(image, mode, method)
```

`cv.findContours` searches for all the contours within an image. The first output contours is a Python list of all the contours in the image. Each individual contour is a Numpy array of (x, y) coordinates of boundary points of the object. The second output hierarchy has the same number of elements as the number of contours. It contains information about the next, previous, parent and child contours of every contour, and enables an examination of image topology. For our purposes hierarchy can be ignored. 

The function takes in 3 inputs. image is the binary image you have just created. mode and method are OpenCV objects that entails how the function should search for contours. We will use `mode = cv.RETR_TREE` and `method = cv.CHAIN_APPROX_SIMPLE`. If you would like to learn more about these inputs, visit the OpenCV documentation for this function: (https://docs.opencv.org/4.x/d3/dc0/group__imgproc__shape.html#gae4156f04053c44f886e387cff0ef6e08)

So the code will look something like this:

``` python
contours, hierachy = cv2.findContours(mask,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
```

Use the 'cv2.drawContours()` functions to draw the contours onto the picture:

``` python
blu_with_contour = cv2.drawContours(blu, contours, -1, [0,0,255], 2)
cv2.imshow('contour', blu_with_contour)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

Here are the results:

<img src="https://user-images.githubusercontent.com/107218842/217414142-3add9418-3d8c-4ba1-82bc-3ae652b991be.png" width="500" height="350">

First a quick explaination of 'cv2.drawContours()`:

``` python
img_with_contour = cv2.drawContours(img, contours, contourchoice, color, thickness)
```

img is the image you want to draw the contours onto, contours is the contour list you have generated. contourchoice let you choose which contours from the list you want to draw. you can refer to a desired contour by its index number in the list, or -1 to draw all contours. color is a GBR array [G, B, R], and thickness is a integer value of the thickness of the contour line you want to draw. here is link to the documentation: https://docs.opencv.org/3.4/d6/d6e/group__imgproc__draw.html#ga746c0625f1781f1ffc9056259103edbc

It is worth noting that I drew the contours onto the original image despite acquiring the contour through a binary mask. Well the 2 images have same dimensions and the entire point of generating a binary mask is to make it easier to find the contours on the original image. 

### Step4: choosing the right contour to draw a box around, and drawing the box

Ok, so we have found all the contours within the image. Now we have to draw a box around the flower in the image.

let's start by examining our contours object, which is a python list of all the contour coordinates.

![image](https://user-images.githubusercontent.com/107218842/217416581-34ecd819-a119-4ff8-84db-6f7065e2e120.png)

Wow. The program found 16 different contours. But which one is the right one?

Let's begin by drawing all the contour boxes:

``` python 
for i in contours:
    x,y,w,h = cv2.boundingRect(i)
    blu_with_box = cv2.rectangle(blu,(x,y),(x+w,y+h),(255,255,0),5)

cv2.imshow('box', blu_with_box)
cv2.waitKey(0)
cv2.destroyAllWindows()

```

<img src="https://user-images.githubusercontent.com/107218842/217451565-c3ae9bc0-1b2e-425e-9c9f-c8b4fbbb5b63.png" width="500" height="350">

First let's take a look at the code. `cv2.boundingRect(arr)` generates the specs for the smallest rectangle that would encompass a set of points. Since an element in out contour list is just a list of points that connects the contour lines. This funciton would give us the rectangle that would box the contoured object within it. See the documentation for this function at: https://docs.opencv.org/3.4/d3/dc0/group__imgproc__shape.html#ga103fcbda2f540f3ef1c042d6a9b35ac7

`out = cv2.rectangle(img, pt1, pt2, color, thickness)` draws a rectangle on img at the specified dimension outlined by pt1 and pt2. pt1 and pt2 are both set of 2 points indicating the coordinate of the rectangle vertices. It is apprent that `cv2.boundingRect(i)` outputted x, y as the diagonal vertices of the rectangle, and w, h as the width and height of the rectangle. So the points to the rectangle would be (x, y), (x+w, y+h). Color specfifies the color of the lines of the rectangle. again it is inputted in a GBR format of [G, B, R]. Thickness is a single value indicating the thickness of the line of the rectangle. See the documentation for the function at: https://docs.opencv.org/3.4/d6/d6e/group__imgproc__draw.html#ga346ac30b5c74e9b5137576c9ee9e0e8c 

Ok. For this image we will probably want to select the contour with the largest area inside the contour. We can find the area inside each contour by a simple function: `cv2.contourArea(contours[i])`. This function simply returns the area inside a specific contour item. Let's find the largest contour area:

``` python
contour_size = np.ones(len(contours))
for i in range(len(contours)):
    contour_size[i] = cv2.contourArea(contours[i])
   
max(contour_size)
```

In the above code, I initialized a list of ones with the same length as the contour list. Then I used a for loop to find the contour area of every contour and fill up the newly initialized list with these values. After that I used the max() function to find the contour with the largest area inside it. 

OK. let's try drawing a box only around the selected contour:


``` python
for i in contours:
    if cv2.contourArea(i) == max(contour_size):
        x,y,w,h = cv2.boundingRect(i)
        blu_with_box = cv2.rectangle(blu,(x,y),(x+w,y+h),(255,255,0),5)

cv2.imshow('box', blu_with_box)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

Here is the output:

<img src="https://user-images.githubusercontent.com/107218842/217455426-5137af09-750c-45cc-9ea5-4231331e73df.png" width="500" height="350">

Great! We have successfully found out how to draw a box outside of a deisred mono-colored object in an image! The only thing left to do is to extend this technique to a streaming video. 

### Final Step(Step 5): Appling everything to a video 

OK. Let's put everything we've learnt together!

We start out code with an instruction to turn on the camera:

```python
cap = cv.VideoCapture(0)

```

This function turns on your webcam for recording.

Then, start a while loop. We want to code to loop indefinitely until we shut it down. Put all the code in the while loop below:

```python
while(1):
    # enter your codes for contouring and boxing 

```

The first line within the loop captures a frame from the camera:

```python
_, frame = cap.read()

```

The frame is the picture that is taken by your webcam. Now we can apply everything we have just learnt to this picture:


step2:

``` python
    # Convert BGR to HSV
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    # define range of blue color in HSV
    lower_blue = np.array([80,50,50])
    upper_blue = np.array([130,255,255])
```
step3:

``` python
    # Threshold the HSV image to get only blue colors
    mask = cv.inRange(hsv, lower_blue, upper_blue)
    # Bitwise-AND mask and original image
    res = cv.bitwise_and(frame,frame, mask= mask)
    
    # use median filter to filter out the camera noise 
    mask_sm = cv.medianBlur(mask, 13)

    # find contours 
    contours, hierachy = cv.findContours(mask_sm,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
 
    # draw all contours(for analysis)
    cv.drawContours(frame, contours, -1, 255, 3)
    
```
step4:

``` python
    #find largest contour area
    contour_size = np.ones(len(contours))
    for i in range(len(contours)):
        contour_size[i] = cv.contourArea(contours[i])
    
    # graph the largest contour 
    for i in contours:
        if cv.contourArea(i) == max(contour_size):
            x,y,w,h = cv.boundingRect(i)
            cv.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)
            cv.rectangle(mask_sm,(x,y),(x+w,y+h),(0,0,255),2)
            
    # put the frame in the window 
    cv.imshow('frame',frame)
    cv.imshow('mask',mask_sm)
    cv.imshow('res',res)

```

Do notice how I added in a median filter in step3. The median filter is commonly used in image processing to smooth out salt and pepper noise. Due to the quality of your webcam this step might be completely unnecessary. However, my webcam generated a lot of noise when I was working on this project and using a noise cancelling filter really helped prevent noise interfering with the object recognition task. 

Here is a clip of the result:

https://user-images.githubusercontent.com/107218842/217465337-28eff54a-dd5d-46f4-934b-62a8b8111def.mp4

<video src='[your URL here](https://user-images.githubusercontent.com/107218842/217465337-28eff54a-dd5d-46f4-934b-62a8b8111def.mp4)' width=180/>

As you can see in the video. The findContour function still picked up noises from the lighting condition of the room as well as the camera. However, choosing the largest contour area allowed us to still track the blue card in my hand. 

Thank you for reading this tutorial. I hope you have learned something useful. 

Here is the entire code:

``` python
#code sources:
#https://code.likeagirl.io/finding-dominant-colour-on-an-image-b4e075f98097
#https://docs.opencv.org/4.x/df/d9d/tutorial_py_colorspaces.html

#improvements:
# invert mask for contouring 
# add in contour tracking
# blur mask to elimminate noise from camera 
# add in threshold for contour area to select correct contour of the desired object 
import cv2 as cv
import numpy as np


cap = cv.VideoCapture(0)

# for recoding purposes
'''
width= int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
height= int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))

writer= cv.VideoWriter('detection.mp4', cv.VideoWriter_fourcc(*'DIVX'), 20, (width,height))
'''

while(1):
    # Take each frame
    _, frame = cap.read()
    # Convert BGR to HSV
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    # define range of blue color in HSV
    lower_blue = np.array([80,50,50])
    upper_blue = np.array([130,255,255])
    # Threshold the HSV image to get only blue colors
    mask = cv.inRange(hsv, lower_blue, upper_blue)
    # Bitwise-AND mask and original image
    res = cv.bitwise_and(frame,frame, mask= mask)
    
    # use median filter to filter out the camera noise 
    mask_sm = cv.medianBlur(mask, 13)

    # find contours 
    contours, hierachy = cv.findContours(mask_sm,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
 
    # draw all contours(for analysis)
    cv.drawContours(frame, contours, -1, 255, 3)
    
    #find largest contour area
    contour_size = np.ones(len(contours))
    for i in range(len(contours)):
        contour_size[i] = cv.contourArea(contours[i])
    
    # graph the largest contour 
    for i in contours:
        if cv.contourArea(i) == max(contour_size):
            x,y,w,h = cv.boundingRect(i)
            cv.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)
            cv.rectangle(mask_sm,(x,y),(x+w,y+h),(0,0,255),2)
            
    # put the frame in the window 
    cv.imshow('frame',frame)
    cv.imshow('mask',mask_sm)
    cv.imshow('res',res)
    
    #writer.write(frame)
    

    k = cv.waitKey(5) & 0xFF
    if k == 27:
        break
cap.release()
writer.release()
cv.destroyAllWindows()

```


References:
* https://opencv.org/about/
* https://docs.opencv.org/3.4/d8/d01/group__imgproc__color__conversions.html#gga4e0972be5de079fed4e3a10e24ef5ef0aa4a7f0ecf2e94150699e48c79139ee12
* https://www.quora.com/Why-do-we-convert-RGB-to-HSV
* https://www.opencv-srf.com/2010/09/object-detection-using-color-seperation.html
* https://docs.opencv.org/3.4/d2/de8/group__core__array.html#ga48af0ab51e36436c5d04340e036ce981
* https://docs.opencv.org/4.x/d7/dfc/group__highgui.html#ga453d42fe4cb60e5723281a89973ee563
* https://docs.opencv.org/4.x/d3/dc0/group__imgproc__shape.html#gae4156f04053c44f886e387cff0ef6e08
* https://docs.opencv.org/3.4/d6/d6e/group__imgproc__draw.html#ga746c0625f1781f1ffc9056259103edbc
* https://docs.opencv.org/3.4/d3/dc0/group__imgproc__shape.html#ga103fcbda2f540f3ef1c042d6a9b35ac7
* https://docs.opencv.org/3.4/d6/d6e/group__imgproc__draw.html#ga346ac30b5c74e9b5137576c9ee9e0e8c
* https://code.likeagirl.io/finding-dominant-colour-on-an-image-b4e075f98097
* https://docs.opencv.org/4.x/df/d9d/tutorial_py_colorspaces.html

