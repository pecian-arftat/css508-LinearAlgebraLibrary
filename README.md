5/3/2026 Updates

Added a YAML file to enable GitHub Actions.



Added rotateEulerX function. The purpose of adding this is to test sequential rotation.

Added rotateEulerY function. The purpose of adding this is to test sequential rotation.

Modified quatFromAxisAngle function to handle normalization internally.





Testing:

Prerequisite:
Docker Desktop



Steps:

1. Clone the repository to a desired location.
2. Open a command line interface and navigate to src folder. This folder includes the Dockerfile.
3. Build the Dockerfile using the following command: docker build -t "Your Image Name Goes Here"
4. Once the image is created, run the application using this command: docker run "You Image Name Goes Here"

