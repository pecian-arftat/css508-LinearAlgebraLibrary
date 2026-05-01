// Generated Automated Unit Test

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