#include <stdio.h>

#define forceinline __inline__ __attribute__((always_inline))
forceinline int min(int a, int b, int c)
{
    int m = a;
    if (m > b) m = b;
    if (m > c) m = c;
    return m;
}

int main(int argc, char* argv[])
{
    FILE* file;
    int x, y, z;
    int s1, s2, s3;
    int total, total_ribbon;

    if (argc < 2)
    {
        fprintf(stdout, "Usage: %s <file>\n", argv[0]);
        return 0;
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Opening File: %s\n", argv[1]);
        return 1;
    }

    total = 0;
    total_ribbon = 0;
    while (fscanf(file, "%dx%dx%d\n", &x, &y, &z) != EOF)
    {
        s1 = x * y;
        s2 = y * z;
        s3 = z * x;

        total += (2 * s1);
        total += (2 * s2);
        total += (2 * s3);

        total += min(s1, s2, s3);

        s1 = 2 * (x + y);
        s2 = 2 * (y + z);
        s3 = 2 * (z + x);

        total_ribbon += min(s1, s2, s3);
        total_ribbon += x * y * z;
    }

    fprintf(stdout, "They should order %d square feet of paper\n", total);
    fprintf(stdout, "They should order %d feet of ribbon\n", total_ribbon);

    fclose(file);
    return 0;
}
