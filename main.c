#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128 * 1024 // 128KB should be plenty for most text files

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("ERROR OPENING FILE");
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, BUFFER_SIZE, file);
    if (ferror(file)) {
        perror("ERROR READING FILE");
        free(buffer);
        fclose(file);
        return 1;
    }

    fclose(file);

    char *newBuffer = (char *)malloc(BUFFER_SIZE);
    if (newBuffer == NULL) {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        free(buffer);
        return 1;
    }

    size_t newBufferIndex = 0;
    int isLineEmpty = 1;

    for (size_t i = 0; i < bytesRead; i++) {
        if (buffer [i] == '\n') {
            if (isLineEmpty) {
                newBuffer[newBufferIndex++] = '\n';
            }
            isLineEmpty = 1; // Reset the flag for the next line
        } else {
            if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\r') {
            isLineEmpty = 0;
            }
            if (!isLineEmpty) {
                newBuffer[newBufferIndex++] = buffer[i];
            }
        }
    }

    if (bytesRead > 0 && buffer[bytesRead - 1] != '\n' && !isLineEmpty) {
        newBuffer[newBufferIndex++] = '\n';
    }

    file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("ERROR OPENING FILE FOR WRITING");
        free(buffer);
        free(newBuffer);
        return 1;
    }

    fwrite(newBuffer, 1, newBufferIndex, file);

    free(buffer);
    free(newBuffer);
    fclose(file);
    return 0;

}