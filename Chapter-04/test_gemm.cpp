//
// Created by sammorley on 31/12/24.
//

#include "gemm.h"

#include <random>

#include <gtest/gtest.h>

#include "matrix.h"

using namespace ct;



class GemmTest : public ::testing::Test {

protected:
    static constexpr ptrdiff_t n_rows = 250;
    static constexpr ptrdiff_t n_cols = 250;
    Matrix<double> a;
    Matrix<double> b;
    Matrix<double> c;

    GemmTest() : a(n_rows, n_cols), b(n_cols, n_rows), c(n_rows, n_cols) {
    }

    void SetUp() override {
        std::fill_n(a.data(), a.size(), 1.0);
        std::fill_n(b.data(), b.size(), 1.0);
    }


};


TEST(BasicGemmTest, TestMulIdentity) {
    const auto n_rows = 10;
    const auto n_cols = 10;
    Matrix<double> A(n_rows, n_cols);
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(-1., 1.);
    for (auto& entry : A.to_span()) {
        entry = dist(rng);
    }

    Matrix<double> I(n_rows, n_cols);
    auto* I_data = I.data();
    for (size_t i=0; i < n_rows; i++) {
        I_data[i*(n_rows + 1)] = 1.0;
    }

    Matrix<double> left_result(n_rows, n_cols);
    dgemm_basic(A, I, left_result, 1.0, 0.0);

    Matrix<double> right_result(n_rows, n_cols);
    dgemm_basic(I, A, right_result, 1.0, 0.0);

    EXPECT_LT(matrix_max_abs_difference(A, left_result), 1e-15);

    EXPECT_LT(matrix_max_abs_difference(A, right_result), 1e-15);
}


TEST(BasicGemmTest, TestAgainstInverse) {
    const auto n_rows = 3;
    const auto n_cols = 3;
    // working out a 3x3 inverse by hand is not too much of a chore,
    // but let's not risk a random matrix that might be singular.
    Matrix<double> A(n_rows, n_cols);
    A.at(0, 0) = 1.0;
    A.at(0, 1) = -1.0;
    A.at(0, 2) = 0.0;
    A.at(1, 0) = 0.5;
    A.at(1, 1) = 0.5;
    A.at(1, 2) = 3;
    A.at(2, 0) = -0.5;
    A.at(2, 1) = 0.5;
    A.at(2, 2) = 2.0;

    // expand along the top row to compute the determinant. The result should be 2
    auto detA = A.at(0,0)*(A.at(1, 1) * A.at(2,2) - A.at(1,2)*A.at(2, 1))
        - A.at(0, 1) * (A.at(1, 0) * A.at(2, 2) - A.at(1, 2)*A.at(2, 0));

    EXPECT_EQ(detA, 2.0);


}


TEST_F(GemmTest, TestBlockedAgainstBasic) {
    Matrix<double> expected(n_rows, n_cols);
    dgemm_basic(a, b, expected, 2.0, 0.0);

    dgemm_blocked(a, b, c, 2.0, 0.0, 64);

    EXPECT_LE(matrix_max_abs_difference(c, expected), 1e-12);
}