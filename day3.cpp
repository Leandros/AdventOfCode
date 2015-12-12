#include <stdio.h>
#include <string.h>
#include <map>
#include <tuple>

struct Position
{
    int x;
    int y;
};

bool operator<(Position const& lhs, Position const& rhs)
{
    return (lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y));
}

int main(int argc, char* argv[])
{
    FILE* file;
    struct Position pos;
    struct Position robo_pos;
    std::map<Position, int> visited_positions;
    int c = 0, i = 0, with_robo = 0;
    char* filename = NULL;

    if (argc < 2)
    {
        fprintf(stdout, "Usage: [--second] %s <file>\n", argv[0]);
        return 0;
    }

    filename = argv[1];
    if (strncmp(argv[1], "--second", 8) == 0)
    {
        with_robo = 1;
        filename = argv[2];
    }

    file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Opening File: %s\n", argv[1]);
        return 1;
    }

    pos.x = 0;
    pos.y = 0;
    robo_pos.x = 0;
    robo_pos.y = 0;
    visited_positions[pos] = 1;
    while ((c = fgetc(file)) != EOF)
    {

        if ((i % 2) == 0)
        {
            if (c == '^') pos.y -= 1;
            else if (c == 'v') pos.y += 1;
            else if (c == '>') pos.x += 1;
            else if (c == '<') pos.x -= 1;
            visited_positions[pos] = 1;
        }
        else
        {
            if (with_robo)
            {
                if (c == '^') robo_pos.y -= 1;
                else if (c == 'v') robo_pos.y += 1;
                else if (c == '>') robo_pos.x += 1;
                else if (c == '<') robo_pos.x -= 1;
                visited_positions[robo_pos] = 1;
            }
            else
            {
                if (c == '^') pos.y -= 1;
                else if (c == 'v') pos.y += 1;
                else if (c == '>') pos.x += 1;
                else if (c == '<') pos.x -= 1;
                visited_positions[pos] = 1;
            }
        }

        i++;
    }

    fprintf(stdout, "Santa visited %lu houses.\n", visited_positions.size());

    return 0;
}
