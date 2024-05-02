#include <stdio.h>

int main() {
    int piket;
    printf("Shkruani piket e grumbulluara: ");
    scanf("%d", &piket);
    int shifra = piket % 10;
    switch (piket / 10) {
        case 10:
        case 9:
            printf("Nota: A\n");
            break;
        case 8:
            printf("Nota: B\n");
            break;
        case 7:
            printf("Nota: C\n");
            break;
        case 6:
            printf("Nota: D\n");
            break;
        default:
            printf("Nota: F\n");
            break;
    }

    return 0;
}
