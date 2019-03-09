#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *generate_random(int nums, int min, int max, uint32_t seed) {
    srand(seed);
    int *p = (int *)malloc(sizeof(int) * 10);
    int flag = 0;

    if (nums > 10) {
        p = (int *)realloc(p, sizeof(int) * nums);
    }
    for (int i = 0; i < nums; i++) {
        if ((rand() % 10) < 1) {
            //p[i] = min + (max * 0.8) + (rand() % ((max * 0.2) - min));
            p[i] = 21 + (rand() % 80);
        } else {
            p[i] = 1 + (rand() % 20);
        }
    }

    return p;
}

int main(int argc, char **argv) {
    int i, min = 1, max = 255, nums = 100;
    uint32_t seed = time(NULL);
    char *output = "stdout";
    char *usage = "generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>][-s <seed>] [-o <output-file-name>]";
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-u") == 0) {
            printf("%s\n", usage);
            exit(3);
        } else if (argv[i][1] == 'm') {
            min = atoi(argv[i + 1]);
            i++;
        } else if (argv[i][1] == 'M') {
            i++;
            max = atoi(argv[i]);
        } else if (argv[i][1] == 'o') {
            i++;
            output = argv[i];
        } else if (argv[i][1] == 'n') {
            i++;
            nums = atoi(argv[i]);
        } else if (argv[i][1] == 's') {
            i++;
            seed = atoi(argv[i]);
        } else {
            printf("%s\n", usage);
            exit(3);
        }
    }
    int *ram = generate_random(nums, min, max, seed);
    FILE *outfile = fopen(output, "w");
    if (outfile == NULL) {
        printf("output file not open\n");
    }

    for (int s = 0; s < nums; s++) {
        if (s == nums - 1) {
            fprintf(outfile, "%d", ram[s]);
            break;
        }
        fprintf(outfile, "%d\n", ram[s]);
    }
    fclose(outfile);
    free(ram);
    ram = NULL;

    return 0;
}