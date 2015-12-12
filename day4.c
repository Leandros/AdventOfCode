#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

#define MAX_STR_LEN 64
#define MAX_APPEND_NUM 0xFFFFFFFF

void bytes_to_str(char* out, char const* in, int len)
{
    int i;
    char const* hex = "0123456789abcdef";

    for (i = 0; i < len - 1; i++)
    {
        *out++ = hex[(*in >> 4) & 0xF];
        *out++ = hex[(*in++) & 0xF];
    }
    *out++ = hex[(*in >> 4) & 0xF];
    *out++ = hex[(*in) & 0xF];
    *out++ = 0;
}

int main(int argc, char* argv[])
{
    int i, test;
    unsigned long input_len;
    unsigned char input[MAX_STR_LEN];
    unsigned char output[MD5_DIGEST_LENGTH];
    unsigned char output_str[32];

    if (argc < 2)
    {
        fprintf(stdout, "Usage: %s <input>\n", argv[0]);
        return 0;
    }

    for (i = 0; i < MAX_APPEND_NUM; i++)
    {
        input_len = snprintf(input, MAX_STR_LEN, "%s%d", argv[1], i);
        if (input_len > MAX_STR_LEN)
        {
            fprintf(stdout, "Reached maximum length. Aborting.\n");
            return 1;
        }

        MD5(input, input_len, output);
        bytes_to_str(output_str, output, MD5_DIGEST_LENGTH);

        sscanf(output_str, "%6x", &test);
        if (test == 0)
        {
            fprintf(stdout, "The secret key is: %s\n", input);
            fprintf(stdout, "The MD5 hash is: %s\n", output_str);
            return 0;
        }
    }

    return 0;
}
