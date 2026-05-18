// ------------------------------------------------------------
// This file is part of the LA-TEST-ENV project
// Purpose: Conduct E2E manual tests focusing on numerical stability, precision, and transformation correctness. 
// Seconary purpose: To gauge usability and maintainability of the library when used in a manual testing context.
// ------------------------------------------------------------

// ------------------------------------------------------------
// To compile and run this test, do not compile "test.cpp" as it contains automated tests using Google Test framework. 
// Instead, compile this file separately and run the resulting executable to perform manual validation of the transformation functions.
// -------------------------------------------------------------

#include <iostream>

#include "pch.h"
#include "VectorTransformation3D.h"


// ------------------------------------------------------------

bool almostEqualShape(const Vec3* shape1, const Vec3* shape2, int vertexCount, double eps)
{
	for (int i = 0; i < vertexCount; i++) {
		if (!almostEqual(shape1[i].x, shape2[i].x, eps) ||
			!almostEqual(shape1[i].y, shape2[i].y, eps) ||
			!almostEqual(shape1[i].z, shape2[i].z, eps)) {
			std::cout << "Vertex " << i << " differs: "
				<< "Expected (" << shape2[i].x << ", " << shape2[i].y << ", " << shape2[i].z << ") "
				<< "Got (" << shape1[i].x << ", " << shape1[i].y << ", " << shape1[i].z << ")"
				<< std::endl;
			return false;
		}
	}
	return true;
}

Vec3* copyShape(const Vec3* shape, int vertexCount, int componentsPerVertex)
{
	Vec3* newShape = new Vec3[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		newShape[i] = shape[i];
	}
	return newShape;
}

int main()
{
	// All shapes are defined as flat arrays of vertex coordinates (x, y, z) for easy processing in graphics pipelines.
	// The shapes will be oriented in a standard way (e.g., centered at the origin, with consistent winding order) to 
	// facilitate testing of transformations and rendering.
	
	// ------------------------------------------------------------
	// Test Shapes
	// ------------------------------------------------------------

	// ------------------------------------------------------------
	// Cube Shape
	// ------------------------------------------------------------

	// Original Cube vertices (8 vertices, 3 components each)
	const Vec3 cube[] = {
		// Vertices are defined in a standard order (e.g., front-bottom-left, front-bottom-right, front-top-right, front-top-left, back-bottom-left, back-bottom-right, back-top-right, back-top-left)
		// Bottom Face
		{ -1, -1, -1 }, // 0
		{  1, -1, -1 }, // 1
		{  1,  1, -1 }, // 2
		{ -1,  1, -1 }, // 3

		// Top Face
		{ -1, -1,  1 }, // 4
		{  1, -1,  1 }, // 5
		{  1,  1,  1 }, // 6
		{ -1,  1,  1 }  // 7
	};

	// Hard coded transformed Cube vertices (after applying a series of transformations, for testing purposes)
	// Cube vertex from about (cube) is transformed by rotating 45 degrees around X axis and then 45 degrees around Y axis.
	const Vec3 transformedCube[] = {
	{-1.7071067811865475, -1.1102230246251565e-16, -0.2928932188134524}, // Vertex 0
	{-0.2928932188134524, -1.1102230246251565e-16, -1.7071067811865475}, // Vertex 1
	{ 0.7071067811865475,  1.4142135623730951,      -0.7071067811865475}, // Vertex 2
	{-0.7071067811865475,  1.4142135623730951,       0.7071067811865475}, // Vertex 3
	{-0.7071067811865475, -1.4142135623730951,       0.7071067811865475}, // Vertex 4
	{ 0.7071067811865475, -1.4142135623730951,      -0.7071067811865475}, // Vertex 5
	{ 1.7071067811865475,  1.1102230246251565e-16,   0.2928932188134524}, // Vertex 6
	{ 0.2928932188134524,  1.1102230246251565e-16,   1.7071067811865475}  // Vertex 7

	};

	// ------------------------------------------------------------
	// Pyramid Shape
	// ------------------------------------------------------------

	// Original Tetrahedron vertices (4 vertices, 3 components each)
	const Vec3 pyramid[] = {
		{ 0, 0, 1 }, // top
		{ -0.5, -0.86602540378, 0 }, // base 1
		{ 0.5, -0.86602540378, 0 }, // base 2
		{ 0.5, 0.86602540378, 0 }, // base 3
		{ -0.5, 0.86602540378, 0 } // base 4
	};

	// Transformed Tetrahedron vertices (after applying a series of transformations, for testing purposes)
	// Tetrahedron is transformed by rotating 30 degrees around X axis and then 60 degrees around Y axis.
	const Vec3 transformedPyramid[] = {
		{  0.75000000000, -0.50000000000,  0.43301270189 }, // top
		{ -0.62500000000, -0.75000000000,  0.21650635095 }, // base 1
		{ -0.12500000000, -0.75000000000, -0.64951905284 }, // base 2
		{  0.62500000000,  0.75000000000, -0.21650635095 }, // base 3
		{  0.12500000000,  0.75000000000,  0.64951905284 }  // base 4
	};

	// ------------------------------------------------------------
	// Hexagonal Pyramid Shape
	// ------------------------------------------------------------

	// Original Hexagonal Pyramid vertices (7 vertices, 3 components each)
	const Vec3 hexagonalPyramid[] = {
		{ 0, 0, 1 }, // top
		{ 0.5, -0.86602540378, 0.5 }, // base 1
		{ -0.5, -0.86602540378, 0.5 }, // base 2
		{ -1.0, 0.0, 0.5 }, // base 3
		{ -0.5, 0.86602540378, 0.5 }, // base 4
		{ 0.5, 0.86602540378, 0.5 }, // base 5
		{ 1.0, 0.0, 0.5 } // base 6
	};

	// Transformed Hexagonal Pyramid vertices (after applying a series of transformations, for testing purposes)
	// Hexagonal Pyramid is transformed by rotating 60 degrees around X axis and then 120 degrees around Y axis.
	const Vec3 transformedHexagonalPyramid[] = {
		{ 0.433012701892219, -0.866025403784439, -0.250000000000000 }, // top
		{ -0.683012701888890, -0.866025403782219, -0.183012701894141 }, // base 1
		{ -0.183012701888890, -0.866025403782219, 0.683012701890297 }, // base 2
		{ 0.716506350946109, -0.433012701892219, 0.741025403784439 }, // base 3
		{ 1.116025403781110, -0.000000000002219, -0.066987298105858 }, // base 4
		{ 0.616025403781110, -0.000000000002219, -0.933012701890297 }, // base 5
		{ -0.283493649053890, -0.433012701892219, -0.991025403784439 }, // base 6
	};

	// ------------------------------------------------------------
	// Subdivided Cube Shape (for testing precision and stability with more vertices)
	// ------------------------------------------------------------

	// Original Subdivided Cube vertices (64 vertices, 3 components each)
	Vec3 subdividedCubeVertices[] = {
	// --- Layer 1: Front Face Outer Shell (Z = 1.0) ---
	{-1.0, -1.0,  1.0},
	{-0.33333333333333333, -1.0,  1.0},
	{0.33333333333333333, -1.0,  1.0},
	{1.0, -1.0,  1.0},
	{-1.0, -0.33333333333333333,  1.0},
	{-0.33333333333333333, -0.33333333333333333,  1.0},
	{0.33333333333333333, -0.33333333333333333,  1.0},
	{1.0, -0.33333333333333333,  1.0},
	{-1.0,  0.33333333333333333,  1.0},
	{-0.33333333333333333,  0.33333333333333333,  1.0},
	{0.33333333333333333,  0.33333333333333333,  1.0},
	{1.0,  0.33333333333333333,  1.0},
	{-1.0,  1.0,  1.0},
	{-0.33333333333333333,  1.0,  1.0},
	{0.33333333333333333,  1.0,  1.0},
	{1.0,  1.0,  1.0},

	// --- Layer 2: Forward-Middle Ring (Z = 0.3333) ---
	{-1.0, -1.0,  0.33333333333333333},
	{-0.33333333333333333, -1.0,  0.33333333333333333},
	{0.33333333333333333, -1.0,  0.33333333333333333},
	{1.0, -1.0,  0.33333333333333333},
	{-1.0, -0.33333333333333333,  0.33333333333333333},
	{1.0, -0.33333333333333333,  0.33333333333333333},
	{-1.0,  0.33333333333333333,  0.33333333333333333},
	{1.0,  0.33333333333333333,  0.33333333333333333},
	{-1.0,  1.0,  0.33333333333333333},
	{-0.33333333333333333,  1.0,  0.33333333333333333},
	{0.33333333333333333,  1.0,  0.33333333333333333},
	{1.0,  1.0,  0.33333333333333333},

	// --- Layer 3: Backward-Middle Ring (Z = -0.3333) ---
	{-1.0, -1.0, -0.33333333333333333},
	{-0.33333333333333333, -1.0, -0.33333333333333333},
	{0.33333333333333333, -1.0, -0.33333333333333333},
	{1.0, -1.0, -0.33333333333333333},
	{-1.0, -0.33333333333333333, -0.33333333333333333},
	{1.0, -0.33333333333333333, -0.33333333333333333},
	{-1.0,  0.33333333333333333, -0.33333333333333333},
	{1.0,  0.33333333333333333, -0.33333333333333333},
	{-1.0,  1.0, -0.33333333333333333},
	{-0.33333333333333333,  1.0, -0.33333333333333333},
	{0.33333333333333333,  1.0, -0.33333333333333333},
	{1.0,  1.0, -0.33333333333333333},

	// --- Layer 4: Back Face Outer Shell (Z = -1.0) ---
	{-1.0, -1.0, -1.0},
	{-0.33333333333333333, -1.0, -1.0},
	{0.33333333333333333, -1.0, -1.0},
	{1.0, -1.0, -1.0},
	{-1.0, -0.33333333333333333, -1.0},
	{-0.33333333333333333, -0.33333333333333333, -1.0},
	{0.33333333333333333, -0.33333333333333333, -1.0},
	{1.0, -0.33333333333333333, -1.0},
	{-1.0,  0.33333333333333333, -1.0},
	{-0.33333333333333333,  0.33333333333333333, -1.0},
	{1.0,  0.33333333333333333, -1.0},
	{-1.0,  1.0, -1.0},
	{-0.33333333333333333,  1.0, -1.0},
	{0.33333333333333333,  1.0, -1.0},
	{1.0,  1.0, -1.0}

	};

	// Transformed Subdivided Cube vertices (after applying a series of transformations, for testing purposes)
	// Subdivided Cube is transformed by rotating 30 degrees around X axis and then 45 degrees around Y axis.
	const Vec3 transformedSubdividedCube[] = {
		// --- Layer 1: Front Face Outer Shell (Z = 1.0) ---
		{-0.4482877360840267, -1.3660254037844386, 0.9659258262890683},
		{0.0231167847070050, -1.3660254037844386, 0.4945213054980366},
		{0.4945213054980366, -1.3660254037844386, 0.0231167847070051},
		{0.9659258262890684, -1.3660254037844386, -0.4482877360840266},
		{-0.2125854756885110, -0.7886751345948129, 1.2016280866845841},
		{0.2588190451025207, -0.7886751345948129, 0.7302235658935525},
		{0.7302235658935524, -0.7886751345948129, 0.2588190451025209},
		{1.2016280866845841, -0.7886751345948129, -0.2125854756885108},
		{0.0231167847070048, -0.2113248654051871, 1.4373303470801000},
		{0.4945213054980365, -0.2113248654051871, 0.9659258262890683},
		{0.9659258262890682, -0.2113248654051871, 0.4945213054980367},
		{1.4373303470801000, -0.2113248654051871, 0.0231167847070051},
		{0.2588190451025206, 0.3660254037844388, 1.6730326074756157},
		{0.7302235658935523, 0.3660254037844388, 1.2016280866845841},
		{1.2016280866845839, 0.3660254037844388, 0.7302235658935525},
		{1.6730326074756157, 0.3660254037844388, 0.2588190451025209},

		// --- Layer 2: Forward-Middle Ring (Z = 0.3333) ---
		{-0.8565360265478897, -1.0326920704511053, 0.5576775358252053},
		{-0.3851315057568581, -1.0326920704511053, 0.0862730150341736},
		{0.0862730150341736, -1.0326920704511053, -0.3851315057568580},
		{0.5576775358252054, -1.0326920704511053, -0.8565360265478896},
		{-0.6208337661523741, -0.4553418012614795, 0.7933797962207210},
		{0.7933797962207211, -0.4553418012614795, -0.6208337661523740},
		{-0.3851315057568582, 0.1220084679281462, 1.0290820566162369},
		{1.0290820566162371, 0.1220084679281462, -0.3851315057568580},
		{-0.1494292453613424, 0.6993587371177721, 1.2647843170117528},
		{0.3219752754296893, 0.6993587371177721, 0.7933797962207210},
		{0.7933797962207210, 0.6993587371177721, 0.3219752754296894},
		{1.2647843170117528, 0.6993587371177721, -0.1494292453613422},

		// --- Layer 3: Backward-Middle Ring (Z = -0.3333) ---
		{-1.2647843170117528, -0.6993587371177721, 0.1494292453613422},
		{-0.7933797962207210, -0.6993587371177721, -0.3219752754296894},
		{-0.3219752754296893, -0.6993587371177721, -0.7933797962207210},
		{0.1494292453613424, -0.6993587371177721, -1.2647843170117528},
		{-1.0290820566162371, -0.1220084679281462, 0.3851315057568580},
		{0.3851315057568582, -0.1220084679281462, -1.0290820566162369},
		{-0.7933797962207211, 0.4553418012614795, 0.6208337661523740},
		{0.6208337661523741, 0.4553418012614795, -0.7933797962207210},
		{-0.5576775358252054, 1.0326920704511053, 0.8565360265478896},
		{-0.0862730150341736, 1.0326920704511053, 0.3851315057568580},
		{0.3851315057568581, 1.0326920704511053, -0.0862730150341736},
		{0.8565360265478897, 1.0326920704511053, -0.5576775358252053},

		// --- Layer 4: Back Face Outer Shell (Z = -1.0) ---
		{-1.6730326074756157, -0.3660254037844388, -0.2588190451025209},
		{-1.2016280866845839, -0.3660254037844388, -0.7302235658935525},
		{-0.7302235658935523, -0.3660254037844388, -1.2016280866845841},
		{-0.2588190451025206, -0.3660254037844388, -1.6730326074756157},
		{-1.4373303470801000, 0.2113248654051871, -0.0231167847070051},
		{-0.9659258262890682, 0.2113248654051871, -0.4945213054980367},
		{-0.4945213054980365, 0.2113248654051871, -0.9659258262890683},
		{-0.0231167847070048, 0.2113248654051871, -1.4373303470801000},
		{-1.2016280866845841, 0.7886751345948129, 0.2125854756885108},
		{-0.7302235658935524, 0.7886751345948129, -0.2588190451025209},
		{0.2125854756885110, 0.7886751345948129, -1.2016280866845841},
		{-0.9659258262890684, 1.3660254037844386, 0.4482877360840266},
		{-0.4945213054980366, 1.3660254037844386, -0.0231167847070051},
		{-0.0231167847070050, 1.3660254037844386, -0.4945213054980366},
		{0.4482877360840267, 1.3660254037844386, -0.9659258262890683}
	};

	// ------------------------------------------------------------
	// Test Scenario 1
	// Description: Manually apply transformations to the cube and compare against expected results.
	// Step 1: Rotate cube 45 degrees around X axis
	// Step 2: Rotate cube 45 degrees around Y axis
	// Step 3: Validate transformed vertices against expected values (transformedCube)
	// ------------------------------------------------------------
	std::cout << "Test Scenario 1: Manual Cube Rotation Validation" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Applying rotations to cube vertices..." << std::endl;
	// Uncomment the following lines to print original vertices for debugging purposes
	//for (int i = 0; i < 8; i++) {
	//	std::cout << "Original Vertex " << i << ": " << cube[i].x << ", " << cube[i].y << ", " << cube[i].z << std::endl;
	//}
	//std::cout << "Expected transformed vertices:" << std::endl;
	//for (int i = 0; i < 8; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << transformedCube[i].x << ", " << transformedCube[i].y << ", " << transformedCube[i].z << std::endl;
	//}
	Vec3* testCube = copyShape(cube, 8, 3);
	int testCubeVertexCount = 8;
	for (int i = 0; i < testCubeVertexCount; i++) {
		testCube[i] = rotateEulerX(testCube[i], 45.0);
	}
	for (int i = 0; i < testCubeVertexCount; i++) {
		testCube[i] = rotateEulerY(testCube[i], 45.0);
	}
	// Uncomment the following lines to print actual transformed vertices for debugging purposes
	//std::cout << "Actual transformed vertices:" << std::endl;
	//for (int i = 0; i < testCubeVertexCount; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << testCube[i].x << ", " << testCube[i].y << ", " << testCube[i].z << std::endl;
	//}
	if (almostEqualShape(testCube, transformedCube, testCubeVertexCount, EPS)) {
		std::cout << "Test Scenario 1 Passed: Transformed vertices match expected values within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 1 Failed: Transformed vertices do not match expected values." << std::endl;
	}
	// ------------------------------------------------------------
	// Test Scenario 2
	// Description: Manually apply transformations to the pyramid and compare against expected results.
	// Step 1: Rotate pyramid 30 degrees around X axis
	// Step 2: Rotate pyramid 60 degrees around Y axis
	// Step 3: Validate transformed vertices against expected values (transformedPyramid)
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 2: Manual Pyramid Rotation Validation" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Applying rotations to pyramid vertices..." << std::endl;
	// Uncomment the following lines to print original vertices for debugging purposes
	//for (int i = 0; i < 5; i++) {
	//	std::cout << "Original Vertex " << i << ": " << pyramid[i].x << ", " << pyramid[i].y << ", " << pyramid[i].z << std::endl;
	//}
	//std::cout << "Expected transformed vertices:" << std::endl;
	//for (int i = 0; i < 5; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << transformedPyramid[i].x << ", " << transformedPyramid[i].y << ", " << transformedPyramid[i].z << std::endl;
	//}
	Vec3* testPyramid = copyShape(pyramid, 5, 3);
	int testPyramidVertexCount = 5;
	for (int i = 0; i < testPyramidVertexCount; i++) {
		testPyramid[i] = rotateEulerX(testPyramid[i], 30.0);
	}
	for (int i = 0; i < testPyramidVertexCount; i++) {
		testPyramid[i] = rotateEulerY(testPyramid[i], 60.0);
	}
	// Uncomment the following lines to print actual transformed vertices for debugging purposes
	//std::cout << "Actual transformed vertices:" << std::endl;
	//for (int i = 0; i < testPyramidVertexCount; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << testPyramid[i].x << ", " << testPyramid[i].y << ", " << testPyramid[i].z << std::endl;
	//}
	if (almostEqualShape(testPyramid, transformedPyramid, testPyramidVertexCount, EPS)) {
		std::cout << "Test Scenario 2 Passed: Transformed vertices match expected values within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 2 Failed: Transformed vertices do not match expected values." << std::endl;
	}

	// ------------------------------------------------------------
	// Test Scenario 3
	// Description: Manually apply transformations to the hexagonal pyramid and compare against expected results.
	// Step 1: Rotate hexagonal pyramid 60 degrees around X axis
	// Step 2: Rotate hexagonal pyramid 120 degrees around Y axis
	// Step 3: Validate transformed vertices against expected values (transformedHexagonalPyramid)
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 3: Manual Hexagonal Pyramid Rotation Validation" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Applying rotations to hexagonal pyramid vertices..." << std::endl;
	// Uncomment the following lines to print original vertices for debugging purposes
	//for (int i = 0; i < 7; i++) {
	//	std::cout << "Original Vertex " << i << ": " << hexagonalPyramid[i].x << ", " << hexagonalPyramid[i].y << ", " << hexagonalPyramid[i].z << std::endl;
	//}
	//std::cout << "Expected transformed vertices:" << std::endl;
	//for (int i = 0; i < 7; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << transformedHexagonalPyramid[i].x << ", " << transformedHexagonalPyramid[i].y << ", " << transformedHexagonalPyramid[i].z << std::endl;
	//}
	Vec3* testHexagonalPyramid = copyShape(hexagonalPyramid, 7, 3);
	int testHexagonalPyramidVertexCount = 7;
	for (int i = 0; i < testHexagonalPyramidVertexCount; i++) {
		testHexagonalPyramid[i] = rotateEulerX(testHexagonalPyramid[i], 60.0);
	}
	for (int i = 0; i < testHexagonalPyramidVertexCount; i++) {
		testHexagonalPyramid[i] = rotateEulerY(testHexagonalPyramid[i], 120.0);
	}
	// Uncomment the following lines to print actual transformed vertices for debugging purposes
	//std::cout << "Actual transformed vertices:" << std::endl;
	//for (int i = 0; i < testHexagonalPyramidVertexCount; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << testHexagonalPyramid[i].x << ", " << testHexagonalPyramid[i].y << ", " << testHexagonalPyramid[i].z << std::endl;
	//}
	if (almostEqualShape(testHexagonalPyramid, transformedHexagonalPyramid, testHexagonalPyramidVertexCount, EPS)) {
		std::cout << "Test Scenario 3 Passed: Transformed vertices match expected values within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 3 Failed: Transformed vertices do not match expected values." << std::endl;
	}

	// ------------------------------------------------------------
	// Test Scenario 4
	// Description: Manually apply transformations to the subdivided cube and compare against expected results. Intended to test precision and stability with a larger number of vertices.
	// Step 1: Rotate subdivided cube 30 degrees around X axis
	// Step 2: Rotate subdivided cube 45 degrees around Y axis
	// Step 3: Validate transformed vertices against expected values (transformedSubdividedCube)
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 4: Manual Subdivided Cube Rotation Validation" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Applying rotations to subdivided cube vertices..." << std::endl;
	// Uncomment the following lines to print original vertices for debugging purposes
	//for (int i = 0; i < 55; i++) {
	//	std::cout << "Original Vertex " << i << ": " << subdividedCubeVertices[i].x << ", " << subdividedCubeVertices[i].y << ", " << subdividedCubeVertices[i].z << std::endl;
	//}
	//std::cout << "Expected transformed vertices:" << std::endl;
	//for (int i = 0; i < 55; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << transformedSubdividedCube[i].x << ", " << transformedSubdividedCube[i].y << ", " << transformedSubdividedCube[i].z << std::endl;
	//}
	Vec3* testSubdividedCube = copyShape(subdividedCubeVertices, 55, 3);
	int testSubdividedCubeVertexCount = 55;
	for (int i = 0; i < testSubdividedCubeVertexCount; i++) {
		testSubdividedCube[i] = rotateEulerX(testSubdividedCube[i], 30.0);
	}
	for (int i = 0; i < testSubdividedCubeVertexCount; i++) {
		testSubdividedCube[i] = rotateEulerY(testSubdividedCube[i], 45.0);
	}
	// Uncomment the following lines to print actual transformed vertices for debugging purposes
	//std::cout << "Actual transformed vertices:" << std::endl;
	//for (int i = 0; i < testSubdividedCubeVertexCount; i++)
	//{
	//	std::cout << "Transformed Vertex " << i << ": " << testSubdividedCube[i].x << ", " << testSubdividedCube[i].y << ", " << testSubdividedCube[i].z << std::endl;
	//}
	if (almostEqualShape(testSubdividedCube, transformedSubdividedCube, testSubdividedCubeVertexCount, EPS)) {
		std::cout << "Test Scenario 4 Passed: Transformed vertices match expected values within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 4 Failed: Transformed vertices do not match expected values." << std::endl;
	}


	// ------------------------------------------------------------
	// Test Scenario 5
	// Description: Manually apply transformation using quaternions to the cube and compare against expected results.
	// Step 1: Rotate cube 45 degrees around X axis using quaternion
	// Step 2: Rotate cube 45 degrees around Y axis using quaternion
	// Step 3: Validate transformed vertices against expected values (transformedCube)
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 5: Manual Cube Rotation Using Quaternions Validation" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Applying quaternion rotations to cube vertices..." << std::endl;
	// Uncomment the following lines to print original vertices for debugging purposes
	//for (int i = 0; i < 8; i++) {
	//	std::cout << "Original Vertex " << i << ": " << cube[i].x << ", " << cube[i].y << ", " << cube[i].z << std::endl;
	//}
	//std::cout << "Expected transformed vertices:" << std::endl;
	//for (int i = 0; i < 8; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << transformedCube[i].x << ", " << transformedCube[i].y << ", " << transformedCube[i].z << std::endl;
	//}
	Vec3* testCube2 = copyShape(cube, 8, 3);

	Quat quatX = quatFromAxisAngle({ 1, 0, 0 }, 45.0);
	Quat quatY = quatFromAxisAngle({ 0, 1, 0 }, 45.0);
	Quat combinedQuat = quatMultiply(quatY, quatX); // Note: Order matters for quaternion multiplication

	for (int i = 0; i < testCubeVertexCount; i++) {
		testCube2[i] = quatRotate(combinedQuat, testCube2[i]);
	}
	// Uncomment the following lines to print actual transformed vertices for debugging purposes
	//std::cout << "Actual transformed vertices:" << std::endl;
	//for (int i = 0; i < testCubeVertexCount; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << testCube2[i].x << ", " << testCube2[i].y << ", " << testCube2[i].z << std::endl;
	//}
	if (almostEqualShape(testCube2, transformedCube, testCubeVertexCount, EPS)) {
		std::cout << "Test Scenario 5 Passed: Transformed vertices match expected values within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 5 Failed: Transformed vertices do not match expected values." << std::endl;
	}

	// ------------------------------------------------------------
	// Test Scenario 6
	// Description: Manually apply transformation using quaternions to the subdivided cube and compare against expected results.
	// Step 1: Rotate subdivided cube 30 degrees around X axis using quaternion
	// Step 2: Rotate subdivided cube 45 degrees around Y axis using quaternion
	// Step 3: Validate transformed vertices against expected values (transformedSubdividedCube)
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 6: Manual Subdivided Cube Rotation Using Quaternions Validation" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Applying quaternion rotations to subdivided cube vertices..." << std::endl;
	// Uncomment the following lines to print original vertices for debugging purposes
	//for (int i = 0; i < 55; i++) {
	//	std::cout << "Original Vertex " << i << ": " << subdividedCubeVertices[i].x << ", " << subdividedCubeVertices[i].y << ", " << subdividedCubeVertices[i].z << std::endl;
	//}
	//std::cout << "Expected transformed vertices:" << std::endl;
	//for (int i = 0; i < 55; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << transformedSubdividedCube[i].x << ", " << transformedSubdividedCube[i].y << ", " << transformedSubdividedCube[i].z << std::endl;
	//}

	Vec3* testSubdividedCube2 = copyShape(subdividedCubeVertices, 55, 3);
	Quat quatX2 = quatFromAxisAngle({ 1, 0, 0 }, 30.0);
	Quat quatY2 = quatFromAxisAngle({ 0, 1, 0 }, 45.0);
	Quat combinedQuat2 = quatMultiply(quatY2, quatX2); // Note: Order matters for quaternion multiplication
	for (int i = 0; i < testSubdividedCubeVertexCount; i++) {
		testSubdividedCube2[i] = quatRotate(combinedQuat2, testSubdividedCube2[i]);
	}
	// Uncomment the following lines to print actual transformed vertices for debugging purposes
	//std::cout << "Actual transformed vertices:" << std::endl;
	//for (int i = 0; i < testSubdividedCubeVertexCount; i++) {
	//	std::cout << "Transformed Vertex " << i << ": " << testSubdividedCube2[i].x << ", " << testSubdividedCube2[i].y << ", " << testSubdividedCube2[i].z << std::endl;
	//}
	if (almostEqualShape(testSubdividedCube2, transformedSubdividedCube, testSubdividedCubeVertexCount, EPS)) {
		std::cout << "Test Scenario 6 Passed: Transformed vertices match expected values within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 6 Failed: Transformed vertices do not match expected values." << std::endl;
	}

	// ------------------------------------------------------------
	// Test Scenario 7
	// Description: Use dot product to validate the orthogonality of the original cube's edges after transformation. This is an additional check to ensure that the transformations are not introducing skewing.
	// Step 1: Copy testCube2 (which has the cube vertices transformed using quaternions) to a new array for testing.
	// Step 2: Randomly select main vertex and adjecent vertices to form edges.
	// Step 3: Calculate edge vectors and use dot product to check for orthogonality.
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 7: Orthogonality Check Using Dot Product" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Validating orthogonality of cube edges after quaternion transformation..." << std::endl;
	Vec3* orthogonalityTestVertices = copyShape(testCube, 8, 3);
	Vec3 mainVertex = orthogonalityTestVertices[0]; // Using the first vertex as the main vertex
	Vec3 adjacentVertex1 = orthogonalityTestVertices[1]; // Adjacent vertex 1
	Vec3 adjacentVertex2 = orthogonalityTestVertices[3]; // Adjacent vertex 2
	Vec3 adjacentVertex3 = orthogonalityTestVertices[4]; // Adjacent vertex 3 (choosing a vertex that shares an edge with the main vertex but is not collinear with the first two adjacent vertices)

	Vec3 edge1 = adjacentVertex1 - mainVertex; // Edge from main vertex to adjacent vertex 1
	Vec3 edge2 = adjacentVertex2 - mainVertex; // Edge from main vertex to adjacent vertex 2
	Vec3 edge3 = adjacentVertex3 - mainVertex; // Edge from main vertex to adjacent vertex 3

	double dot12 = dot3(edge1, edge2); // Dot product of edge1 and edge2
	double dot13 = dot3(edge1, edge3); // Dot product of edge1 and edge3
	double dot23 = dot3(edge2, edge3); // Dot product of edge2 and edge3

	if (dot12 < EPS && dot13 < EPS && dot23 < EPS) {
		std::cout << "Test Scenario 7 Passed: Edges are orthogonal within tolerance." << std::endl;
	}
	else {
		std::cout << "Test Scenario 7 Failed: Edges are not orthogonal." << std::endl;
		std::cout << "Dot Product of Edge1 and Edge2: " << dot12 << std::endl;
		std::cout << "Dot Product of Edge1 and Edge3: " << dot13 << std::endl;
		std::cout << "Dot Product of Edge2 and Edge3: " << dot23 << std::endl;
	}

	// ------------------------------------------------------------
	// Test Scenario 8
	// Description: Use cross product to validate the right-handedness of the original cube's edges after transformation. This is an additional check to ensure that the transformations are not introducing mirroring.
	// Step 1: Copy testCube2 (which has the cube vertices transformed using quaternions) to a new array for testing.
	// Step 2: Randomly select main vertex and adjecent vertices to form edges.
	// Step 3: Calculate edge vectors and use cross product to check for right-handedness.
	// ------------------------------------------------------------
	std::cout << "\nTest Scenario 8: Right-Handedness Check Using Cross Product" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "Validating right-handedness of cube edges after quaternion transformation..." << std::endl;
	Vec3* rightHandednessTestVertices = copyShape(testCube, 8, 3);
	mainVertex = rightHandednessTestVertices[0]; // Using the first vertex as the main vertex
	adjacentVertex1 = rightHandednessTestVertices[1]; // Adjacent vertex 1
	adjacentVertex2 = rightHandednessTestVertices[3]; // Adjacent vertex 2
	adjacentVertex3 = rightHandednessTestVertices[4]; // Adjacent vertex 3 (choosing a vertex that shares an edge with the main vertex but is not collinear with the first two adjacent vertices)

	Vec3 edgeA = adjacentVertex1 - mainVertex; // Edge from main vertex to adjacent vertex 1
	Vec3 edgeB = adjacentVertex2 - mainVertex; // Edge from main vertex to adjacent vertex 2
	Vec3 edgeC = adjacentVertex3 - mainVertex; // Edge from main vertex to adjacent vertex 3

	Vec3 crossAB = cross3(edgeA, edgeB); // Cross product of edgeA and edgeB
	double dotCrossC = dot3(crossAB, edgeC); // Dot product of crossAB and edgeC
	if (dotCrossC > EPS) {
		std::cout << "Test Scenario 8 Passed: Edges maintain right-handedness." << std::endl;
	}
	else {
		std::cout << "Test Scenario 8 Failed: Edges do not maintain right-handedness." << std::endl;
		std::cout << "Dot Product of Cross Product and EdgeC: " << dotCrossC << std::endl;
	}


	return 0;
}