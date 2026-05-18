# **Analysis of Most Valuable Scenario**



## Scenarios for Automated E2E tests

1. Generate E2E test using the C++ unit test and integration test with the following scenario: A graphic programmer has the vertex coordinates of a 3D unit cube (length of 2) and wants to rotate the cube 45 degrees around the x-axis and then rotate 45 degrees around the y-axis.
2. Generate another E2E test using the C++ unit test and integration test with the following scenario: A graphic programmer has the vertex coordinates of a shape, but does not know whether the shape is a box. To verify, the programmer uses dot4 and cross3 to confirm that it is indeed a box.



## Most Valuable Scenario

* Generate E2E test using the C++ unit test and integration test with the following scenario: A graphic programmer has the vertex coordinates of a 3D unit cube (length of 2) and wants to rotate the cube 45 degrees around the x-axis and then rotate 45 degrees around the y-axis.



## Explanation

The reason for choosing the first scenario as the most valuable is that developers who work with 3D space typically interact with 3D cubes. Scaling and translating the vertex coordinates of 3D cubes is very easy, as it involves only vector addition and multiplication. Challenges come from the rotation of the objects. It requires much more complex calculations and is prone to numerical drifting. This is much more prevalent when all the vertex coordinates of a cube are rotated, and the developer of this project must guarantee the rotation's accuracy within the target error tolerance. 



This scenario also provides an opportunity to load-test the API to verify that it operates at an acceptable performance level.



