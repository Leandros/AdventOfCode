#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 65536
#define LINE_SIZE 512

int readline(char const* buffer, char* out, size_t max_len)
{
    size_t i;
    for (i = 0; i < max_len; i++)
    {
        if (buffer[i] == '\n')
        {
            memcpy(out, buffer, i);
            out[i] = '\0';
            return i;
        }
    }

    return EOF;
}

int contains(char const* str, char c)
{
    int count;
    size_t i;
    size_t len = strlen(str);

    count = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == c)
        { count++; }
    }

    return count;
}

int contains_one(char const* str, char const* chars)
{
    int count;
    size_t i, j;
    size_t len = strlen(str);
    size_t charlen = strlen(chars);

    count = 0;
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < charlen; j++)
        {
            if (str[i] == chars[j])
            { count++; }
        }
    }

    return count;
}

int contains_all(char const* str, char const* chars)
{
    size_t i, j;
    size_t len = strlen(str);
    size_t charlen = strlen(chars);

    j = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == chars[j])
        {
            j++;
            if (j == charlen)
            { return 1; }
        }
        else
        {
            j = 0;
        }
    }

    return j == charlen;
}

int contains_two_letters_in_row(char const* str)
{
    size_t i, j;
    size_t len = strlen(str);

    for (i = 0; i < len; i++)
    {
        if ((i + 1) > len)
        { return 0; }

        if (str[i] == str[i + 1])
        { return 1; }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    FILE* file;
    size_t size_read;
    char buffer[BUFFER_SIZE];
    int chars_read;
    char line[LINE_SIZE];
    char* rbuf_tmp;

    int count = 0;

    if (argc < 2)
    {
        fprintf(stdout, "Usage: %s <file>\n", argv[0]);
        return 0;
    }

    file = fopen(argv[1], "rb");
    if (!file)
    {
        fprintf(stderr, "Error: Opening File: %s\n", argv[1]);
        return 1;
    }

loop:
    size_read = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    rbuf_tmp = buffer;
    while ((chars_read = readline(rbuf_tmp, line, LINE_SIZE)) != EOF)
    {
        if (contains_one(line, "aeiou") >= 3 && contains_two_letters_in_row(line) &&
                !contains_all(line, "ab") && !contains_all(line, "cd") &&
                !contains_all(line, "pq") && !contains_all(line, "xy"))
        {
            count++;
        }

        rbuf_tmp = rbuf_tmp + chars_read + 1;
    }

    if (size_read == BUFFER_SIZE) { goto loop; }

    fprintf(stdout, "Contains %d nice strings.\n", count);

    fclose(file);
    return 0;
}
