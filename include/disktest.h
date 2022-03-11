#ifndef DISKTEST_H
#define DISKTEST_H

#include <chrono>
#include <random>
#include <iomanip>

#include "diskbase.h"

class DiskTest : public DiskBase
{
protected:
public:
    void _write_test(size_t numBytes);
    void _read_test();
    std::minstd_rand0 _generator;
public:
    DiskTest();
    ~DiskTest();
    void run(size_t numBytes);
};

#endif