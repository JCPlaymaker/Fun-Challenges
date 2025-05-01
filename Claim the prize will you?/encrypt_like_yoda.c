#include <stdio.h>
#include <stdlib.h>

// Swap two bytes
void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input.jpg> <output.yoda>\n", argv[0]);
        return 1;
    }

    // Open input file
    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("fopen input");
        return 1;
    }

    // Get file size
    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    rewind(in);

    // Read file into memory
    unsigned char *data = malloc(size);
    if (!data) {
        perror("malloc");
        fclose(in);
        return 1;
    }
    fread(data, 1, size, in);
    fclose(in);

    // Step 1: swap first two bytes with last two bytes in each 4-byte block
    for (long i = 0; i + 3 < size; i += 4) {
        swap(&data[i + 0], &data[i + 2]);
        swap(&data[i + 1], &data[i + 3]);
    }

    // Step 2: swap every adjacent pair
    for (long i = 0; i + 1 < size; i += 2) {
        swap(&data[i], &data[i + 1]);
    }

    // Write to output file
    FILE *out = fopen(argv[2], "wb");
    if (!out) {
        perror("fopen output");
        free(data);
        return 1;
    }
    fwrite(data, 1, size, out);
    fclose(out);
    free(data);

    printf("[+] Obfuscated file written to: %s\n", argv[2]);
    return 0;
}

