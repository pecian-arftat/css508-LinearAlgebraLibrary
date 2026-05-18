# **DOCUMENTATION-E2E-MANUAL-TEST**

## Types of Test
1. Manual Test
2. User Feedback Questionnaire.

## Manual Test Description

### How it's Conducted
To conduct a manual E2E test, I have prepared 8 arrays that store vertex coordinates in a specific shape. The first 4 arrays will store the vertex coordinates for a 3D cube, a 3D pyramid (square base), a 3D Hexagonal Pyramid (hexagonal base), and a subdivided 3D cube (3 subdivisions). Note that the 3D cube and the subdivided 3D cube are treated differently because the subdivided 3D cube will include a significant number of vertices compared to the 3D cube. To be exact, while a 3D cube includes 8 vertices, a subdivided 3D cube with 3 subdivisions will include 56 vertices. These arrays will be used in vector transformation to achieve the target transformation. The last 4 arrays will contain the vertex coordinates of the transformed shapes for each shape. These arrays will be used to compare the output transformation. 

The purpose of preparing the vertex coordinates is to simulate a developer importing 3D meshes into a project for object transformation. The last 4 transformed shapes will simulate the user's expected result. 

While having the original vertex coordinates, I will attempt to transform them using the API available in the project. When developing code and executing the coordinate transformation, I will assess performance, usability, and maintainability. Performance is measured with time and the accuracy of the output. Usability will be assessed by verifying that the function name and description are accurate. Maintainability is assessed by code readability and documentation available within the source code.

After assessing the API, I will complete the User Feedback Questionnaire to document my experience during the assessment. 

###  Goals
1. Test Performance
2. Test Usability
3. Test Maintainability
4. Test Product with the Perspective of a User

## User Feedback Questionnaire
### How it's Conducted
The User Feedback Questionnaire is an AI-generated questionnaire that I further refined to align with this mock project. It includes questions about the user's background and experience with the API. This questionnaire, if the mock project is an actual project, will be given to testers immediately to gather feedback on the current state of the project. 

### Goals
1. Gain further insight about the customer. 
2. Gain knowledge about the strength of the current project. 
3. Gain knowledge about the weaknesses of the current project.
4. Gain knowledge about the desired feature to be included. 