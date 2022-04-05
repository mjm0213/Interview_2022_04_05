#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIST_LENGTH 1000000
#define MAX_WORD_LENGTH 50

double ComputeAverage(int list_length, double *list) {
    double sum = 0;
    for (int ii = 0; ii < list_length; ii++) {
        if (sum + list[ii] > DBL_MAX || sum + list[ii] < DBL_MIN) {
            printf("Error: Sum of numbers will exceed limits of a double.");
            exit(1);
        }
        sum += list[ii];
    }
    return sum/(double)list_length;
}

bool UsingCsv(char *arg) {
    int ii = 0;
    while (arg[ii] != '\0') {
        if (arg[ii] == '.') {
            if (arg[ii + 1] == 'c' && arg[ii + 2] == 's' && arg[ii + 3] == 'v') {
                return true;
            }
            break;
        }
        ii++;
    }
    return false;
}

void ParseCsvFile(char *path, double *list, int *list_length) {
    FILE *list_file = fopen(path, "r");
    if (list_file != NULL) {
        // string that will get turned into a double
        char list_item[MAX_WORD_LENGTH];
        int word_index = 0;
        int list_index = 0;
        char character = getc(list_file);
        while (character != EOF) {
            if (character != ',') {
                list_item[word_index++] = character;
                
                if (word_index >= MAX_WORD_LENGTH) {
                    printf("Error: a string in the csv file exceeded the max of %d\n", MAX_WORD_LENGTH);
                    exit(1);
                }
            } else {
                list[list_index++] = strtod(list_item, NULL);
                (*list_length)++;
                memset(list_item, 0, word_index);
                word_index = 0;
                
                if (list_index >= MAX_LIST_LENGTH) {
                    printf("Error: list size has exceeded the maximum of %d\n", MAX_LIST_LENGTH);
                    exit(1);
                }
            }
            character = getc(list_file);
        }
        fclose(list_file);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough arguments. Provide a list of doubles as arguments or in a .csv file\n");
        exit(1);
    }
    
    double list[MAX_LIST_LENGTH];
    int list_length = 0;
    if (UsingCsv(argv[1])) {
        ParseCsvFile(argv[1], list, &list_length);
    } else {
        for (int ii = 0; ii < argc - 1; ii++) {
            list[ii] = strtod(argv[ii + 1], NULL);
        }
        list_length = argc - 1;
    }
    
    if (list_length == 0) {
        printf("No items in list. Cannot compute an average.\n");
        exit(1);
    }
    
    double average = ComputeAverage(list_length, list);
    printf("Average: %lf\n", average);
    
    return 0;
}
