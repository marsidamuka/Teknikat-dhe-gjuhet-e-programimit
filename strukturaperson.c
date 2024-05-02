#include <stdio.h>
#include <string.h>
#define MAX_PERSONA 3
#define MAX_GJATESI_MBIEMRI 30

struct person {
    char emri[20];
    char mbiemri[20];
    int mosha;
} person[MAX_PERSONA];
struct person personMeMbiemrinMeGjate(struct person p[], int numriPersonave) {
    struct person personMeGjatesinMeTeGjate = p[0];
    for (int i = 1; i < numriPersonave; i++) {
        if (strlen(p[i].mbiemri) > strlen(personMeGjatesinMeTeGjate.mbiemri)) {
            personMeGjatesinMeTeGjate = p[i];
        }
    }
    return personMeGjatesinMeTeGjate;
}

int personi_vjeter(struct person p[]) {
    int max = p[0].mosha;
    for (int i = 1; i < MAX_PERSONA; i++) {
        if (p[i].mosha > max) {
            max = p[i].mosha;
        }
    }
    return max;
}
int personaMeShkronj(struct person p[], int numriPersonave, char shkronja) {
    int count = 0;
    for (int i = 0; i < numriPersonave; i++) {
        if (p[i].emri[0] == shkronja) {
            count++;
        }
    }
    return count;
}

void emriPerpara(struct person p[]) {
    for (int i = 0; i < MAX_PERSONA - 1; i++) {
        int rezultati = strcmp(p[i].emri, p[i + 1].emri);
        if (rezultati > 0) {
            printf("\nEmri %s eshte mbrapa emrit %s", p[i].emri, p[i + 1].emri);
        } else if (rezultati == 0) {
            printf("\nEmrat %s dhe %s jane njesoj", p[i].emri, p[i + 1].emri);
        } else {
            printf("\nEmri %s eshte me perpara se emri %s", p[i].emri, p[i + 1].emri);
        }
    }
}

void rendit(struct person p[]) {
    for (int i = 0; i < MAX_PERSONA - 1; i++) {
        for (int j = i + 1; j < MAX_PERSONA; j++) {
            int emriComparison = strcmp(p[i].emri, p[j].emri);
            if (emriComparison > 0 || (emriComparison == 0 && strcmp(p[i].mbiemri, p[j].mbiemri) > 0)) {
                struct person temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

struct person printoDhena(struct person person) {
    printf("\nEmri: %s", person.emri);
    printf("\nMbiemri: %s", person.mbiemri);
    printf("\nMosha: %d", person.mosha);
    return person;
}

int main() {
    for (int i = 0; i < MAX_PERSONA; i++) {
        printf("Jep emrin e personit: ");
        scanf("%s", person[i].emri);
        printf("Jep mbiemrin e personit: ");
        scanf("%s", person[i].mbiemri);
        printf("Jep moshen e personit: ");
        scanf("%d", &person[i].mosha);
    }

    printf("\nMosha me e madhe: %d", personi_vjeter(person));
    emriPerpara(person);
    rendit(person);
    printf("\nPersonat e renditur:");

    for (int i = 0; i < MAX_PERSONA; i++) {
        printoDhena(person[i]);
    }
    char shkronja;
    printf("\nJepni shkronjen per te numeruar personat me emer qe fillon me ate: ");
    scanf(" %c", &shkronja);
    int numriPersonave = MAX_PERSONA;
    int count = personaMeShkronj(person, numriPersonave, shkronja);
    printf("Numri i personave qe fillon emri me shkronjen '%c' eshte: %d\n", shkronja, count);
    struct person personMeMbiemrinGjate = personMeMbiemrinMeGjate(person, MAX_PERSONA);
    printf("Personi me mbiemrin me te gjate eshte: %s %s\n", personMeMbiemrinGjate.emri, personMeMbiemrinGjate.mbiemri);

    return 0;
}
