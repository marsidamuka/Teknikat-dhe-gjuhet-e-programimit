#include <stdio.h>

#define GJAT_EMER 25
#define MAX_ARTIKULL 100

struct artikull {
    int numri;
    char emri[GJAT_EMER + 1];
    int gjendja;
} inventari[MAX_ARTIKULL];

int nr_artikull = 0;

int gjej_artikull(int numer);
void shto(void);
void kerko(void);
void update(void);
void printo(void);
int lexo_rresht(char str[], int n);
int artikull_zero(void);
void kodi_unik(void);

void print_menu() {
    printf("\n----------------------------------------\n");
    printf("      Menu:\n");
    printf("1. Shto artikull\n");
    printf("2. Kerko artikull\n");
    printf("3. Update artikull\n");
    printf("4. Printo te gjithe artikujt\n");
    printf("5. Kontrollo gjendjen 0 te artikujve\n");
    printf("6. Kerko artikuj me kod te vetem shifror \n");
    printf("0. Exit\n");
    printf("Zgjidh nje veprim (0-6): ");
}

int main() {
    int kodi;

    while (1) {
        print_menu();
        scanf("%d", &kodi);
        while (getchar() != '\n');

        switch (kodi) {
            case 1: shto(); break;
            case 2: kerko(); break;
            case 3: update(); break;
            case 4: printo(); break;
            case 5: printf("Gjendje 0 të gjetura: %d\n", artikull_zero()); break;
            case 6: kodi_unik(); break;
            case 0: return 0;
            default: printf("Kod i gabuar\n");
        }
    }
    return 0;
}

int gjej_artikull(int numri) {
    for (int i = 0; i < nr_artikull; i++) {
        if (inventari[i].numri == numri)
            return i;
    }
    return -1;
}

void shto(void) {
    int artikull_nr;
    if (nr_artikull == MAX_ARTIKULL) {
        printf("Databaza eshte plot; nuk mund te shtohet artikull.\n");
        return;
    }
    printf("Fut numrin e artikullit: ");
    scanf("%d", &artikull_nr);
    if (gjej_artikull(artikull_nr) >= 0) {
        printf("Artikulli egziston.\n");
        return;
    }

    inventari[nr_artikull].numri = artikull_nr;
    printf("Jep emrin e artikullit: ");
    lexo_rresht(inventari[nr_artikull].emri, GJAT_EMER);
    printf("Jep gjendjen e artikullit: ");
    scanf("%d", &inventari[nr_artikull].gjendja);
    nr_artikull++;
}

void kerko(void) {
    int numer;
    printf("Jep numrin e artikullit: ");
    scanf("%d", &numer);
    int i = gjej_artikull(numer);
    if (i >= 0) {
        printf("Emri i artikullit: %s\n", inventari[i].emri);
        printf("Gjendja e artikullit: %d\n", inventari[i].gjendja);
    } else {
        printf("Artikulli nuk u gjet.\n");
    }
}

void update(void) {
    int numer, ndryshimi;
    printf("Jep numrin e artikullit: ");
    scanf("%d", &numer);
    int i = gjej_artikull(numer);
    if (i >= 0) {
        printf("Jep ndryshimin ne gjendje te artikullit: ");
        scanf("%d", &ndryshimi);
        inventari[i].gjendja += ndryshimi;
    } else {
        printf("Artikulli nuk u gjet.\n");
    }
}

void printo(void) {
    printf("Numri i Artikullit Emri i Artikullit Gjendja e Artikullit\n");
    for (int i = 0; i < nr_artikull; i++) {
        printf("%7d %25s %25d\n", inventari[i].numri, inventari[i].emri, inventari[i].gjendja);
    }
}

int artikull_zero(void) {
    int count = 0;
    for (int i = 0; i < nr_artikull; i++) {
        if (inventari[i].gjendja == 0) {
            count++;
        }
    }
    return count;
}

void kodi_unik(void) {
    int found = 0;
    printf("Artikujt me kod të vetëm shifror:\n");
    for (int i = 0; i < nr_artikull; i++) {
        if (inventari[i].numri >= 1000 && inventari[i].numri <= 9999) {
            printf("%d\n", inventari[i].numri);
            found = 1;
        }
    }
    if (!found) {
        printf("Nuk ka artikuj me kod të vetëm shifror.\n");
    }
}

int lexo_rresht(char str[], int n) {
    int i = 0, ch;
    ch = getchar();
    while (ch == ' ') {
        ch = getchar();
    }
    while (ch != '\n' && i < n) {
        str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}
