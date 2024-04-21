#include <stdio.h>

#define ROWS 3
#define COLS 3

int shumaMatrices(int matrica[][COLS], int row, int col) {
    if (row == ROWS) {
        return 0;
    }

    int element = matrica[row][col];
    int nextCol = (col + 1) % COLS;
    int nextRow = row + (nextCol == 0 ? 1 : 0);
    return element + shumaMatrices(matrica, nextRow, nextCol);
}

int main() {
    int matrica[ROWS][COLS] = {
        {2, 2, 3},
        {4, 5, 5},
        {8, 8, 8}
    };

    int totali = shumaMatrices(matrica, 0, 0);
    printf("Shuma e elmenteve te matrices: %d\n", totali);

    return 0;
}
