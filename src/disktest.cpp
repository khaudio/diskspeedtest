#include "disktest.h"

DiskTest::DiskTest() :
DiskBase::DiskBase(),
_generator(std::time(0))
{
}

DiskTest::~DiskTest()
{
}

void DiskTest::_write_test(size_t numBytes)
{
    using namespace std::chrono;

    long double bytesPerSecond;
    size_t i(0);
    int remainder(numBytes % 4);
    int32_t randomInt;
    uint8_t* buff = reinterpret_cast<uint8_t*>(&randomInt);
    std::stringstream mBytesPerSecond;
    high_resolution_clock::time_point writeStart, writeEnd;
    
    _open_write();

    writeStart = high_resolution_clock::now();

    while (i < numBytes)
    {
        randomInt = this->_generator();
        this->_writeStream.write(
                reinterpret_cast<const char*>(buff),
                ((numBytes - i) > 4 ? 4 : remainder)
            );
        i += 4;
    }

    writeEnd = high_resolution_clock::now();
    auto writeDurationNs = duration_cast<nanoseconds>(writeEnd - writeStart);
    
    this->_fileSize += i;

    bytesPerSecond = (
            (
                static_cast<long double>(numBytes)
                / static_cast<long double>(writeDurationNs.count() / 1e9)
            )
        );
    mBytesPerSecond << std::setprecision(5) << (bytesPerSecond / 1e6);

    std::cout << "Write speed: " << mBytesPerSecond.str();
    std::cout << " MB per second" << std::endl;
    this->_writeStream.close();
}

void DiskTest::_read_test()
{
    using namespace std::chrono;

    long double bytesPerSecond;
    size_t i(0);
    int remainder(size() % 4);
    char buff[4];
    std::stringstream mBytesPerSecond;
    high_resolution_clock::time_point readStart, readEnd;
    
    _open_read();

    this->_readStream.seekg(0);

    readStart = high_resolution_clock::now();

    while (i < size())
    {
        this->_readStream.read(
                buff,
                ((size() - i) > 4 ? 4 : remainder)
            );
        i += 4;
    }

    readEnd = high_resolution_clock::now();
    auto readDurationNs = duration_cast<nanoseconds>(readEnd - readStart);

    bytesPerSecond = (
            (
                static_cast<long double>(size())
                / static_cast<long double>(readDurationNs.count() / 1e9)
            )
        );
    mBytesPerSecond << std::setprecision(5) << (bytesPerSecond / 1e6);

    std::cout << "Read speed: " << mBytesPerSecond.str();
    std::cout << " MB per second" << std::endl;
    this->_readStream.close();
}

void DiskTest::run(size_t numBytes)
{
    _write_test(numBytes);
    _read_test();
}
