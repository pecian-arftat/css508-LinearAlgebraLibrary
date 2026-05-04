Manual Testing 



The aim of manual testing would be to simulate possible ways the client uses the API that were not covered by the unit and integration tests.



Test 1 tests a series of rotations that rotate a vector and return it to the original vector.



Test 2 tests whether a complete 360-degree rotation on each axis would cause any bugs. 



Test 3 tests whether an incremental 45-degree rotation on a single axis would cause any bugs. 



Test 4 stress test Euler angle rotation for numerical stability by rotating a vector incrementally by 1 degree to 360 degrees for all axes. 

NOTE: It is expected that Test 4 will fail, as no applicable mitigation method has been implemented for the Euler rotation function.



Test 5 stress test Quaternion rotation for numerical stability by rotating a vector incrementally by 1 degree to 360 degrees for all axes.

NOTE: It is expected that Test 5 will fail, as no mitigation method has been implemented for the Quaternion rotation function.





Running Manual Testing Guide: 

To run the manual testing, please exclude the test.cpp file, as it also includes a main function that would cause a compilation error.

