#include <stdio.h>

int main() {
    int n;
    int piket = 0;
    char portaFillestare = 'C';
    char portaAktuale;

    printf("Vendosni numrin e hedhjeve te njepasnjeshme te topit: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Vendosni porten ku hidhet topi %d (A/B/C/D): ", i + 1);
        scanf(" %c", &portaAktuale);

        if (portaAktuale == 'D') {
            piket++;
            printf("Ju fituat nje pike!\n");
        }
        else if (portaAktuale == 'C') {
            printf("Ju nuk fituat pike!\n");
        }


        if (portaAktuale == 'A' || portaAktuale == 'B') {
            printf("Celesat x1 dhe x3 ndryshojne kah/gjendje \n");
        } else if (portaAktuale == 'C' && (portaFillestare == 'A' || portaFillestare == 'B')) {
            printf("Celesi x2 ndryshon kah/gjendje \n");
        }

        portaFillestare = portaAktuale;
    }


    printf("Totali i pikeve te fituara: %d\n", piket);

    return 0;
}
