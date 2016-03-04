/**
 * This program prints "Hello, World!" and acts as a filter extracting meta-information lines from VCF file.
 * It is safe to run on any other text file, though result will probably be less impressing.
 *
 * (c) Seven Bridge Genomics, 2016
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
    static char buf[4096];

    FILE * f_input;
    FILE * f_output;
    unsigned long long count;
    int is_new_line;

    printf("Hello, World!\n");

    if (argc != 3) {
        printf("\nIf you would specify input and output file, this program "
                       "would filter for all lines starting with ##,\n"
                       "Usage:\n\t$ helloc <input_file> <output_file>\n");
        return 0;
    }

    printf("\nFiltering meta-information...\n\t%s ==> %s\n", argv[1], argv[2]);

    f_input = fopen(argv[1], "r");
    if (f_input == NULL)
    {
        printf("\nOops! Failed to open file %s for reading. Bye!\n", argv[1]);
        return 1;
    }

    f_output = fopen(argv[2], "w");
    if (f_output == NULL)
    {
        printf("\nOops! Failed to open file %s for writing. Bye!\n", argv[2]);
        return 2;
    }

    count = 0;
    is_new_line = 1;

    while (1) {
        char * p = fgets(buf, 4096, f_input);
        size_t n;
        if ((p == NULL) || ((n = strlen(buf)) == 0)) break;

        if (is_new_line && (buf[0] == '#') && (buf[1] == '#')) {
            fputs(buf, f_output);
            count++;
        }

        is_new_line = (buf[n - 1] == '\n');
    }

    fclose(f_input);
    fclose(f_output);

    printf("\nFound %llu lines starting with '##', filtered it all to output file.\n"
                   "\nChiao!\n", count);
    return 0;
}
