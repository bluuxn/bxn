#include "io.h"

#include <stdio.h>
#include <stdlib.h>

char *IOReadFileString(const char *file_path) {
    FILE *fp;
    long size;
    char *buffer;

    fp = fopen(file_path, "rb");
    if (fp == NULL) {
        printf("[!IO] Failed to open file %s!\n", file_path);
        return NULL;
    }
    printf("[IO] Opening file %s!\n", file_path);

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    printf("[IO] Length of %s is %ld bytes\n", file_path, size);
    rewind(fp);

    buffer = malloc(size+1);
    fread(buffer, sizeof(char), size, fp);
    buffer[size] = '\0';
    printf("[IO] Read file %s!\n", file_path);

    fclose(fp);

    return buffer;
}
