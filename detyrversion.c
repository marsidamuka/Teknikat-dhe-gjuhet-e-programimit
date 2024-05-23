#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STUDENT_MAX 6

struct data {
    int dita;
    int muaji;
    int viti;
};

struct Studenti {
    char ID[20];
    char emri[30];
    char mbiemri[30];
    struct data ditelindje;
};

struct instruktor {
    char ID[20];
    char emri[30];
    char mbiemri[30];
    struct data ditelindje;
    char kategoria;
};

struct kursi {
    int id;
    char kategoria[30];
    char instruktor[30];
    char dataeNisjes[11];
    char ditet_e_kursit[30];
    char orari[20];
    int numStudents;
};

void ruajStudent(struct Studenti s1);
void ruajInstruktor(struct instruktor i1);
void ruajKursin(struct kursi *k1);
void regjistrimStudenti();
void regjistroInstruktor();
void krijoNjeKurs(int idKursi, const char *kategoria, const char *instruktor, const char *dataeNisjes, const char *ditet_e_kursit, const char *orari );
void regjistroStudentNeKurs(char idstudent[], int idKursi);
void fshiInstruktor(char idInstruktor[]);
void fshiKursin(int idKursit);
void crregjistrimStudenti(char studentId[], int courseId);
void listoKurset();
void listoStudent();
void listoInstruktor();
void menu();

void ruajStudent(struct Studenti s1) {
    FILE *f;
    f = fopen("student.txt", "a");
    if (f == NULL) {
        printf("Gabim ne hapjen e file-s student.txt.\n");
        return;
    }
    fwrite(&s1, sizeof(struct Studenti), 1, f);
    fclose(f);
}

void ruajInstruktor(struct instruktor i1) {
    FILE *fi;
    fi = fopen("instruktor.txt", "a");
    if (fi == NULL) {
        printf("Gabim ne hapjen e file-s instruktor.txt.\n");
        return;
    }
    fwrite(&i1, sizeof(struct instruktor), 1, fi);
    fclose(fi);
}

void ruajKursin(struct kursi *k1) {
    FILE *fk = fopen("kurs.txt", "a");
    if (fk == NULL) {
        printf("Gabim ne hapjen e file-s kurs.txt.\n");
        return;
    }
    fwrite(k1, sizeof(struct kursi), 1, fk);
    fclose(fk);
}

void regjistrimStudenti(){
    struct Studenti s1;
    printf("Vendos ID e studentit: ");
    scanf("%s", s1.ID);
    printf("Vendos emrin e studentit: ");
    scanf("%s", s1.emri);
    printf("Vendos mbiemrin e studentit: ");
    scanf("%s", s1.mbiemri);
    printf("Vendos ditelindjen e studentit (dita muaji viti): ");
    scanf("%d %d %d", &s1.ditelindje.dita, &s1.ditelindje.muaji, &s1.ditelindje.viti);


    int mosha = 2024 - s1.ditelindje.viti;
    if (mosha < 5 || mosha > 14) {
        printf("Ky student nuk mund te regjistrohet pasi nuk ka moshen e lejuar per kurset!\n");
        return;}
    else{
        printf("Ky student u regjistrua me sukses!");
    }

    ruajStudent(s1);
}

void regjistroInstruktor() {
    struct instruktor i1;
    printf("Vendos ID e instruktorit: ");
    scanf("%s", i1.ID);
    printf("Vendos emrin e instruktorit: ");
    scanf("%s", i1.emri);
    printf("Vendos mbiemrin e instruktorit: ");
    scanf("%s", i1.mbiemri);
    printf("Vendos ditelindjen e instruktorit (dita muaji viti): ");
    scanf("%d %d %d", &i1.ditelindje.dita, &i1.ditelindje.muaji, &i1.ditelindje.viti);
    printf("Vendos kategorine e kursit (Robotike, Programim, Graphic Design): ");
    scanf("%s", i1.kategoria);

    if (strcmp(i1.kategoria, "Robotike") != 0 && strcmp(i1.kategoria, "Programim") != 0 && strcmp(i1.kategoria, "Graphic Design") != 0) {
        printf("Kategoria e kursit nuk eshte e vlefshme. Ju lutem zgjidhni Robotike, Programim, ose Graphic Design.\n");
        return;
    }

    int mosha = 2024 - i1.ditelindje.viti;
    if (mosha < 20 || mosha > 60) {
        printf("Ky instruktor nuk mund te rregjistrohet ne kurs pasi nuk permbush kriteret e caktuara te moshes.\n");
        return;
    }
    ruajInstruktor(i1);
    printf("Instruktori u shtua me sukses!\n");
}

void krijoNjeKurs(int idKursi, const char *kategoria, const char *instruktor, const char *dataeNisjes, const char *ditet_e_kursit, const char *orari ){
    struct kursi k1;
    k1.id=idKursi;
    strcpy(k1.kategoria, kategoria);
    strcpy(k1.instruktor, instruktor);
    strcpy(k1.dataeNisjes, dataeNisjes);
    strcpy(k1.ditet_e_kursit, ditet_e_kursit);
    strcpy(k1.orari, orari);
    k1.numStudents = 0;

    ruajKursin(&k1);
    printf("Kursi u krijua me sukses!\n");
}

void regjistroStudentNeKurs(char idstudent[], int idKursi) {
    FILE *fs = fopen("student.txt", "r");
    if (fs == NULL) {
        printf("Gabim ne hapjen e file-s student.txt.\n");
        return;
    }

    struct Studenti s1;
    int studentEkziston = 0;
    while (fread(&s1, sizeof(struct Studenti), 1, fs)) {
        if (strcmp(s1.ID, idstudent) == 0) {
            studentEkziston = 1;
            break;
        }
    }
    fclose(fs);

    if (!studentEkziston){
        printf("Studenti nuk ekziston.\n");
        return;
    }

    FILE *fk = fopen("kurs.txt", "r+");
    if (fk == NULL) {
        printf("Gabim ne hapjen e file-s kurs.dat.\n");
        return;
    }

    struct kursi k1;
    int kursiEkziston = 0;
    while (fread(&k1, sizeof(struct kursi), 1, fk)) {
        if (k1.id == idKursi) {
            kursiEkziston = 1;
            if (k1.numStudents >= STUDENT_MAX) {
                printf("Ky grup ka mbushur numrin e lejuar te studenteve, zgjidh nje kurs tjeter!\n");
                fclose(fk);
                return;
            }

            k1.numStudents++;
            fseek(fk, -(long int)sizeof(struct kursi), SEEK_CUR);
            fwrite(&k1, sizeof(struct kursi), 1, fk);
            break;
        }
    }

    fclose(fk);

    if (!kursiEkziston){
        printf("Kursi nuk u gjet ne sistem.\n");
        return;
    }

    FILE *studentNeKurs = fopen("student_kurs.txt", "a");
    if (studentNeKurs == NULL) {
        printf("Gabim ne hapjen e file-s per te shkruar.\n");
        return;
    }
    fwrite(idstudent, sizeof(char), strlen(idstudent), studentNeKurs);
    fwrite(&idKursi, sizeof(int), 1, studentNeKurs);
    fclose(studentNeKurs);

    printf("Studenti u regjistrua me sukses ne kete kurs.\n");
}

void fshiInstruktor(char idInstruktor[]) {
    struct instruktor i1;
    FILE *fi = fopen("instruktor.txt", "r");
    if (fi == NULL) {
        printf("Gabim ne hapjen e file-s instruktor.txt.\n");
        return;
    }

    FILE *temp = fopen("temp_instruktor.txt", "w");
    if (temp == NULL) {
        printf("Gabim ne krijimin e nje file te perkohshem.\n");
        fclose(fi);
        return;
    }

    int gjendet = 0;
    while (fread(&i1, sizeof(struct instruktor), 1, fi)) {
        if (strcmp(i1.ID, idInstruktor) == 0) {
            gjendet = 1;
            if (strlen(i1.kategoria) > 0) {
                printf("Instruktori po jep mesim ne te pakten nje kurs dhe nuk mund te fshihet.\n");
            } else {
                printf("Instruktori u fshi nga sistemi.\n");
            }
        } else {
            fwrite(&i1, sizeof(struct instruktor), 1, temp);
        }
    }

    fclose(fi);
    fclose(temp);

    if (gjendet) {
        remove("instruktor.txt");
        rename("temp_instruktor.txt", "instruktor.txt");
    } else {
        remove("temp_instruktor.txt");
    }
}

void fshiKursin(int idKursit) {
    struct kursi k1;

    FILE *fk = fopen("kurs.txt", "r");
    if (fk == NULL) {
        printf("Gabim ne hapjen e file-s kurs.txt.\n");
        return;
    }

    FILE *temp = fopen("temp_kurs.txt", "w");
    if (temp == NULL) {
        printf("Gabim ne krijimin e nje file te perkohshem.\n");
        fclose(fk);
        return;
    }

    int gjendet = 0;
    while (fread(&k1, sizeof(struct kursi), 1, fk)) {
        if (k1.id == idKursit) {
            gjendet = 1;
            if (k1.numStudents > 0) {
                printf("Kursi ka studente te regjistruar dhe prandaj nuk mund te fshihet.\n");
            } else {
                printf("Kursi u fshi me sukses.\n");
            }
        } else {
            fwrite(&k1, sizeof(struct kursi), 1, temp);
        }
    }

    fclose(fk);
    fclose(temp);

    if (gjendet) {
        remove("kurs.txt");
        rename("temp_kurs.txt", "kurs.txt");
    } else {
        remove("temp_kurs.txt");
    }
}

void crregjistrimStudenti(char studentId[], int courseId) {
    struct kursi k1;
    FILE *fk = fopen("kurs.txt", "r+");
    if (fk == NULL) {
        printf("Gabim ne hapjen e file-s kurs.txt.\n");
        return;
    }

    int kursiEkziston = 0;
    while (fread(&k1, sizeof(struct kursi), 1, fk)) {
        if (k1.id == courseId) {
            kursiEkziston = 1;
            if (k1.numStudents == 0) {
                printf("Nuk ka asnje student te regjistruar ne kete kurs.\n");
                fclose(fk);
                return;
            }

            k1.numStudents--;
            fseek(fk, -(long int)sizeof(struct kursi), SEEK_CUR);
            fwrite(&k1, sizeof(struct kursi), 1, fk);
            break;
        }
    }
    fclose(fk);

    if (!kursiEkziston) {
        printf("Kursi nuk u gjet ne sistem.\n");
        return;
    }

    FILE *studentNeKurs = fopen("student_kurs.txt", "r");
    if (studentNeKurs == NULL) {
        printf("Gabim ne hapjen e file-s student_kurs.txt.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Gabim ne hapjen e file-s temp.txt.\n");
        fclose(studentNeKurs);
        return;
    }

    char studId[20];
    int kursId;
    while (fscanf(studentNeKurs, "%s %d", studId, &kursId) != EOF) {
        if (strcmp(studId, studentId) != 0 || kursId != courseId) {
            fprintf(temp, "%s %d\n", studId, kursId);
        }
    }

    fclose(studentNeKurs);
    fclose(temp);

    remove("student_kurs.txt");
    rename("temp.txt", "student_kurs.txt");

    printf("Studenti u crregjistrua nga kursi me sukses.\n");
}

void listoKurset() {
    struct kursi k1;
    FILE *fk = fopen("kurs.txt", "r");
    if (fk == NULL) {
        printf("Gabim ne hapjen e file-s kurs.txt.\n");
        return;
    }

    printf("Lista e kurseve:\n");
    while (fread(&k1, sizeof(struct kursi), 1, fk)) {
        printf("ID: %d, Kategoria: %s, Instruktor: %s, Data e Nisjes: %s, Ditet e Kursit: %s, Orari: %s, Numri i Studenteve: %d\n",
                k1.id, k1.kategoria, k1.instruktor, k1.dataeNisjes, k1.ditet_e_kursit, k1.orari, k1.numStudents);
    }
    fclose(fk);
}

void listoStudent() {
    printf("Lista e te gjithe studenteve te regjistruar:\n");
    printf("----------------------------------------------\n");

    struct Studenti s1;
    FILE *fs = fopen("student.txt", "r");
    if (fs == NULL) {
        printf("Gabim ne hapjen e skedarit.\n");
        return;
    }

    while (fread(&s1, sizeof(struct Studenti), 1, fs)) {
        printf("ID e studentit: %s\n", s1.ID);
        printf("Emri: %s\n", s1.emri);
        printf("Mbiemri: %s\n", s1.mbiemri);
        printf("Ditelindja: %d/%d/%d\n", s1.ditelindje.dita, s1.ditelindje.muaji, s1.ditelindje.viti);
        printf("----------------------------------------------\n");
    }

    fclose(fs);
}

void listoInstruktor() {
    printf("Lista e te gjithe instruktoreve te regjistruar:\n");
    printf("----------------------------------------------\n");

    struct instruktor i1;
    FILE *fi = fopen("instruktor.txt", "r");
    if (fi == NULL) {
        printf("Gabim ne hapjen e file-s instruktor.dat.\n");
        return;
    }

    while (fread(&i1, sizeof(struct instruktor), 1, fi)) {
        printf("ID e instruktorit: %s\n", i1.ID);
        printf("Emri: %s\n", i1.emri);
        printf("Mbiemri: %s\n", i1.mbiemri);
        printf("Ditelindja: %d/%d/%d\n", i1.ditelindje.dita, i1.ditelindje.muaji, i1.ditelindje.viti);
        printf("Kategoria e kursit: %c\n", i1.kategoria);
        printf("----------------------------------------------\n");
    }

    fclose(fi);
}

void menu() {
    printf("\n ------------------------------------------\n");
    printf("\n ******************************************\n");
    printf("\n        QENDRA E KURSIT 'THE FUTURE'      ");
    printf("\n");
    printf("\n  Menuja kryesore:");
    printf("\n 1 - Rregjistro nje student te ri");
    printf("\n 2 - Rregjistro nje instruktor te ri");
    printf("\n 3 - Krijo nje kurs te ri");
    printf("\n 4 - Rregjistro nje student ne nje kurs ");
    printf("\n 5 - Crregjistro nje student ");
    printf("\n 6 - Fshi nje instruktor ");
    printf("\n 7 - Fshi nje kurs ");
    printf("\n 8 - Listo te gjitha kurset e krijuara");
    printf("\n 9 - Listo te gjithe studentet");
    printf("\n 10 - Listo te gjithe instruktoret");
    printf("\n 11 - Listo studentet ne nje kurs te caktuar");
    printf("\n 12 - Informacione mbi instruktorin ");
    printf("\n Mbyll-mbyll programin");
    printf("\n ");
    printf("\n -->Veprimi qe dua te kryej: ");
}

int main() {
    char m;
    do {
        menu();
        scanf(" %c", &m);

        switch (m) {
            case '1':
                regjistrimStudenti();
                break;
            case '2':
                regjistroInstruktor();
                break;
            case '3': {
                int idKursi;
                char kategoria[30], instruktor[30], dataeNisjes[11], ditet_e_kursit[30], orari[20];
                printf("Vendos ID e kursit: ");
                scanf("%d", &idKursi);
                printf("Vendos kategorine e kursit: ");
                scanf("%s", kategoria);
                printf("Vendos emrin e instruktorit: ");
                scanf("%s", instruktor);
                printf("Vendos daten e nisjes se kursit : ");
                scanf("%s", dataeNisjes);
                printf("Vendos ditet e kursit: ");
                scanf("%s", ditet_e_kursit);
                printf("Vendos orarin e kursit: ");
                scanf("%s", orari);
                krijoNjeKurs(idKursi, kategoria, instruktor, dataeNisjes, ditet_e_kursit, orari);
                break;
            }
            case '4': {
                char idstudent[20];
                int idKursi;
                printf("Vendos ID e studentit: ");
                scanf("%s", idstudent);
                printf("Vendos ID e kursit: ");
                scanf("%d", &idKursi);
                regjistroStudentNeKurs(idstudent, idKursi);
                break;
            }
            case '5': {
                char idstudent[20];
                printf("Vendos ID e studentit: ");
                scanf("%s", idstudent);
                int idKursi;
                printf("Vendos ID e kursit: ");
                scanf("%d", &idKursi);
                crregjistrimStudenti(idstudent, idKursi);
                break;
            }
            case '6': {
                char idInstruktor[20];
                printf("Vendos ID e instruktorit: ");
                scanf("%s", idInstruktor);
                fshiInstruktor(idInstruktor);
                break;
            }
            case '7': {
                int idKursi;
                printf("Vendos ID e kursit: ");
                scanf("%d", &idKursi);
                fshiKursin(idKursi);
                break;
            }
            case '8':
                listoKurset();
                break;
            case '9':
                listoStudent();
                break;
            case '10':
                listoInstruktor();
                break;
            default:
                printf("Veprimi i zgjedhur nuk ekziston!\n");
        }
    } while (m != 'M' && m != 'm');

    return 0;
}
