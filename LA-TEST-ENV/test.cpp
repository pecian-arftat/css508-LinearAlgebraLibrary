#include "pch.h"

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <tuple>


#include "VectorTransformation3D.h"

// ----------------------------
// Unit Tests
// ----------------------------
// ----------------------------
// Dot Product Tests
// ----------------------------
TEST(DotProductTest, Basic) {
    Vec3 a{ 1,2,3 };
    EXPECT_DOUBLE_EQ(dot3(a, a), 14);
}

TEST(DotProductTest, Orthogonal) {
    Vec3 a{ 1,0,0 };
    Vec3 b{ 0,1,0 };
    EXPECT_DOUBLE_EQ(dot3(a, b), 0);
}

TEST(DotProductTest, Commutative) {
    Vec3 a{ 1,2,3 };
    Vec3 b{ 4,3,2 };
    EXPECT_DOUBLE_EQ(dot3(a, b), dot3(b, a));
}

// ----------------------------
// Cross Product Tests
// ----------------------------
TEST(CrossProductTest, Basis) {
    Vec3 i{ 1,0,0 }, j{ 0,1,0 };
    Vec3 k = cross3(i, j);
    EXPECT_TRUE(almostEqualVec3(k, { 0,0,1 }));
}

TEST(CrossProductTest, AntiCommutative) {
    Vec3 a{ 1,2,3 }, b{ 4,5,6 };
    Vec3 c1 = cross3(a, b);
    Vec3 c2 = cross3(b, a);
    EXPECT_TRUE(almostEqualVec3(c1, { -c2.x, -c2.y, -c2.z }));
}

TEST(CrossProductTest, Parallel) {
    Vec3 a{ 1,2,3 }, b{ 2,4,6 };
    Vec3 c = cross3(a, b);
    EXPECT_TRUE(almostEqualVec3(c, { 0,0,0 }));
}

// ----------------------------
// Quaternion Tests
// ----------------------------
TEST(QuaternionTest, Identity) {
    Quat q{ 1,0,0,0 };
    Vec3 v{ 1,2,3 };
    EXPECT_TRUE(almostEqualVec3(quatRotate(q, v), v));
}

TEST(QuaternionTest, Rotate90Z) {
    Quat q = quatFromAxisAngle({ 0,0,1 }, 90);
    Vec3 v{ 1,0,0 };
    Vec3 result = quatRotate(q, v);
    EXPECT_TRUE(almostEqualVec3(result, { 0,1,0 }));
}

TEST(QuaternionTest, Inverse) {
    Quat q = quatFromAxisAngle({ 0,0,1 }, 45);
    Quat qInv{ q.w, -q.x, -q.y, -q.z };

    Vec3 v{ 1,0,0 };
    Vec3 rotated = quatRotate(q, v);
    Vec3 back = quatRotate(qInv, rotated);

    EXPECT_TRUE(almostEqualVec3(back, v));
}

TEST(QuaternionTest, Normalization) {
    Quat q{ 2,0,0,0 };
    Quat qn = normalizeQuat(q);
    EXPECT_TRUE(almostEqual(qn.w, 1.0));
}

// ----------------------------
// Euler Tests
// ----------------------------
TEST(EulerTest, Rotate90X) {
    Vec3 v{ 0,1,0 };
    Vec3 result = rotateEulerX(v, 90);
    EXPECT_TRUE(almostEqualVec3(result, { 0,0,1 }));
}

TEST(EulerTest, Rotate90Y) {
    Vec3 v{ 0,0,1 };
    Vec3 result = rotateEulerY(v, 90);
    EXPECT_TRUE(almostEqualVec3(result, { 1,0,0 }));
}

TEST(EulerTest, Rotate90Z) {
    Vec3 v{ 1,0,0 };
    Vec3 result = rotateEulerZ(v, 90);
    EXPECT_TRUE(almostEqualVec3(result, { 0,1,0 }));
}

TEST(EulerTest, ZeroRotation) {
    Vec3 v{ 1,2,3 };
    EXPECT_TRUE(almostEqualVec3(rotateEulerZ(v, 0), v));
}

TEST(EulerTest, FullRotation) {
    Vec3 v{ 1,2,3 };
    EXPECT_TRUE(almostEqualVec3(rotateEulerZ(v, 360), v));
}

// ----------------------------
// Consistency Tests
// ----------------------------
TEST(ConsistencyTest, EulerVsQuaternion) {
    Vec3 v{ 1,0,0 };

    Vec3 eulerRot = rotateEulerZ(v, 90);
    Quat q = quatFromAxisAngle({ 0,0,1 }, 90);
    Vec3 quatRot = quatRotate(q, v);

    EXPECT_TRUE(almostEqualVec3(eulerRot, quatRot));
}

// ----------------------------
// Invariants
// ----------------------------
TEST(InvariantTest, LengthPreserved) {
    Vec3 v{ 3,4,0 };
    Quat q = quatFromAxisAngle({ 0,0,1 }, 123);

    Vec3 rotated = quatRotate(q, v);
    EXPECT_NEAR(magnitude(v), magnitude(rotated), EPS);
}

TEST(InvariantTest, OrthogonalityPreserved) {
    Vec3 a{ 1,0,0 }, b{ 0,1,0 };
    Quat q = quatFromAxisAngle({ 0,0,1 }, 45);

    Vec3 a2 = quatRotate(q, a);
    Vec3 b2 = quatRotate(q, b);

    double dot = a2.x * b2.x + a2.y * b2.y + a2.z * b2.z;
    EXPECT_NEAR(dot, 0.0, EPS);
}

// ----------------------------
// Edge Cases
// ----------------------------
TEST(EdgeCaseTest, SmallValues) {
    Vec3 v{ 1e-8, 0, 0 };
    Quat q = quatFromAxisAngle({ 0,0,1 }, 90);

    Vec3 result = quatRotate(q, v);
    EXPECT_GT(magnitude(result), 0);
}

TEST(EdgeCaseTest, LargeValues) {
    Vec3 v{ 1e8, 0, 0 };
    Quat q = quatFromAxisAngle({ 0,0,1 }, 90);

    Vec3 result = quatRotate(q, v);
    EXPECT_NEAR(magnitude(v), magnitude(result), 1e2);
}

// ----------------------------
// Integration Tests
// ----------------------------

Vec4 applyEulerToVec4(const Vec4& v, double angleDeg) {
    Vec3 rotated = rotateEulerZ({ v.x, v.y, v.z }, angleDeg);
    return { rotated.x, rotated.y, rotated.z, v.w }; // preserve w
}

Vec4 applyQuatToVec4(const Vec4& v, const Quat& q) {
    Vec3 rotated = quatRotate(q, { v.x, v.y, v.z });
    return { rotated.x, rotated.y, rotated.z, v.w }; // preserve w
}

double magnitude4(const Vec4& v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

bool almostEqualVec4(const Vec4& a, const Vec4& b, double eps = EPS) {
    return almostEqual(a.x, b.x, eps) &&
        almostEqual(a.y, b.y, eps) &&
        almostEqual(a.z, b.z, eps) &&
        almostEqual(a.w, b.w, eps);
}


// Full pipeline integration test
TEST(IntegrationTest, EulerQuaternion4DConsistencyPipeline) {
    Vec4 v{ 1.0, 2.0, 3.0, 1.0 };  // homogeneous point
    double angle = 90.0;

    // Step 1: Euler rotation
    Vec4 eulerResult = applyEulerToVec4(v, angle);

    // Step 2: Quaternion rotation
    Quat q = quatFromAxisAngle({ 0,0,1 }, angle);
    Vec4 quatResult = applyQuatToVec4(v, q);

    // Step 3: Compare results
    EXPECT_TRUE(almostEqualVec4(eulerResult, quatResult));

    // Step 4: Ensure w is preserved
    EXPECT_DOUBLE_EQ(eulerResult.w, v.w);
    EXPECT_DOUBLE_EQ(quatResult.w, v.w);

    // Step 5: Check magnitude preservation (xyz only)
    Vec3 original3{ v.x, v.y, v.z };
    Vec3 rotated3{ quatResult.x, quatResult.y, quatResult.z };

    EXPECT_NEAR(magnitude(original3), magnitude(rotated3), EPS);
}


// ----------------------------
// Integration: Composition Pipeline
// ----------------------------
TEST(IntegrationTest, QuaternionCompositionMatchesSequentialRotation) {
    Vec3 v{ 1,0,0 };

    // Two rotations
    Quat q1 = quatFromAxisAngle({ 0,0,1 }, 45);
    Quat q2 = quatFromAxisAngle({ 0,0,1 }, 45);

    // Sequential rotation
    Vec3 step1 = quatRotate(q1, v);
    Vec3 sequential = quatRotate(q2, step1);

    // Combined rotation
    Quat combined = quatMultiply(q2, q1);
    Vec3 combinedResult = quatRotate(combined, v);

    EXPECT_TRUE(almostEqualVec3(sequential, combinedResult));
}

// ----------------------------
// Integration: Sequence of Euler Rotations to Original Vector
// ----------------------------
TEST(IntegrationTest, EulerFullRotationSequence) {
    Vec3 v{ 1,2,3 };
	double magnitudeBefore = magnitude(v);
	Vec3 normalized = v * (1.0 / magnitudeBefore); // normalize to avoid overflow
    Vec3 rotated = rotateEulerZ(normalized, 90);
	rotated = rotateEulerX(rotated, -90);
    rotated = rotateEulerY(rotated, 90);
	rotated = rotateEulerX(rotated, 90);
	Vec3 final = rotateEulerZ(rotated, 180);

	final = final * magnitudeBefore; // restore original magnitude
	EXPECT_TRUE(almostEqualVec3(v, final));
}

// ----------------------------
// Integration: Round Trip Conversion
// ----------------------------
TEST(IntegrationTest, QuaternionInverseRoundTrip) {
    Vec3 v{ 3, -2, 5 };

    Quat q = quatFromAxisAngle({ 1,1,1 }, 60);
    Quat qInv{ q.w, -q.x, -q.y, -q.z };

    Vec3 rotated = quatRotate(q, v);
    Vec3 recovered = quatRotate(qInv, rotated);

    EXPECT_TRUE(almostEqualVec3(v, recovered));
}


// ----------------------------
// Integration: Stress Test (Drift Detection)
// ----------------------------
TEST(IntegrationTest, RepeatedRotationStability) {
    Vec3 v{ 1,0,0 };
    Quat q = quatFromAxisAngle({ 0,0,1 }, 1); // small rotation

    Vec3 current = v;

    for (int i = 0; i < 360; i++) {
        current = quatRotate(q, current);
    }

    // After 360 * 1° rotations → should return to original
    EXPECT_TRUE(almostEqualVec3(current, v, 1e-3)); // relaxed tolerance
}


// ----------------------------
// Integration: Orthogonality Preservation
// ----------------------------
TEST(IntegrationTest, OrthogonalVectorsRemainOrthogonal) {
    Vec3 a{ 1,0,0 };
    Vec3 b{ 0,1,0 };

    Quat q = quatFromAxisAngle({ 1,1,1 }, 33);

    Vec3 a2 = quatRotate(q, a);
    Vec3 b2 = quatRotate(q, b);

    double dotResult = a2.x * b2.x + a2.y * b2.y + a2.z * b2.z;

    EXPECT_NEAR(dotResult, 0.0, EPS);
}

// ============================================================
// E2E TEST SCENARIO
// 3D Unit Cube Transformation Pipeline
//
// Scenario:
// A graphics programmer has the vertex coordinates of a
// 3D unit cube (side length = 2).
//
// The cube must:
//   1. Rotate 45 degrees around X axis
//   2. Rotate 45 degrees around Y axis
//
// This E2E test validates:
//   - Sequential quaternion rotations
//   - Transformation pipeline correctness
//   - Magnitude preservation
//   - Orthogonality preservation
//   - No NaN/Inf corruption
//   - Correct cube structure retention
// ============================================================

std::vector<Vec3> createUnitCubeVertices() {
	return {
		{ -1, -1, -1 }, // 0
		{  1, -1, -1 }, // 1
		{  1,  1, -1 }, // 2
		{ -1,  1, -1 }, // 3
		{ -1, -1,  1 }, // 4
		{  1, -1,  1 }, // 5
		{  1,  1,  1 }, // 6
		{ -1,  1,  1 }  // 7
	};
}

double distance(const Vec3& a, const Vec3& b) {
	return std::sqrt(
		(a.x - b.x) * (a.x - b.x) +
		(a.y - b.y) * (a.y - b.y) +
		(a.z - b.z) * (a.z - b.z)
	);
}

// ============================================================
// E2E TEST
// ============================================================

TEST(E2ETest, CubeRotationPipeline_X45_Y45) {

    // --------------------------------------------------------
    // Step 1:
    // Create Cube Vertices
    // --------------------------------------------------------

    std::vector<Vec3> cube =
        createUnitCubeVertices();

    ASSERT_EQ(cube.size(), 8);

    // --------------------------------------------------------
    // Step 2:
    // Create Rotations
    // --------------------------------------------------------

    Quat rotateX =
        quatFromAxisAngle(
            { 1,0,0 },
            45.0
        );

    Quat rotateY =
        quatFromAxisAngle(
            { 0,1,0 },
            45.0
        );

    // --------------------------------------------------------
    // Step 3:
    // Apply Sequential Rotations
    // --------------------------------------------------------

    std::vector<Vec3> transformed;

    for (const auto& vertex : cube) {

        // Rotate around X
        Vec3 xRotated =
            quatRotate(
                rotateX,
                vertex
            );

        // Rotate around Y
        Vec3 finalRotated =
            quatRotate(
                rotateY,
                xRotated
            );

        transformed.push_back(finalRotated);
    }

    ASSERT_EQ(transformed.size(), 8);

    // --------------------------------------------------------
    // Step 4:
    // Validate No NaN / Inf
    // --------------------------------------------------------

    for (const auto& v : transformed) {

        EXPECT_FALSE(std::isnan(v.x));
        EXPECT_FALSE(std::isnan(v.y));
        EXPECT_FALSE(std::isnan(v.z));

        EXPECT_FALSE(std::isinf(v.x));
        EXPECT_FALSE(std::isinf(v.y));
        EXPECT_FALSE(std::isinf(v.z));
    }

    // --------------------------------------------------------
    // Step 5:
    // Validate Magnitude Preservation
    //
    // Rotation should not change
    // distance from origin
    // --------------------------------------------------------

    for (size_t i = 0; i < cube.size(); i++) {

        double originalMag =
            magnitude(cube[i]);

        double rotatedMag =
            magnitude(transformed[i]);

        EXPECT_NEAR(
            originalMag,
            rotatedMag,
            EPS
        );
    }

    // --------------------------------------------------------
    // Step 6:
    // Validate Edge Length Preservation
    //
    // Cube edges should remain length 2
    // --------------------------------------------------------

    // Example edge:
    // Vertex 0 -> Vertex 1

    double originalEdge =
        distance(cube[0], cube[1]);

    double transformedEdge =
        distance(
            transformed[0],
            transformed[1]
        );

    EXPECT_NEAR(
        originalEdge,
        transformedEdge,
        EPS
    );

    EXPECT_NEAR(
        transformedEdge,
        2.0,
        EPS
    );

    // --------------------------------------------------------
    // Step 7:
    // Validate Orthogonality Preservation
    //
    // Adjacent cube edges should remain orthogonal
    // --------------------------------------------------------

    Vec3 edgeA{
        transformed[1].x - transformed[0].x,
        transformed[1].y - transformed[0].y,
        transformed[1].z - transformed[0].z
    };

    Vec3 edgeB{
        transformed[3].x - transformed[0].x,
        transformed[3].y - transformed[0].y,
        transformed[3].z - transformed[0].z
    };

    double dot =
        edgeA.x * edgeB.x +
        edgeA.y * edgeB.y +
        edgeA.z * edgeB.z;

    EXPECT_NEAR(dot, 0.0, EPS);

    // --------------------------------------------------------
    // Step 8:
    // Validate Deterministic Output
    // --------------------------------------------------------

    std::vector<Vec3> rerun;

    for (const auto& vertex : cube) {

        Vec3 xRotated =
            quatRotate(
                rotateX,
                vertex
            );

        Vec3 finalRotated =
            quatRotate(
                rotateY,
                xRotated
            );

        rerun.push_back(finalRotated);
    }

    for (size_t i = 0; i < transformed.size(); i++) {

        EXPECT_TRUE(
            almostEqualVec3(
                transformed[i],
                rerun[i]
            )
        );
    }
}

// ============================================================
// E2E TEST SCENARIO
// Shape Verification Using dot4 and cross3
//
// Scenario:
// A graphics programmer receives a set of vertices
// representing an unknown 3D shape.
//
// The programmer wants to verify whether the shape
// is a valid box (rectangular prism / cube).
//
// Validation Strategy:
//   1. Use cross3 to verify adjacent edges are
//      perpendicular (orthogonal faces)
//   2. Use dot4 to verify orthogonality
//   3. Verify opposite edges are parallel
//   4. Verify edge lengths are consistent
//
// This test validates the FULL geometry pipeline.
// ============================================================

// ============================================================
// Utility Functions
// ============================================================

Vec3 subtract(
    const Vec3& a,
    const Vec3& b
) {
    return {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

// ============================================================
// Shape Definition
//
// Cube / Box with side length = 2
// Centered at origin
// ============================================================

std::vector<Vec3> createShapeVertices() {

    return {
        {-1,-1,-1}, // 0
        { 1,-1,-1}, // 1
        { 1, 1,-1}, // 2
        {-1, 1,-1}, // 3

        {-1,-1, 1}, // 4
        { 1,-1, 1}, // 5
        { 1, 1, 1}, // 6
        {-1, 1, 1}  // 7
    };
}

// ============================================================
// E2E TEST
// ============================================================

TEST(E2ETest, VerifyShapeIsBoxUsingDotAndCross) {

    // --------------------------------------------------------
    // Step 1:
    // Load Unknown Shape
    // --------------------------------------------------------

    std::vector<Vec3> shape =
        createShapeVertices();

    ASSERT_EQ(shape.size(), 8);

    // --------------------------------------------------------
    // Step 2:
    // Construct Adjacent Edges
    //
    // Use vertex 0 as reference
    // --------------------------------------------------------

    Vec3 edgeX =
        subtract(shape[1], shape[0]);

    Vec3 edgeY =
        subtract(shape[3], shape[0]);

    Vec3 edgeZ =
        subtract(shape[4], shape[0]);

    // --------------------------------------------------------
    // Step 3:
    // Verify Orthogonality Using dot3
    //
    // Adjacent edges of a box must be perpendicular
    // --------------------------------------------------------

    Vec3 edgeX3{
        edgeX.x,
        edgeX.y,
        edgeX.z
    };

    Vec3 edgeY3{
        edgeY.x,
        edgeY.y,
        edgeY.z
    };

    Vec3 edgeZ3{
        edgeZ.x,
        edgeZ.y,
        edgeZ.z
    };

    double dotXY =
        dot3(edgeX3, edgeY3);

    double dotXZ =
        dot3(edgeX3, edgeZ3);

    double dotYZ =
        dot3(edgeY3, edgeZ3);

    EXPECT_NEAR(dotXY, 0.0, EPS);
    EXPECT_NEAR(dotXZ, 0.0, EPS);
    EXPECT_NEAR(dotYZ, 0.0, EPS);

    // --------------------------------------------------------
    // Step 4:
    // Verify Cross Products
    //
    // cross(X,Y) should align with Z
    // --------------------------------------------------------

    Vec3 crossXY =
        cross3(edgeX, edgeY);

    // Normalize comparison direction
    double crossMag =
        magnitude(crossXY);

    ASSERT_GT(crossMag, 0.0);

    Vec3 normalizedCross{
        crossXY.x / crossMag,
        crossXY.y / crossMag,
        crossXY.z / crossMag
    };

    double edgeZMag =
        magnitude(edgeZ);

    Vec3 normalizedZ{
        edgeZ.x / edgeZMag,
        edgeZ.y / edgeZMag,
        edgeZ.z / edgeZMag
    };

    // Cross product should point along Z axis
    EXPECT_TRUE(
        almostEqual(
            normalizedCross.x,
            normalizedZ.x
        )
    );

    EXPECT_TRUE(
        almostEqual(
            normalizedCross.y,
            normalizedZ.y
        )
    );

    EXPECT_TRUE(
        almostEqual(
            normalizedCross.z,
            normalizedZ.z
        )
    );

    // --------------------------------------------------------
    // Step 5:
    // Verify Edge Length Consistency
    // --------------------------------------------------------

    double lenX =
        magnitude(edgeX);

    double lenY =
        magnitude(edgeY);

    double lenZ =
        magnitude(edgeZ);

    EXPECT_NEAR(lenX, 2.0, EPS);
    EXPECT_NEAR(lenY, 2.0, EPS);
    EXPECT_NEAR(lenZ, 2.0, EPS);

    // --------------------------------------------------------
    // Step 6:
    // Verify Opposite Edges Parallel
    // --------------------------------------------------------

    Vec3 oppositeX =
        subtract(shape[2], shape[3]);

    Vec3 crossParallel =
        cross3(edgeX, oppositeX);

    EXPECT_NEAR(
        magnitude(crossParallel),
        0.0,
        EPS
    );

    // --------------------------------------------------------
    // Step 7:
    // Verify No Invalid Values
    // --------------------------------------------------------

    for (const auto& v : shape) {

        EXPECT_FALSE(std::isnan(v.x));
        EXPECT_FALSE(std::isnan(v.y));
        EXPECT_FALSE(std::isnan(v.z));

        EXPECT_FALSE(std::isinf(v.x));
        EXPECT_FALSE(std::isinf(v.y));
        EXPECT_FALSE(std::isinf(v.z));
    }

    // --------------------------------------------------------
    // Step 8:
    // Final Validation
    //
    // If all geometric properties hold:
    // Shape is verified as a valid box
    // --------------------------------------------------------

    SUCCEED();
}

// ============================================================
// MAIN
// ============================================================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

