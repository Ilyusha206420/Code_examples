#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int is_consonant(char c) {
    return (c >= 'a' && c <= 'z' && !(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'));
}

int main() {
    char str[1000];
    char word[100];
    int i = 0, j = 0;
    int reading = 1;

    printf("please, enter string(max lenight is 999) : ");
    while (reading == 1) {
        str[i] = getchar();
        if (str[i] == '\n') {
            str[i] = '\0';
            i = 0;
            reading = 0;
        }
        i++;
    }

    printf("in this string werbs, ending on consoant: \n");

    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\n') {
            word[j++] = str[i];
        }
        else {
            if (is_consonant(word[j - 1])) {
                word[j] = '\0';
                printf(" %s \n", word);
            }
            j = 0;
        }
        i++;
    }

    if (is_consonant(word[j - 1])) {
        word[j] = '\0';
        printf(" %s \n", word);
    }

    return 0;
}