/*
*   Author:      Abirov Ansat
*   Description: Decrease checking rows/columns to 2 and check only 5 cells
*   Complexity:  O(N^2)
*   Details:     Consider all possible turns(O(N^2)), check only required rows/columns.
*                Check row or column with constant complexity.
*   Elapsed time: 4h
*/

#include <iostream>
#include <algorithm>
#include <vector>

/*
    After the move there are only 2 changed cells. 
    It means that it is enough to check only (2 rows and 1 column) or (2 columns and 1 row).
    This optimization decreases complexity to O(N^3)

    Then, we do not have to check all row or all column. 
    After making a turn, we need to check previous 2 and next 2 cells
    Finally, complexity decreases to O(N^2), 
    because function to check a row or column becomes a constant.
*/
bool check_row(int** field, int n, int m, int index_i, int index_j);
bool check_column(int** field, int n, int m, int index_i, int index_j);

bool check_match_3(int** field, int n, int m, int index_i, int index_j,  bool row_swap) {
    if (row_swap) {
        return check_row(field, n, m, index_i, index_j) ||
            check_row(field, n, m, index_i + 1, index_j) ||
            check_column(field, n, m, index_i, index_j);
    }
    else {
        return check_column(field, n, m, index_i, index_j) || 
            check_column(field, n, m, index_i, index_j + 1) ||
            check_row(field, n, m, index_i, index_j);
    }
}

bool check_row(int** field, int n, int m, int index_i, int index_j) {
    std::vector<int> row;
    for (int j = index_j - 3; j <= index_j + 3; ++j) {
        if (j < 0 || j >= m)
            continue;
        row.push_back(field[index_i][j]);
    }

    int max_in_row = 1;
    for (int i = 1; i < row.size(); ++i) {
        if (row[i] == 0) {
            max_in_row = 1;
            continue;
        }
        if (row[i] == row[i - 1]) {
            ++max_in_row;
            if (max_in_row == 3)
                return true;
        }
        else {
            max_in_row = 1;
        }
    }

    return false;
}

bool check_column(int** field, int n, int m, int index_i, int index_j) {
    std::vector<int> column;
    for (int i = index_i - 3; i <= index_i + 3; ++i) {
        if (i < 0 || i >= n)
            continue;
        column.push_back(field[i][index_j]);
    }
    int max_in_column = 1;
    for (int i = 1; i < column.size(); ++i) {
        if (column[i] == 0) {
            max_in_column = 1;
            continue;
        }
        if (column[i] == column[i - 1]) {
            ++max_in_column;
            if (max_in_column == 3)
                return true;
        }
        else {
            max_in_column = 1;
        }
    }

    return false;
}

bool is_possible_turn(int **field, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n) {
                std::swap(field[i][j], field[i + 1][j]);
                bool possible = check_match_3(field, n, m, i, j, true);
                std::swap(field[i][j], field[i + 1][j]);
                if (possible) {
                    fprintf(stderr, "move: (%d, %d) <-> (%d, %d);\n", i, j, i + 1, j);
                    return true;
                }
            }
            if (j + 1 < m) {
                std::swap(field[i][j], field[i][j + 1]);
                bool possible = check_match_3(field, n, m, i, j, false);
                std::swap(field[i][j], field[i][j + 1]);
                if (possible) {
                    fprintf(stderr, "move: (%d, %d) <-> (%d, %d);\n", i, j, i, j + 1);
                    return true;
                }
            }
        }
    }
    return false;
}
/*
*   Function deletes matched cells and return false if nothing to delete
*/
bool delete_match_3(int** field, int n, int m) {
    bool **matched_cells = new bool*[n];
    for (int i = 0; i < n; ++i) {
        matched_cells[i] = new bool[m];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matched_cells[i][j] = false;
        }
    }

    // find match in rows
    for (int i = 0; i < n; ++i) {
        int max_in_row = 1;
        for (int j = 1; j < m; ++j) {
            if (field[i][j] == 0 ||
                field[i][j] != field[i][j - 1]) {
                if (max_in_row >= 3) {
                    for (int k = 0, pos_j = j - 1; k < max_in_row; ++k, --pos_j) {
                        matched_cells[i][pos_j] = true;
                    }
                }
                max_in_row = 1;
                continue;
            }

            max_in_row++;
        }
        if (max_in_row >= 3) {
            for (int k = 0, pos_j = m - 1; k < max_in_row; ++k, --pos_j) {
                matched_cells[i][pos_j] = true;
            }
        }
    }
    // find match in columns
    for (int j = 0; j < m; ++j) {
        int max_in_row = 1;
        for (int i = 1; i < n; ++i) {
            if (field[i][j] == 0 ||
                field[i][j] != field[i - 1][j]) {
                if (max_in_row >= 3) {
                    for (int k = 0, pos_i = i - 1; k < max_in_row; ++k, --pos_i) {
                        matched_cells[pos_i][j] = true;
                    }
                }
                max_in_row = 1;
                continue;
            }

            max_in_row++;
        }
        if (max_in_row >= 3) {
            for (int k = 0, pos_i = n - 1; k < max_in_row; ++k, --pos_i) {
                matched_cells[pos_i][j] = true;
            }
        }
    }

    // delete matched cells
    bool result = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matched_cells[i][j]) {
                result = true;
                field[i][j] = 0;
            }
        }
    }
    return result;
}

void shift_to_bottom(int** field, int n, int m) {
    /* Naive O(N^3) shift:

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i + 1 < n; ++i) {
            while (field[i][j] != 0 && field[i + 1][j] == 0) {
                std::swap(field[i][j], field[i + 1][j]);
            }
        }
    }
    */

    // N^2 shift
    for (int j = 0; j < m; ++j) {
        std::vector<int> column;
        for (int i = 0; i < n; ++i) {
            if (field[i][j] != 0) {
                column.push_back(field[i][j]);
            }
        }
        for (int i = n - 1, k = column.size() - 1; i >= 0; --i, --k) {
                field[i][j] = (k >= 0 ? column[k] : 0);
        }
    }
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

    /*
        Preprocessing:

        Given field possibly has 3 in a row. 
        Delete all such cells and shift others to bottom
    */
    while (delete_match_3(field, N, M)) {
        shift_to_bottom(field, N, M);
    }

    std::cerr << "Field after deleting matched cells:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cerr << field[i][j] << " ";
        }
        std::cerr << "\n";
    }
    
    // output
    std::cout << "Is move possible: " << (is_possible_turn(field, N, M) ? "Yes" : "No");

    return 0;
}