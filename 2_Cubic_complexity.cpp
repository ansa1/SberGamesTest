/*
*   Author:      Abirov Ansat
*   Description: Decrease checking rows/columns to 2
*   Complexity:  O(N^3)
*   Details:     Consider all possible turns(O(N^2)) and 
                 check only 2 rows or columns
*   Elapsed time: 1h
*/

#include <iostream>
#include <algorithm>

/*
    After the move there are only 2 changed cells. 
    It means that it is enough to check only two rows or two columns.
    This optimization decreases complexity to O(N^2 * (4N)) -> O(N^3)
*/
bool check_row(int** field, int n, int m, int row_id);
bool check_column(int** field, int n, int m, int column_id);

bool check_3_in_a_row(int** field, int n, int m, int index,  bool row_swap) {
    if (row_swap) {
        return check_row(field, n, m, index) ||
            check_row(field, n, m, index + 1);
    }
    else {
        return check_column(field, n, m, index) || 
            check_column(field, n, m, index + 1);
    }
}

bool check_row(int** field, int n, int m, int row_id) {
    int max_length = 1;
    for (int j = 1; j < m; ++j) {
        if (field[row_id][j] == 0) {
            max_length = 1;
            continue;
        }

        if (field[row_id][j] == field[row_id][j - 1]) {
            max_length++;
            if (max_length == 3) {
                return true;
            }
        }
        else {
            max_length = 1;
        }
    }

    return false;
}

bool check_column(int** field, int n, int m, int column_id) {
    int max_length = 1;
    for (int i = 1; i < n; ++i) {
        if (field[i][column_id] == 0) {
            max_length = 1;
            continue;
        }

        if (field[i][column_id] == field[i - 1][column_id]) {
            max_length++;
            if (max_length == 3) {
                return true;
            }
        }
        else {
            max_length = 1;
        }
    }

    return false;
}

bool is_possible_turn(int **field, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n) {
                std::swap(field[i][j], field[i + 1][j]);
                bool result = check_3_in_a_row(field, n, m, i, true);
                std::swap(field[i][j], field[i + 1][j]);
                if (result) {
                    return true;
                }
            }
            if (j + 1 < m) {
                std::swap(field[i][j], field[i][j + 1]);
                bool result = check_3_in_a_row(field, n, m, j, false);
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