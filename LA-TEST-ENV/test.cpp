// Unit tests for LinearAlgebra.h using Google Test framework

#include "pch.h"

#include <iostream>

#include <gtest/gtest.h>
#include <tuple>

#include "LinearAlgebra.h"

// ----------------------------
// Dot Product Tests
// ----------------------------
TEST(DotProductTest, Basic) {
    Vec4 a{ 1,2,3,4 };
    EXPECT_DOUBLE_EQ(dot4(a, a), 30);
}

TEST(DotProductTest, Orthogonal) {
    Vec4 a{ 1,0,0,0 };
    Vec4 b{ 0,1,0,0 };
    EXPECT_DOUBLE_EQ(dot4(a, b), 0);
}

TEST(DotProductTest, Commutative) {
    Vec4 a{ 1,2,3,4 };
    Vec4 b{ 4,3,2,1 };
    EXPECT_DOUBLE_EQ(dot4(a, b), dot4(b, a));
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

