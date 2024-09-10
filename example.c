#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("ERROR OPENING FILE");
        return 1;
    }

    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        perror("ERROR CREATING TEMP FILE");
        fclose(file);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // Check if the line is not empty (contains more than just a newline character)
        if (strspn(buffer, " \t\r\n") != strlen(buffer)) {
            fputs(buffer, tempFile);
        }
    }

    fclose(file);

    // Reopen the original file for writing
    file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("ERROR OPENING FILE FOR WRITING");
        fclose(tempFile);
        return 1;
    }

    // Write the contents of the temporary file back to the original file
    rewind(tempFile);
    while (fgets(buffer, BUFFER_SIZE, tempFile)) {
        fputs(buffer, file);
    }

    fclose(file);
    fclose(tempFile);

    return 0;
}