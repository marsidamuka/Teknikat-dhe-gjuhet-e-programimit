#include <stdio.h>

int sasiaPozitivCift(int v[], int n);

int main(void) {

    int x = 0;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    x = sasiaPozitivCift(a, 10);
    printf("Sasia e numrave pozitive cift ne vektor eshte: %d\n", x);

    printf("\n");
    return 0;
}

int sasiaPozitivCift(int v[], int n) {
    if (n == 0) {
        return 0;
    }
    if ((v[n - 1] % 2 == 0) && (v[n - 1] > 0)) {
        return 1 + sasiaPozitivCift(v, n - 1);
    } else {
        return sasiaPozitivCift(v, n - 1);
    }
}
