# calibration-augmented-reality

Nick Cantalupa and Sean Duffy

https://www.youtube.com/watch?v=44_nmsOVgSE

https://drive.google.com/file/d/1eOVSKuasedi-_3aCDoNpGlE2v6jYn-sX/view?usp=sharing

We compiled the code using VS Code and CMake, as well as CLion. 

### Build instructions:
- Clone Repo
- Must have OpenCV installed on OS
- run commands: 
    - mkdir build
    - cd build
    - cmake ..
    - make
    - ./calibration-AR 

### Usage:
This program is set to calibrate on a 9x6 checkerboard pattern. Print out this pattern or have it displayed on a screen in view of the camera to start calibration. 
- 's' to save the current frame as a calibration datapoint. Must save > 4 calibration images to calibrate camera
- 'c' to calibrate camera 
- '1' to display sphere on checkerboard pattern
- '2' to display wireframe paper airplane

Our extension is the creation of the spherical points using the object_points.py file. The photos can be seen in the report or replicated as seen in the instructions above.

We are submitting late with permission from Prof. Maxwell due to personal reasons.
