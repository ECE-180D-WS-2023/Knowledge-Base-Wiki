# Pose Recognition using OpenCV and MediaPipe

[OpenCV](https://docs.opencv.org/4.x/d0/de3/tutorial_py_intro.html) is a python library designed to solve computer vision problems. It provides some tools for image and video processing such as object detection. For example, it can follow a blue object as was done in Lab 1. 

[MediaPipe](https://google.github.io/mediapipe/) is an open-source framework developed by Google which offers cross-platform, customizable Machine Learning solutions for live and streaming media. It offers a number of pre-trained models that can recognize face and body landmarks as well as track objects.

This tutorial will present how OpenCV and MediaPipe can be used to recognize different poses done with a body and face.


<p align="center">
<img width="598" alt="Screenshot_2023-02-08_at_6 26 04_PM" src="https://user-images.githubusercontent.com/74027562/217741279-d4e9a89b-67f3-435b-ada3-f5353d0f856e.png">
</p>

# Steps to Follow

1. Setting up OpenCV and MediaPipe
2. Collecting Data, Training and Evaluating the ML model
3. Classify the poses

# 1. Setting up OpenCV and MediaPipe

First we will need to install the independencies:

```python
!pip install mediapipe opencv-python pandas scikit-learn
```

(For M1/M2: replace mediapipe with mediapipe-silicon)

The python libraries pandas and scikit-learn will later be used to train the data using ML.

```python
import mediapipe as mp
import cv2
```

```python
mp_drawing = mp.solutions.drawing_utils
mp_holistic = mp.solutions.holistic
```

MediaPipe’s mp_drawing helps draw the landmarks while mp_holistic gives the landmark detections that will be needed to detect the pose.

```python
import csv
import os
import numpy as np
```

CSV is used to work with lists of data.

OS is used to work with files.

Numpy is used to work with arrays, lists, and matrices.

# 2. Collecting Data, Training and Evaluating the ML model

### 1. Collecting Data

```python
num_coords = len(results.pose_landmarks.landmark)+len(results.face_landmarks.landmark)
```

```python
landmarks = ['class']
for val in range(1, num_coords+1):
    landmarks += ['x{}'.format(val), 'y{}'.format(val), 'z{}'.format(val), 'v{}'.format(val)]
```

```python
with open('coords.csv', mode='w', newline='') as f:
    csv_writer = csv.writer(f, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    csv_writer.writerow(landmarks)
```

These block codes create a new CSV file “coords.csv” which have 2005 columns:

- 1 column for the Class name
- 501*4 columns for the 501 landmark’s of body (pose) and face:
    - We multiply by 4 for the x, y, z coordinates and visibility (which means if a landmark is present in the frame or not: can take 0 or 1 values).

“coords.csv” will allow to store all the landmarks collected, and will be used as an input to train the ML model.

### Repeat n times

n represents the number of classes/poses your model will be able to recognize.

```python
class_name = "Wakanda Forever"
```

This represents the class you will be collecting data points for. (You may change “Wakanda Forever” to any class you’d like).

```python
cap = cv2.VideoCapture(0)
# Initiate holistic model
with mp_holistic.Holistic(min_detection_confidence=0.5, min_tracking_confidence=0.5) as holistic:
    
    while cap.isOpened():
        ret, frame = cap.read()
        
        # Recolor Feed
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image.flags.writeable = False        
        
        # Make Detections
        results = holistic.process(image)
        # print(results.face_landmarks)
        
        # face_landmarks, pose_landmarks, left_hand_landmarks, right_hand_landmarks
        
        # Recolor image back to BGR for rendering
        image.flags.writeable = True   
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        
        # 1. Draw face landmarks
        mp_drawing.draw_landmarks(image, results.face_landmarks, mp_holistic.FACEMESH_TESSELATION, 
                                 mp_drawing.DrawingSpec(color=(80,110,10), thickness=1, circle_radius=1),
                                 mp_drawing.DrawingSpec(color=(80,256,121), thickness=1, circle_radius=1)
                                 )
        
        # 2. Right hand
        mp_drawing.draw_landmarks(image, results.right_hand_landmarks, mp_holistic.HAND_CONNECTIONS, 
                                 mp_drawing.DrawingSpec(color=(80,22,10), thickness=2, circle_radius=4),
                                 mp_drawing.DrawingSpec(color=(80,44,121), thickness=2, circle_radius=2)
                                 )

        # 3. Left Hand
        mp_drawing.draw_landmarks(image, results.left_hand_landmarks, mp_holistic.HAND_CONNECTIONS, 
                                 mp_drawing.DrawingSpec(color=(121,22,76), thickness=2, circle_radius=4),
                                 mp_drawing.DrawingSpec(color=(121,44,250), thickness=2, circle_radius=2)
                                 )

        # 4. Pose Detections
        mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_holistic.POSE_CONNECTIONS, 
                                 mp_drawing.DrawingSpec(color=(245,117,66), thickness=2, circle_radius=4),
                                 mp_drawing.DrawingSpec(color=(245,66,230), thickness=2, circle_radius=2)
                                 )
        # Export coordinates
        try:
            # Extract Pose landmarks
            pose = results.pose_landmarks.landmark
            pose_row = list(np.array([[landmark.x, landmark.y, landmark.z, landmark.visibility] for landmark in pose]).flatten())
            
            # Extract Face landmarks
            face = results.face_landmarks.landmark
            face_row = list(np.array([[landmark.x, landmark.y, landmark.z, landmark.visibility] for landmark in face]).flatten())
            
            # Concate rows
            row = pose_row+face_row
            
            # Append class name 
            row.insert(0, class_name)
            
            # Export to CSV
            with open('coords.csv', mode='a', newline='') as f:
                csv_writer = csv.writer(f, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
                csv_writer.writerow(row) 
            
        except:
            pass
                        
        cv2.imshow('Raw Webcam Feed', image)

        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()
```

In the block of code above, we are capturing the frames from our video feed. We set the thresholds of our mp_holistic solution to 0.5. This means that MediaPipe will consider a landmark tracking successful when it is at least 50% sure. We then use OpenCV to convert the colors of the from BGR (Blue, Green, Red) to RGB (Red, Green, Blue), as OpenCV works with BGR while MediaPipe works with RGB. We also set the image’s writeable property to false to save some memory before processing the image with MediaPipe’s holistic. We store the output into results. Once we are done, we can do the steps in the inverse order. 

The next step is to draw the face, hands, and pose (here pose represents the main landmarks on your body like shoulder and hips). This is done using mp_drawing which we defined earlier. It allows us to see all the tessellations of our body on the live feed. 

The final step is to extract those same landmarks and store them all in a continuous array and write them to out “coords.csv” file.

📝 In order to close the window, press “q”.

📝 The longer it takes you to close the window, the more data you’ll be able to collect. It will take longer to train the data, but you will get more accurate results. I think 15 seconds of capturing will give acceptable results.

### 2. Training the ML model

```python
import pandas as pd
from sklearn.model_selection import train_test_split
```

The train_test_split is used to split data into training data and testing data.

```python
df = pd.read_csv('coords.csv')
X = df.drop('class', axis=1)
y = df['class']
```

Here X represents all the features from “coords.csv” excluding the Class name while y represents the class name.

```python
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1234)
```

This line splits X and y into two categories: training (70%) and testing (30%) in a random way.

```python
from sklearn.pipeline import make_pipeline 
from sklearn.preprocessing import StandardScaler 

from sklearn.linear_model import LogisticRegression, RidgeClassifier
from sklearn.ensemble import RandomForestClassifier, GradientBoostingClassifier
```

These are the classification model dependancies.

- The make_pipeline function creates a ML pipeline.
- The StandardScaler class is used to normalize the data.
- The last two lines represent four different classification algorithms.

We will pick the best out of the four algorithms at the end to classify the poses.

 

```python
pipelines = {
    'lr':make_pipeline(StandardScaler(), LogisticRegression()),
    'rc':make_pipeline(StandardScaler(), RidgeClassifier()),
    'rf':make_pipeline(StandardScaler(), RandomForestClassifier()),
    'gb':make_pipeline(StandardScaler(), GradientBoostingClassifier()),
}
```

Here, we are creating four different pipelines (another way to look at it is we are creating four different machine Learning models).

```python
fit_models = {}
for algo, pipeline in pipelines.items():
    model = pipeline.fit(X_train, y_train)
    fit_models[algo] = model
```

We train our four different models with our training data.

### 3. Evaluating the ML model

```python
from sklearn.metrics import accuracy_score
import pickle
```

The accuracy_score function is used to evaluate the accuracy of a classifier.

The pickle library is used to save ML models to disk.

```python
for algo, model in fit_models.items():
    yhat = model.predict(X_test)
    print(algo, accuracy_score(y_test, yhat))
```

We loop over the four ML models, and predict the class of our testing set X_test. We then output the accuracy score of each model which is a number in [0, 1] where 1 means our predictions are 100% accurate (y_test contains the actual expected classes, while y_hat contains the predicted classes).

```python
with open('body_language.pkl', 'wb') as f:
    pickle.dump(fit_models['rf'], f)
```

We use the pickle library to save our best model, in my case rf (has the highest accuracy score), and save it to the file body_language.pkl. If your other models have higher accuracy score, then change 'rf' to 'lr', 'rc', or 'gb'.

```python
with open('body_language.pkl', 'rb') as f:
    model = pickle.load(f)
```

Although you don’t have to save the model if you are running all the code above in one go, it is good practice to do so as you don’t want to waster computing power every time training the model if the data hasn’t changed.

# 3. Classify the poses

```python
cap = cv2.VideoCapture(0)
# Initiate holistic model
with mp_holistic.Holistic(min_detection_confidence=0.5, min_tracking_confidence=0.5) as holistic:
    
    while cap.isOpened():
        ret, frame = cap.read()
        
        # Recolor Feed
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image.flags.writeable = False        
        
        # Make Detections
        results = holistic.process(image)
        
        # face_landmarks, pose_landmarks, left_hand_landmarks, right_hand_landmarks
        
        # Recolor image back to BGR for rendering
        image.flags.writeable = True   
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        
        # 1. Draw face landmarks
        mp_drawing.draw_landmarks(image, results.face_landmarks, mp_holistic.FACEMESH_TESSELATION, 
                                 mp_drawing.DrawingSpec(color=(80,110,10), thickness=1, circle_radius=1),
                                 mp_drawing.DrawingSpec(color=(80,256,121), thickness=1, circle_radius=1)
                                 )
        
        # 2. Right hand
        mp_drawing.draw_landmarks(image, results.right_hand_landmarks, mp_holistic.HAND_CONNECTIONS, 
                                 mp_drawing.DrawingSpec(color=(80,22,10), thickness=2, circle_radius=4),
                                 mp_drawing.DrawingSpec(color=(80,44,121), thickness=2, circle_radius=2)
                                 )

        # 3. Left Hand
        mp_drawing.draw_landmarks(image, results.left_hand_landmarks, mp_holistic.HAND_CONNECTIONS, 
                                 mp_drawing.DrawingSpec(color=(121,22,76), thickness=2, circle_radius=4),
                                 mp_drawing.DrawingSpec(color=(121,44,250), thickness=2, circle_radius=2)
                                 )

        # 4. Pose Detections
        mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_holistic.POSE_CONNECTIONS, 
                                 mp_drawing.DrawingSpec(color=(245,117,66), thickness=2, circle_radius=4),
                                 mp_drawing.DrawingSpec(color=(245,66,230), thickness=2, circle_radius=2)
                                 )
        # Export coordinates
        try:
            # Extract Pose landmarks
            pose = results.pose_landmarks.landmark
            pose_row = list(np.array([[landmark.x, landmark.y, landmark.z, landmark.visibility] for landmark in pose]).flatten())
            
            # Extract Face landmarks
            face = results.face_landmarks.landmark
            face_row = list(np.array([[landmark.x, landmark.y, landmark.z, landmark.visibility] for landmark in face]).flatten())
            
            # Concate rows
            row = pose_row+face_row

            # Make Detections
            X = pd.DataFrame([row])
            body_language_class = model.predict(X)[0]
            body_language_prob = model.predict_proba(X)[0]
            print(body_language_class, body_language_prob)
            
            # Grab ear coords
            coords = tuple(np.multiply(
                            np.array(
                                (results.pose_landmarks.landmark[mp_holistic.PoseLandmark.LEFT_EAR].x, 
                                 results.pose_landmarks.landmark[mp_holistic.PoseLandmark.LEFT_EAR].y))
                        , [640,480]).astype(int))
            
            cv2.rectangle(image, 
                          (coords[0], coords[1]+5), 
                          (coords[0]+len(body_language_class)*20, coords[1]-30), 
                          colors[np.argmax(body_language_prob)], -1)
            cv2.putText(image, body_language_class, coords, 
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2, cv2.LINE_AA)
            
            image = prob_viz(body_language_prob,["Happy","Sad","Wakanda Forever"],image,colors)
            
        except:
            pass
                        
        cv2.imshow('Raw Webcam Feed', image)

        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()
```

The beginning of the code here is similar to when we are collecting data. 

The # Make detections section is the most important as it detects the pose:

- X = pd.DataFrame([row]) — the input row contains all of our coordinates (x, y, z, visibility)
- body_language_class = model.predict(X)[0] — predicts what class we have
- body_language_prob = model.predict_proba(X)[0] — predicts the probability of each class
- print(body_language_class, body_language_prob)

The # Grab ear coords section grabs the ears coordinates and scales them to the screen size. We use those coordinates to display what class is detected close to your ear.

The prob_viz function is described below and represents another fun way to display the classes!

```python
colors = [(245,117,16), (117,245,16), (16,117,245)]
def prob_viz(res, actions, input_frame, colors):
    output_frame = input_frame.copy()
    for num, prob in enumerate(res):
        cv2.rectangle(output_frame, (0,60+num*40), (int(prob*300), 90+num*40), colors[num], -1)
        cv2.putText(output_frame, actions[num] + ' ' + str(res[num]), (0, 85+num*40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255,255,255), 2, cv2.LINE_AA)
        
    return output_frame
```

The function outputs all three classes (in my case “Happy”, “Sad”, and “Wakanda Forever”) to the video feed with their respective probabilities in an interactive way (the rectangle widens and shrinks depending on the probability of each class). Feel free to modify the colors :)

This is the final result:

<p align="center">
  <img src="https://user-images.githubusercontent.com/74027562/217741351-ac93e9ee-f1a7-46fb-9e54-1198b328ec5c.gif" alt="animated" />
</p>


**********************References:**********************

[OpenCV](https://docs.opencv.org/4.x/d0/de3/tutorial_py_intro.html)

[MediaPipe](https://google.github.io/mediapipe/)

[AI Body Language Decoder with MediaPipe and Python in 90 Minutes by Nicholas Renotte](https://www.youtube.com/watch?v=We1uB79Ci-w)

[Sign Language Detection using Action Recognition with Python | LSTM Deep Learning Model by Nicholas Renotte](https://www.youtube.com/watch?v=doDUihpj6ro&t=6050s)
