/* from https://www.hackerrank.com/x/library/hackerrank/all/questions/127486/view */
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * For count elements in an array, set to 1 if power of 2, 0 otherwise.
 * The input arr and output result arrays can be the same to be modified in place or a new array of size count.
 */
int isPower(int count, int *arr, int *result)
{
    for (int i = 0; i < count; ++i) {
        if (arr[i] == 0)
            result[i] = 0;
        // n is a power of 2 if only one bit is set.
        // n & (n-1) checks if the msb is set in n but not (n-1).
        else if ((arr[i] & (arr[i] - 1)) == 0)
            result[i] = 1;
        else
            result[i] = 0;
    }

    return count;
}

/*
 * From stdin:
 * count of elements
 * each element separated by a newline
 *
 * Input:
 * 4
 * 0
 * 1
 * 2
 * 3
 *
 * Output:
 * 0
 * 0
 * 1
 * 1
 * 0
 */
int main()
{
    FILE *fptr;
    if (getenv("OUTPUT_PATH") != NULL)
        fptr = fopen(getenv("OUTPUT_PATH"), "w");
    else
        fptr = tmpfile();

    int count = parse_int(ltrim(rtrim(readline())));

    int* arr = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        int arr_item = parse_int(ltrim(rtrim(readline())));

        *(arr + i) = arr_item;
    }

    int *result = arr; // overwrite input
    int result_count = isPower(count, arr, arr);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));
        printf("%d\n", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    free(arr);

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
