/*
* Author:      Abirov Ansat
* Description: Naive solution
* Complexity:  O(N^4)
* Details:     Consider all possible turns(O(N^2)) and 
               check that at least 1 row or column has 3 in a row
* Elapsed time: 1.5h
*/

#include <iostream>
#include <algorithm>

bool check_3_in_a_row(int** field, int n, int m) {
    // rows
    for (int i = 0; i < n; ++i) {
        int max_length = 1;
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == 0) {
                max_length = 1;
                continue;
            }

            if (j > 0 && field[i][j] == field[i][j - 1]) {
                max_length++;
                if (max_length == 3) {
                    return true;
                }
            }
            else {
                max_length = 1;
            }
        }
    }
    // columns
    for (int j = 0; j < m; ++j) {
        int max_length = 1;
        for (int i = 0; i < n; ++i) {
            if (field[i][j] == 0) {
                max_length = 1;
                continue;
            }

            if (i > 0 && field[i][j] == field[i - 1][j]) {
                max_length++;
                if (max_length == 3) {
                    return true;
                }
            }
            else {
                max_length = 1;
            }
        }
    }

    return false;
}

bool is_possible_turn(int **field, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n) {
                std::swap(field[i][j], field[i + 1][j]);
                bool result = check_3_in_a_row(field, n, m);
                std::swap(field[i][j], field[i + 1][j]);
                if (result) {
                    return true;
                }
            }
            if (j + 1 < m) {
                std::swap(field[i][j], field[i][j + 1]);
                bool result = check_3_in_a_row(field, n, m);
                std::swap(field[i][j], field[i][j + 1]);
                if (result) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    // init
    const int N = 6, M = 6;
    int **field = new int*[N];
    for (int i = 0; i < N; ++i) {
        field[i] = new int[M];
    }

    // input
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> field[i][j];
        }
    }
    
    // output
    std::cout << (is_possible_turn(field, N, M) ? "Yes" : "No");

    return 0;
}