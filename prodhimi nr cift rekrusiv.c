#include <stdio.h>

int prodhimiCift(int limit) {
    if (limit < 2) {
        return 1;
    }

    if (limit % 2 == 0) {
        return limit * prodhimiCift(limit - 2);
    }

    else {
        return prodhimiCift(limit - 1);
    }
}

int main() {
    int limit;
    printf("Vendos limitin (numer cift): ");
    scanf("%d", &limit);

    if (limit % 2 != 0) {
        printf("Vendos nje numer cift.\n");
        return 1;
    }

    int rezultat = prodhimiCift(limit);
    printf("Prodhimi i numrave cift deri ne %d: %d\n", limit, rezultat);

    return 0;
}
