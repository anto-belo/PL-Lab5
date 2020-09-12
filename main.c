#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER 100
#define FILE_NAME "D:\\User\\OneDrive\\Documents\\PL\\PL-Lab5\\data.txt"

int countLineMembers(char membersLine[]);

int isFileEmpty(FILE *f);

void convertToNumbers(long int members[], char numberLine[]);

void sort(long int members[], int size);

void file(FILE *f, long int members[], int size);

int main() {
    FILE *f = fopen(FILE_NAME, "r+");
    if(isFileEmpty(f)) {
        puts("Error, file is empty");
        return 0;
    }

    char numberLine[BUFFER];
    fgets(numberLine, BUFFER, f);

    int size = countLineMembers(numberLine);
    long int members[size];
    convertToNumbers(members, numberLine);

    sort(members, size);
    file(f, members, size);

    fclose(f);
    return 0;
}

int countLineMembers(char membersLine[]) {
    int count = 1;
    for (int i = 0; i < strlen(membersLine); i++)
        if (membersLine[i] == ' ') count++;
    return count;
}

int isFileEmpty(FILE *f) {
    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    rewind(f);
    return (pos <= 0);
}

void convertToNumbers(long int members[], char numberLine[]) {
    int members_off = 0;
    char *end;
    for (int i = 0; i < countLineMembers(numberLine); i++)
        if (i == 0) members[members_off++] = strtol(numberLine, &end, 10);
        else members[members_off++] = strtol(end, &end, 10);
}

void sort(long int members[], int size) {
    for (int j = 1; j < size; j++) {
        int k = j, value = members[j];
        while (k > 0 && value < members[k - 1]) {
            members[k] = members[k - 1];
            k--;
        }
        members[k] = value;
    }
}

void file(FILE *f, long int members[], int size) {
    rewind(f);
    char result[10];
    for (int i = 0; i < size; i++) {
        lltoa(members[i], result, 10);
        fputs(result, f);
        fputc(' ', f);
    }
}