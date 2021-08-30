#include "arguments.hpp"

int main(int argc, char* argv[])
{
    Arguments args;
    if (!args.ParseArguments(argc, argv))
    {
        return -1;
    }

    return 0;
}