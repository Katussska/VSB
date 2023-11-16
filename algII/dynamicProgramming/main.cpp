#include <iostream>
#include <vector>

using namespace std;

int RobotCoinCollection(vector<vector<int>>& board) {
    int rows = board.size(); // n
    int columns = board[0].size(); // m

    vector<vector<int>> F(rows, vector<int>(columns, 0));

    F[0][0] = board[0][0];

    for (int j = 1; j < columns; ++j) {
        F[0][j] = F[0][j - 1] + board[0][j];
    }

   for (int i = 1; i < rows; ++i) {
        F[i][0] = F[i - 1][0] + board[i][0];
    }

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < columns; ++j) {
            F[i][j] = max(F[i - 1][j], F[i][j - 1]) + board[i][j];
        }
    }

    return F[rows - 1][columns - 1];
}

int main() {
    vector<vector<int>> board = {
            {1, 0, 1, 0, 1},
            {1, 1, 0, 1, 0},
            {0, 1, 1, 0, 1},
            {1, 0, 1, 1, 0}
    };

    int maxCoins = RobotCoinCollection(board);
    cout << "Maximum number of coins collected: " << maxCoins << endl;

    vector<vector<int>> board2 = {
            {0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
            {0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 0, 1, 1, 0, 1, 1},
            {0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 0, 0, 0},
            {1, 1, 1, 0, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
            {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
            {0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 1, 0},
            {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
            {0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
            {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
            {0, 0, 0, 0, 1, 1, 1, 0, 1, 1},
            {0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
            {1, 1, 1, 1, 0, 1, 0, 1, 1, 0},
            {1, 1, 1, 0, 1, 1, 0, 0, 0, 1}
    };

    maxCoins = RobotCoinCollection(board2);
    cout << "Maximum number of coins collected: " << maxCoins << endl;

    return 0;
}
