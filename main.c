#include <stdio.h>
#include <mem.h>


void hexdump_with_chars(FILE *file);

int hexdump(FILE *file)
{
    int buf;
    unsigned int count = 0;
    while ((buf = getc(file)) != EOF) {
        if (count % 0x10 == 0) {
            printf("\n%08x  ", count);
        }
        printf("%02x ", buf);
        count++;
    }
}

int main(int argc, char const **argv)
{
    if (strcmp(argv[1], "-c") == 0) {
        FILE *f = fopen(argv[2], "rb");
        hexdump_with_chars(f);
    } else {
        FILE *f = fopen(argv[1], "rb");
        hexdump(f);
    }
    return 0;
}

void hexdump_with_chars(FILE *file)
{
    int buf;
    char line[0x10];
    int index = 0;
    unsigned int count = 0;

    while ((buf = getc(file)) != EOF) {
        if (count % 0x10 == 0) {
            if (count > 0) {
                printf("\n          ");
                for (int i = 0; i < 0x10; i++) {
                    if (line[i] < ' ' || line[i] > 255) {
                        printf(" . ");
                    } else {
                        printf(" %c ", line[i]);
                    }
                }
                index = 0;
            }
            printf("\n%08x  ", count);
        }
        printf("%02x ", buf);
        line[index++] = (char) buf;
        count++;
    }
}
