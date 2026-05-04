// When testing this file, please exclude the "test.cpp" file as it contains the main test suite.

// This file contains manual tests for the linear algebra library. 
// These tests are designed to be run independently of the main test suite and can be used for quick verification of specific functionalities or 
// for debugging purposes. 
// Each test applies a series of transformations to a vector and checks the final result against an expected value, printing the results to the 
// console for easy verification.

#include "pch.h"
#include "LinearAlgebra.h"



int main()
{
	// Manual Test

	
	// This test applies a series of rotations to a vector and checks the final result.
	Vec3 expected{ 1,2,3 };
	double magnitudeBefore = magnitude(expected);
	Vec3 normalized = expected * (1.0 / magnitudeBefore); // normalize to avoid overflow
	Vec3 rotated = rotateEulerZ(normalized, 90);
	rotated = rotateEulerX(rotated, -90);
	rotated = rotateEulerY(rotated, 90);
	rotated = rotateEulerX(rotated, 90);
	Vec3 final = rotateEulerZ(rotated, 180);

	std::cout << "Test: Sequential rotations on vector (1, 2, 3)" << std::endl;
	std::cout << "Applied rotations: Z(90), X(-90), Y(90), X(90), Z(180)" << std::endl;
	std::cout << "Expected magnitude: " << magnitudeBefore << std::endl;
	std::cout << "Magnitude before: " << magnitudeBefore << std::endl;
	std::cout << "Original vector: (" << expected.x << ", " << expected.y << ", " << expected.z << ")" << std::endl;
	std::cout << "Final rotated vector: (" << final.x << ", " << final.y << ", " << final.z << ")" << std::endl;
	if (almostEqualVec3(final, expected, 1e-6)) {
		std::cout << "Test passed!" << std::endl;
	} else {
		std::cout << "Test failed!" << std::endl;
	}

	// This test applies complete 360 degree rotations around each axis to ensure the vector returns to its original position.
	Vec3 expected2{ -3, -1, 2 };
	Vec3 normalizedexpected2 = expected2 * (1.0 / magnitude(expected2)); // normalize to avoid overflow
	Vec3 rotatedexpected2 = rotateEulerZ(normalizedexpected2, 360);
	rotatedexpected2 = rotateEulerX(rotatedexpected2, 360);
	rotatedexpected2 = rotateEulerY(rotatedexpected2, 360);
	rotatedexpected2 = rotateEulerX(rotatedexpected2, 360);
	final = rotateEulerZ(rotatedexpected2, 360);
	final = final * magnitude(expected2); // scale back to original magnitude

	std::cout << "\nTest: Complete 360 degree rotations on vector (-3, -1, 2)" << std::endl;
	std::cout << "Applied rotations: Z(360), X(360), Y(360), X(360), Z(360)" << std::endl;
	std::cout << "Expected magnitude: " << magnitude(expected2) << std::endl;
	std::cout << "Magnitude before: " << magnitude(expected2) << std::endl;
	std::cout << "Original vector: (" << expected2.x << ", " << expected2.y << ", " << expected2.z << ")" << std::endl;
	std::cout << "Final rotated vector: (" << final.x << ", " << final.y << ", " << final.z << ")" << std::endl;
	if (almostEqualVec3(final, expected2, 1e-6)) {
		std::cout << "Test passed!" << std::endl;
	} else {
		std::cout << "Test failed!" << std::endl;
	}

	// This test applies sequential 45 degree rotations to one axis and checks the final result.
	Vec3 expected3{ 633, 946, 45 };
	Vec3 normalizedexpected3 = expected3 * (1.0 / magnitude(expected3)); // normalize to avoid overflow
	Vec3 rotatedexpected3 = rotateEulerZ(normalizedexpected3, 45);

	for (int i = 0; i < 7; i++) {
		rotatedexpected3 = rotateEulerZ(rotatedexpected3, 45);
	}

	final = rotatedexpected3 * magnitude(expected3); // scale back to original magnitude

	std::cout << "\nTest: Sequential 45 degree rotations on vector (633, 946, 45)" << std::endl;
	std::cout << "Applied rotations: Z(45) x 8" << std::endl;
	std::cout << "Expected magnitude: " << magnitude(expected3) << std::endl;
	std::cout << "Magnitude before: " << magnitude(expected3) << std::endl;
	std::cout << "Original vector: (" << expected3.x << ", " << expected3.y << ", " << expected3.z << ")" << std::endl;
	std::cout << "Final rotated vector: (" << final.x << ", " << final.y << ", " << final.z << ")" << std::endl;
	if (almostEqualVec3(final, expected3, 1e-6)) {
		std::cout << "Test passed!" << std::endl;
	} else {
		std::cout << "Test failed!" << std::endl;
	}
	
	// This test conduct repeated transformations to check for numerical stability and precision over multiple operations.
	Vec3 expected4{ 12345, 67890, 13579 };
	Vec3 normalizedexpected4 = expected4 * (1.0 / magnitude(expected4)); // normalize to avoid overflow
	Vec3 rotatedexpected4 = rotateEulerX(normalizedexpected4, 1);
	for(int i = 0; i < 360; i++) {
		rotatedexpected4 = rotateEulerX(rotatedexpected4, 1);
	}
	for (int i = 0; i < 360; i++) {
		rotatedexpected4 = rotateEulerY(rotatedexpected4, 1);
	}
	for (int i = 0; i < 360; i++) {
		rotatedexpected4 = rotateEulerZ(rotatedexpected4, 1);
	}
	final = rotatedexpected4 * magnitude(expected4); // scale back to original magnitude

	std::cout << "\nTest: Repeated 1 degree rotations on vector (12345, 67890, 13579)" << std::endl;
	std::cout << "Applied rotations: X(1) x 360, Y(1) x 360, Z(1) x 360" << std::endl;
	std::cout << "Expected magnitude: " << magnitude(expected4) << std::endl;
	std::cout << "Magnitude before: " << magnitude(expected4) << std::endl;
	std::cout << "Original vector: (" << expected4.x << ", " << expected4.y << ", " << expected4.z << ")" << std::endl;
	std::cout << "Final rotated vector: (" << final.x << ", " << final.y << ", " << final.z << ")" << std::endl;
	if (almostEqualVec3(final, expected4, 1e-6)) {
		std::cout << "Test passed! Not Expected. Should Numerically Drift." << std::endl;
	} else {
		std::cout << "Test failed! As Expected. Numerical Drifting." << std::endl;
	}

	// This test applies repeated quaternion-based rotations to check for consistency with Euler rotations and to verify that the quaternion functions are working correctly.
	Quat qx = quatFromAxisAngle({ 1, 0, 0 }, 1);
	Vec3 expected5{ 12345, 67890, 13579 };
	Vec3 normalizedexpected5 = expected5 * (1.0 / magnitude(expected5)); // normalize to avoid overflow

	Vec3 rotatedexpected5 = quatRotate(qx, normalizedexpected5);

	for (int i = 0; i < 360; i++) {
		rotatedexpected5 = rotatedexpected5 * (1.0 / magnitude(rotatedexpected5)); // re-normalize to prevent drift
		rotatedexpected5 = quatRotate(qx, rotatedexpected5);
	}

	Quat qy = quatFromAxisAngle({ 0, 1, 0 }, 1);

	for (int i = 0; i < 360; i++) {
		rotatedexpected5 = rotatedexpected5 * (1.0 / magnitude(rotatedexpected5)); // re-normalize to prevent drift
		rotatedexpected5 = quatRotate(qy, rotatedexpected5);
	}

	Quat qz = quatFromAxisAngle({ 0, 0, 1 }, 1);

	for (int i = 0; i < 360; i++) {
		rotatedexpected5 = rotatedexpected5 * (1.0 / magnitude(rotatedexpected5)); // re-normalize to prevent drift
		rotatedexpected5 = quatRotate(qz, rotatedexpected5);
	}

	final = rotatedexpected5 * magnitude(expected5); // scale back to original magnitude

	std::cout << "\nTest: Repeated quaternion rotations on vector (12345, 67890, 13579)" << std::endl;
	std::cout << "Applied rotations: Quaternion X(1) x 360, Quaternion Y(1) x 360, Quaternion Z(1) x 360" << std::endl;
	std::cout << "Expected magnitude: " << magnitude(expected5) << std::endl;
	std::cout << "Magnitude before: " << magnitude(expected5) << std::endl;
	std::cout << "Original vector: (" << expected5.x << ", " << expected5.y << ", " << expected5.z << ")" << std::endl;
	std::cout << "Final rotated vector: (" << final.x << ", " << final.y << ", " << final.z << ")" << std::endl;
	if (almostEqualVec3(final, expected5, 1e-6)) {
		std::cout << "Test passed! Not Expected. Should Numerically Drift." << std::endl;
	} else {
		std::cout << "Test failed! As Expected. Numerical Drifting." << std::endl;
	}
	return 0;
}