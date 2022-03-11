#ifndef DISKBASE_H
#define DISKBASE_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <sstream>

class DiskBase
{
protected:
public:
    bool _writeMode;
    size_t _fileSize;
    std::ifstream _readStream;
    std::ofstream _writeStream;
    void _open_write();
    void _open_read();
    void _delete();
public:
    std::string filePath;
    DiskBase();
    ~DiskBase();
    void write(uint8_t* data, size_t length);
    void read(uint8_t* data, size_t length = 0);
    size_t size();
};

#endif
