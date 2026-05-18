# **3D Vector Transformation API**

## Updates
---
### 5/17/2026 Updates
Added PRODUCT-QUESTIONNAIRE-ORIGINAL. Original copy of questionnaire to be given to test after tests.

Added PRODUCT-QUESTIONNAIRE-SAMPLE-SUBMISSION. Filled out copy of the questionnaire. It is stated sample but, this will be feedback to the current state of the project.

Added DOCUMENTATION-E2E-MANUAL-TEST. 

Added TEST-REPORT(E2E-TEST). 

Added ANALYSIS-BEST-SCENARIO. Analysis of scenario used in the automated E2E test.

Added automated E2E section to test.cpp. 

---
### 5/3/2026 Updates 

Added a YAML file to enable GitHub Actions.

Added rotateEulerX function. The purpose of adding this is to test sequential rotation.

Added rotateEulerY function. The purpose of adding this is to test sequential rotation.

Modified quatFromAxisAngle function to handle normalization internally.

---
## Purpose
It's purpose is to provide developers an easy tool to transform 3D vector. 

---
## READ THIS BEFORE USAGE!
When using this API, it is necessary to keep in mind the orientations of each axis.

| Axis | Direction |
|------|-----------|
| +z | Up |
| -z | Down |
| +x | Right |
| -x | Left |
| +y | Inward |
| -y | Outward |

If the API is used in any other coordinate system, there will be unexpected results.

---
## Features

| Name | Explanation |
|------|-------------|
| Vec3 | A struct that stores information in order of x, y, z. Intended for Cartesian coordinates. |
| Vec3.operator+ | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec3.operator- | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec3.operator* | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec3.operator/ | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec4 | A struct that stores information in order of x, y, z, w. Intended for homogeneous coordinates. |
| Vec4.operator+ | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec4.operator- | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec4.operator* | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Vec4.operator/ | Operator override to ease vector calculation. Must match dimension for proper calculation. |
| Quat | A struct that stores information in order of x, y, z, w. Intended for storing Quaternion. |
| dot3 | This function takes Vec3 objects and returns the dot product of the two vectors. |
| cross3 | This function takes Vec3 objects and returns new Vec3 that is perpendicular to input vectors. |
| rotateEulerX | This function takes in a single Vec3 object and a degree angle to rotate about x axis. |
| rotateEulerY | This function takes in a single Vec3 object and a degree angle to rotate about y axis. |
| rotateEulerZ | This function takes in a single Vec3 object and a degree angle to rotate about z axis. |
| magnitude | This function takes in a single Vec3 and returns the magnitude of the vector. |
| quatFromAxisAngle | This function takes a Vec3 vector object and angle of degree to return a corresponding quaternion. |
| normalizeQuat | This function take in a Quat object and returns normalized quaternion. |
| quatMultiply | This function takes two Quat object and returns the muliplied quaternion. |
| quatRotate | This function takes Quat object (used for rotation) and Vec3 object (intended to be rotated) to rotate Vec3. |

---
## Test Yourself!

### Prerequisite:
Docker Desktop

### Steps:

1. Clone the repository to a desired location.
2. Open a command line interface and navigate to src folder. This folder includes the Dockerfile.
3. Build the Dockerfile using the following command: docker build -t "Your Image Name Goes Here"
4. Once the image is created, run the application using this command: docker run "You Image Name Goes Here"

### Here's how it should look on your cli (I've used "test" for my images name):
```bash
docker build -t test
docker run test
```

