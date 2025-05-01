#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <scrambled.yoda> <output.jpg>\n", argv[0]);
        return 1;
    }

    const unsigned char key[] = "Yoda";
    const size_t key_len = strlen((const char *)key);

    FILE *in = fopen(argv[1], "rb");
    if (!in) { perror("fopen input"); return 1; }

    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    rewind(in);

    unsigned char *data = malloc(size);
    if (!data) { perror("malloc"); fclose(in); return 1; }

    fread(data, 1, size, in);
    fclose(in);

    // Step 1: Undo adjacent byte swaps [y x] -> [x y]
    for (long i = 0; i + 1 < size; i += 2) {
        swap(&data[i], &data[i+1]);
    }

    // Step 2: Undo 4-byte block reordering [C D A B] -> [A B C D]
    for (long i = 0; i + 3 < size; i += 4) {
        swap(&data[i+0], &data[i+2]);
        swap(&data[i+1], &data[i+3]);
    }

    // Step 3: XOR again with "Yoda"
    for (long i = 0; i < size; i++) {
        data[i] ^= key[i % key_len];
    }

    FILE *out = fopen(argv[2], "wb");
    if (!out) { perror("fopen output"); free(data); return 1; }

    fwrite(data, 1, size, out);
    fclose(out);
    free(data);

    printf("[+] Decrypted image written to: %s using XOR key \"Yoda\"\n", argv[2]);
    return 0;
}

