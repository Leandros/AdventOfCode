#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* file;
    int c, floor, counter;

    if (argc < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 0;
    }

    // start on 0th floor.
    floor = 0;
    counter = 0;

    file = fopen(argv[1], "r");
    while ((c = getc(file)) != EOF)
    {
        counter++;
        if (((unsigned char) c) == '(')
            floor++;
        else if (((unsigned char) c) == ')')
            floor--;

        if (floor == -1)
        {
            printf("Santa reaches the basement at position: %d\n", counter);
        }
    }

    printf("He ends up on floor: %d\n", floor);
    fclose(file);
    return 0;
}
