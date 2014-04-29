/*
 * Copyright (C) 2012-2014 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>

#include "ignition/math/Helpers.hh"
#include "ignition/math/Matrix3d.hh"

using namespace ignition;

/////////////////////////////////////////////////
TEST(Matrix3dTest, Matrix3d)
{
  {
    math::Matrix3d matrix;
    EXPECT_TRUE(matrix == math::Matrix3d(0, 0, 0, 0, 0, 0, 0, 0, 0));
  }

  {
    math::Matrix3d matrix(1, 2, 3, 4, 5, 6, 7, 8, 9);
    EXPECT_TRUE(matrix == math::Matrix3d(1, 2, 3, 4, 5, 6, 7, 8, 9));

    math::Matrix3d matrix1(matrix);
    EXPECT_TRUE(matrix1 == math::Matrix3d(1, 2, 3, 4, 5, 6, 7, 8, 9));
  }

  math::Matrix3d matrix;
  matrix.SetFromAxes(math::Vector3d(1, 1, 1), math::Vector3d(2, 2, 2),
                     math::Vector3d(3, 3, 3));
  EXPECT_TRUE(matrix == math::Matrix3d(1, 2, 3, 1, 2, 3, 1, 2, 3));

  matrix.SetFromAxis(math::Vector3d(1, 1, 1), M_PI);
  EXPECT_TRUE(matrix == math::Matrix3d(1, 2, 2, 2, 1, 2, 2, 2, 1));

  matrix.SetCol(0, math::Vector3d(3, 4, 5));
  EXPECT_TRUE(matrix == math::Matrix3d(3, 2, 2, 4, 1, 2, 5, 2, 1));

  EXPECT_THROW(matrix.SetCol(3, math::Vector3d(1, 1, 1)),
      ignition::math::IndexException);
}

/////////////////////////////////////////////////
TEST(Matrix3dTest, IndexException)
{
  math::Matrix3d mat = math::Matrix3d::Zero;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      EXPECT_NO_THROW(mat(i, j));

  EXPECT_THROW(math::equal(mat(3, 0), 0.0), math::IndexException);
  EXPECT_THROW(math::equal(mat(0, 3), 0.0), math::IndexException);
  EXPECT_THROW(math::equal(mat(3, 3), 0.0), math::IndexException);

  EXPECT_THROW(mat(3, 0) = 0, math::IndexException);
  EXPECT_THROW(mat(0, 3) = 0, math::IndexException);
  EXPECT_THROW(mat(3, 3) = 0, math::IndexException);

  const math::Matrix3d constMat(math::Matrix3d::Zero);

  EXPECT_THROW(math::equal(constMat(3, 0), 0.0), math::IndexException);
  EXPECT_THROW(math::equal(constMat(0, 3), 0.0), math::IndexException);
  EXPECT_THROW(math::equal(constMat(3, 3), 0.0), math::IndexException);
}

/////////////////////////////////////////////////
TEST(Matrix3dTest, OperatorSubtract)
{
  math::Matrix3d matZero = math::Matrix3d::Zero;
  math::Matrix3d matIdent = math::Matrix3d::Identity;

  math::Matrix3d mat = matIdent - matZero;
  EXPECT_EQ(mat, matIdent);

  math::Matrix3d matA(1, 2, 3,
                      4, 5, 6,
                      7, 8, 9);

  math::Matrix3d matB(10, 20, 30,
                      40, 50, 60,
                      70, 80, 90);

  mat = matB - matA;
  EXPECT_EQ(mat, math::Matrix3d(9, 18, 27, 36, 45, 54, 63, 72, 81));
}

/////////////////////////////////////////////////
TEST(Matrix3dTest, OperatorAdd)
{
  math::Matrix3d matZero = math::Matrix3d::Zero;
  math::Matrix3d matIdent = math::Matrix3d::Identity;

  math::Matrix3d mat = matIdent + matZero;
  EXPECT_EQ(mat, matIdent);

  math::Matrix3d matA(1, 2, 3,
                      4, 5, 6,
                      7, 8, 9);

  math::Matrix3d matB(10, 20, 30,
                      40, 50, 60,
                      70, 80, 90);

  mat = matB + matA;
  EXPECT_EQ(mat, math::Matrix3d(11, 22, 33, 44, 55, 66, 77, 88, 99));
}

/////////////////////////////////////////////////
TEST(Matrix3dTest, OperatorMul)
{
  math::Matrix3d matZero = math::Matrix3d::Zero;
  math::Matrix3d matIdent = math::Matrix3d::Identity;

  math::Matrix3d mat = matIdent * matZero;
  EXPECT_EQ(mat, matZero);

  math::Matrix3d matA(1, 2, 3,
                      4, 5, 6,
                      7, 8, 9);

  math::Matrix3d matB(10, 20, 30,
                      40, 50, 60,
                      70, 80, 90);

  mat = matA * matB;
  EXPECT_EQ(mat, math::Matrix3d(300, 360, 420,
                                660, 810, 960,
                                1020, 1260, 1500));

  mat = matB * matA;
  EXPECT_EQ(mat, math::Matrix3d(300, 360, 420,
                                660, 810, 960,
                                1020, 1260, 1500));

  mat = mat * 2.0;
  EXPECT_EQ(mat, math::Matrix3d(600, 720, 840,
                                1320, 1620, 1920,
                                2040, 2520, 3000));
}

/////////////////////////////////////////////////
TEST(Matrix3dTest, OperatorStreamOut)
{
  math::Matrix3d matA(1, 2, 3,
                      4, 5, 6,
                      7, 8, 9);

  std::ostringstream stream;
  stream << matA;
  EXPECT_EQ(stream.str(), "1 2 3 4 5 6 7 8 9");
}

/////////////////////////////////////////////////
TEST(Matrix3dTest, OperatorStreamIn)
{
  math::Matrix3d mat;
  EXPECT_EQ(mat, math::Matrix3d::Zero);

  std::istringstream stream("1 2 3 4 5 6 7 8 9");
  stream >> mat;
  EXPECT_EQ(mat, math::Matrix3d(1, 2, 3, 4, 5, 6, 7, 8, 9));
}