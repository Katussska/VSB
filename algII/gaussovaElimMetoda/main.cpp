#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>
#include <cmath>

class GaussElimination {
private:
    std::vector<std::vector<float>> matrix;
    std::vector<float> constants;
    std::vector<float> result;

public:
    GaussElimination(std::vector<std::vector<float>> A, std::vector<float> B) {
        matrix = std::move(A);
        constants = std::move(B);
    }

    void forwardElimination() {
        int rows = matrix.size();
        for (int i = 0; i < rows - 1; ++i) {
            if (matrix[i][i] == 0) {
                for (int k = i + 1; k < rows; ++k) {
                    if (matrix[k][i] != 0) {
                        std::swap(matrix[i], matrix[k]);
                        std::swap(constants[i], constants[k]);
                        break;
                    }
                }
            }

            for (int j = i + 1; j < rows; ++j) {
                float factor = matrix[j][i] / matrix[i][i];
                for (int k = i; k < rows; ++k) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
                constants[j] -= factor * constants[i];
            }
        }
    }

    void backSubstitution() {
        int rows = matrix.size();
        result.resize(rows);

        for (int i = rows - 1; i >= 0; --i) {
            float sum = 0.0;
            for (int j = i + 1; j < rows; ++j) {
                sum += matrix[i][j] * result[j];
            }
            result[i] = (constants[i] - sum) / matrix[i][i];
        }
    }

    std::vector<float> solve() {
        forwardElimination();
        backSubstitution();
        return result;
    }
};

void printResult(const std::vector<float> &result) {
    if (result.empty()) {
        std::cout << "Result: Nekonecne mnoho reseni" << std::endl;
    } else {
        std::cout << "Result: {";
        for (float val: result) {
            std::cout << val << ", ";
        }
        std::cout << "}" << std::endl;
    }
}

int main() {
    std::vector<std::vector<float>> A_1 = {
            {1, 2,  -3, 4, 5},
            {2, 1,  0,  3, 0},
            {0, 2,  1,  2, -1},
            {3, -1, 0,  5, 2},
            {2, 1,  2,  3, -4}
    };
    std::vector<float> B_1 = {4, 9, 5, 3, 2};

    GaussElimination system1(A_1, B_1);
    std::vector<float> result1 = system1.solve();
    if (std::isnan(result1[0])) {
        printResult(std::vector<float>());
    } else {
        printResult(result1);
    }

    std::vector<std::vector<float>> A_2 = {
            {2,  4,  -2, -2},
            {1,  2,  4,  -3},
            {-3, -3, 8,  -2},
            {-1, 1,  6,  -3}
    };
    std::vector<float> B_2 = {-4, 5, 7, 7};

    GaussElimination system2(A_2, B_2);
    std::vector<float> result2 = system2.solve();
    if (std::isnan(result2[0])) {
        printResult(std::vector<float>());
    } else {
        printResult(result2);
    }

    std::vector<std::vector<float>> A_3 = {
            {1,  2,  3,  4,  5},
            {6,  7,  8,  9,  10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20},
            {21, 22, 23, 24, 25}
    };
    std::vector<float> B_3 = {1, 2, 3, 4, 5};

    GaussElimination system3(A_3, B_3);
    std::vector<float> result3 = system3.solve();
    if (std::isnan(result3[0])) {
        printResult(std::vector<float>());
    } else {
        printResult(result3);
    }

    std::vector<std::vector<float>> A_4 = {
            {2, 5, 0, 8},
            {1, 4, 2, 6},
            {7, 8, 9, 3},
            {1, 5, 7, 8}
    };
    std::vector<float> B_4 = {6, 5, 4, 3};

    GaussElimination system4(A_4, B_4);
    std::vector<float> result4 = system4.solve();
    if (std::isnan(result4[0])) {
        printResult(std::vector<float>());
    } else {
        printResult(result4);
    }

    return 0;
}