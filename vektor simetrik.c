#include <stdio.h>
#include <stdbool.h>

bool vektoriSimetrik(int vec[], int start, int end) {
    if (start >= end) {
        return true;
    }

    if (vec[start] != vec[end]) {
        return false;
    }

    return vektoriSimetrik(vec, start + 1, end - 1);
}

int main() {
    int vektor1[] = {1, 2, 3, 4, 3, 2, 1};
    int vektor2[] = {1, 2, 3, 4, 5, 6, 7};

    int size1 = sizeof(vektor1) / sizeof(vektor1[0]);
    int size2 = sizeof(vektor2) / sizeof(vektor2[0]);

    if (vektoriSimetrik(vektor1, 0, size1 - 1)) {
        printf("Vektori 1 eshte simetrik.\n");
    } else {
        printf("Vektori 1 nuk eshte simetrik.\n");
    }

    if (vektoriSimetrik(vektor2, 0, size2 - 1)) {
        printf("Vektori 2 eshte simetrik.\n");
    } else {
        printf("Vektori 2 nuk eshte simetrik.\n");
    }

    return 0;
}
