#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define PART1 0
#define PART2 1

static char lights[1000][1000];

#define REGEXSTRING "([0-9]+),([0-9]+)[^0-9]*([0-9]+),([0-9]+)"
#define REGEXGROUPS 5
int get_coords(char const* buffer, long* x1, long* x2, long* y1, long* y2)
{
    int ret;
    regex_t regex;
    regmatch_t matches[REGEXGROUPS];

    ret = regcomp(&regex, REGEXSTRING, REG_EXTENDED);
    if (ret) return 1;

    ret = regexec(&regex, buffer, REGEXGROUPS, matches, 0);
    if (!ret)
    {
        char buf[8];
        snprintf(buf, 8, "%.*s", matches[1].rm_eo - matches[1].rm_so, buffer + matches[1].rm_so);
        *x1 = strtol(buf, NULL, 10);
        snprintf(buf, 8, "%.*s", matches[2].rm_eo - matches[2].rm_so, buffer + matches[2].rm_so);
        *y1 = strtol(buf, NULL, 10);
        snprintf(buf, 8, "%.*s", matches[3].rm_eo - matches[3].rm_so, buffer + matches[3].rm_so);
        *x2 = strtol(buf, NULL, 10);
        snprintf(buf, 8, "%.*s", matches[4].rm_eo - matches[4].rm_so, buffer + matches[4].rm_so);
        *y2 = strtol(buf, NULL, 10);

        return 0;
    }

    return 1;
}

int operate(char* buffer, long len)
{
    int i, j, ret;
    long x1, x2;
    long y1, y2;

    if (get_coords(buffer, &x1, &x2, &y1, &y2)) return 1;

    if (strncmp(buffer, "toggle", 6) == 0)
    {
        for (i = x1; i <= x2; i++)
        {
            for (j = y1; j <= y2; j++)
            {
#if PART1
                lights[i][j] = !lights[i][j];
#elif PART2
                lights[i][j] += 2;
#endif
            }
        }
    }
    else if (strncmp(buffer, "turn on", 7) == 0)
    {
        for (i = x1; i <= x2; i++)
        {
            for (j = y1; j <= y2; j++)
            {
#if PART1
                lights[i][j] = 1;
#elif PART2
                lights[i][j] += 1;
#endif
            }
        }
    }
    else if (strncmp(buffer, "turn off", 8) == 0)
    {
        for (i = x1; i <= x2; i++)
        {
            for (j = y1; j <= y2; j++)
            {
#if PART1
                lights[i][j] = 0;
#elif PART2
                if (lights[i][j] > 0)
                    lights[i][j] -= 1;
#endif
            }
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    FILE* file;
    long i, j, count;
    char* buffer;

    if (argc < 2)
    {
        fprintf(stdout, "Usage: %s <input>\n", argv[0]);
        return 0;
    }

    file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    count = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = malloc(count);
    fread(buffer, 1, count, file);

    for (i = 0, j = 0; i < count; i++)
    {
        if (buffer[i] == '\n')
        {
            if (operate(buffer + j, i - j))
                exit(1);
            j = i + 1;
        }
    }

    count = 0;
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++)
        {
#if PART1
            if (lights[i][j] > 0)
                count++;
#elif PART2
            count += lights[i][j];
#endif
        }
    }

#if PART1
    printf("%d lights are on!\n", count);
#elif PART2
    printf("The total brightness is %d!\n", count);
#endif

    free(buffer);
}
