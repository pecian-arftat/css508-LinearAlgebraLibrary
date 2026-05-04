\# 🔗 Integration Test (End-to-End Pipeline)



This test simulates a realistic transformation flow:



1\. Start with a 4D vector (homogeneous coordinates)

2\. Apply Euler rotation

3\. Convert to quaternion and rotate

4\. Compare results

5\. Validate invariants (length, orthogonality)

6\. Ensure `w` component is preserved



\---



\## 🧪 Code



```cpp

// ----------------------------

// Integration Tests

// ----------------------------



Vec4 applyEulerToVec4(const Vec4\& v, double angleDeg) {

&#x20;   Vec3 rotated = rotateEulerZ({v.x, v.y, v.z}, angleDeg);

&#x20;   return {rotated.x, rotated.y, rotated.z, v.w}; // preserve w

}



Vec4 applyQuatToVec4(const Vec4\& v, const Quat\& q) {

&#x20;   Vec3 rotated = quatRotate(q, {v.x, v.y, v.z});

&#x20;   return {rotated.x, rotated.y, rotated.z, v.w}; // preserve w

}



double magnitude4(const Vec4\& v) {

&#x20;   return std::sqrt(v.x\*v.x + v.y\*v.y + v.z\*v.z + v.w\*v.w);

}



bool almostEqualVec4(const Vec4\& a, const Vec4\& b, double eps = EPS) {

&#x20;   return almostEqual(a.x, b.x, eps) \&\&

&#x20;          almostEqual(a.y, b.y, eps) \&\&

&#x20;          almostEqual(a.z, b.z, eps) \&\&

&#x20;          almostEqual(a.w, b.w, eps);

}





// Full pipeline integration test

TEST(IntegrationTest, EulerQuaternion4DConsistencyPipeline) {

&#x20;   Vec4 v{1.0, 2.0, 3.0, 1.0};  // homogeneous point

&#x20;   double angle = 90.0;



&#x20;   // Step 1: Euler rotation

&#x20;   Vec4 eulerResult = applyEulerToVec4(v, angle);



&#x20;   // Step 2: Quaternion rotation

&#x20;   Quat q = quatFromAxisAngle({0,0,1}, angle);

&#x20;   Vec4 quatResult = applyQuatToVec4(v, q);



&#x20;   // Step 3: Compare results

&#x20;   EXPECT\_TRUE(almostEqualVec4(eulerResult, quatResult));



&#x20;   // Step 4: Ensure w is preserved

&#x20;   EXPECT\_DOUBLE\_EQ(eulerResult.w, v.w);

&#x20;   EXPECT\_DOUBLE\_EQ(quatResult.w, v.w);



&#x20;   // Step 5: Check magnitude preservation (xyz only)

&#x20;   Vec3 original3{v.x, v.y, v.z};

&#x20;   Vec3 rotated3{quatResult.x, quatResult.y, quatResult.z};



&#x20;   EXPECT\_NEAR(magnitude(original3), magnitude(rotated3), EPS);

}





// ----------------------------

// Integration: Composition Pipeline

// ----------------------------

TEST(IntegrationTest, QuaternionCompositionMatchesSequentialRotation) {

&#x20;   Vec3 v{1,0,0};



&#x20;   // Two rotations

&#x20;   Quat q1 = quatFromAxisAngle({0,0,1}, 45);

&#x20;   Quat q2 = quatFromAxisAngle({0,0,1}, 45);



&#x20;   // Sequential rotation

&#x20;   Vec3 step1 = quatRotate(q1, v);

&#x20;   Vec3 sequential = quatRotate(q2, step1);



&#x20;   // Combined rotation

&#x20;   Quat combined = quatMultiply(q2, q1);

&#x20;   Vec3 combinedResult = quatRotate(combined, v);



&#x20;   EXPECT\_TRUE(almostEqualVec3(sequential, combinedResult));

}





// ----------------------------

// Integration: Round Trip Conversion

// ----------------------------

TEST(IntegrationTest, QuaternionInverseRoundTrip) {

&#x20;   Vec3 v{3, -2, 5};



&#x20;   Quat q = quatFromAxisAngle({1,1,1}, 60);

&#x20;   Quat qInv{q.w, -q.x, -q.y, -q.z};



&#x20;   Vec3 rotated = quatRotate(q, v);

&#x20;   Vec3 recovered = quatRotate(qInv, rotated);



&#x20;   EXPECT\_TRUE(almostEqualVec3(v, recovered));

}





// ----------------------------

// Integration: Stress Test (Drift Detection)

// ----------------------------

TEST(IntegrationTest, RepeatedRotationStability) {

&#x20;   Vec3 v{1,0,0};

&#x20;   Quat q = quatFromAxisAngle({0,0,1}, 1); // small rotation



&#x20;   Vec3 current = v;



&#x20;   for (int i = 0; i < 360; i++) {

&#x20;       current = quatRotate(q, current);

&#x20;   }



&#x20;   // After 360 \* 1° rotations → should return to original

&#x20;   EXPECT\_TRUE(almostEqualVec3(current, v, 1e-3)); // relaxed tolerance

}





// ----------------------------

// Integration: Orthogonality Preservation

// ----------------------------

TEST(IntegrationTest, OrthogonalVectorsRemainOrthogonal) {

&#x20;   Vec3 a{1,0,0};

&#x20;   Vec3 b{0,1,0};



&#x20;   Quat q = quatFromAxisAngle({1,1,1}, 33);



&#x20;   Vec3 a2 = quatRotate(q, a);

&#x20;   Vec3 b2 = quatRotate(q, b);



&#x20;   double dotResult = a2.x\*b2.x + a2.y\*b2.y + a2.z\*b2.z;



&#x20;   EXPECT\_NEAR(dotResult, 0.0, EPS);

}

```



\---



\# 🧠 Why These Are \*Real\* Integration Tests



These aren’t just bigger unit tests—they validate:



\### ✅ Full pipeline correctness



\* Input → transform → output across multiple systems



\### 🔄 Cross-representation agreement



\* Euler vs Quaternion



\### 🔗 Composition logic



\* Sequential vs combined rotations



\### 🔁 System stability over time



\* Drift detection (huge for graphics/physics engines)



\### 📦 4D correctness



\* Proper handling of homogeneous coordinates (`w`)



\---



\# 🚀 If You Want to Go Even Further



I can extend this with:



\* Randomized integration tests (Monte Carlo style)

\* Matrix + quaternion + Euler triple-consistency tests

\* SIMD vs scalar validation (for performance code)

\* CI-ready test harness with coverage thresholds



Just say the word.



