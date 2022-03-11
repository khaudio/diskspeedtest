#include "disktest.h"

int main(int argc, const char** argv)
{
    DiskTest d;
    size_t size;

    /* Default to 1GB if test size not specified */
    if (argc < 2) size = 1073741824;
    else size = std::atoi(argv[1]);

    std::cout << "Starting r/w test with size " << size << std::endl;

    d.run(size);

    return 0;
}

