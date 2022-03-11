#include "diskbase.h"

DiskBase::DiskBase() :
_writeMode(0),
_fileSize(0)
{
    std::stringstream timestream;
    timestream << "dst_" << std::time(0);
    this->filePath = timestream.str();
}

DiskBase::~DiskBase()
{
    this->_writeStream.close();
    this->_readStream.close();
    _delete();
}

void DiskBase::_delete()
{
    std::remove(this->filePath.c_str());
}

void DiskBase::_open_write()
{
    this->_readStream.close();
    this->_writeStream.open(this->filePath.c_str(), std::ios::binary);
    this->_writeMode = 1;
}

void DiskBase::_open_read()
{
    this->_writeStream.close();
    this->_readStream.open(this->filePath.c_str(), std::ios::binary);
    this->_writeMode = 0;
}

void DiskBase::write(uint8_t* data, size_t length)
{
    if (!this->_writeMode) _open_write();
    this->_fileSize += length;
    this->_writeStream.write(reinterpret_cast<const char*>(data), length);
}

void DiskBase::read(uint8_t* data, size_t length)
{
    if (this->_writeMode) _open_read();
    this->_readStream.read(reinterpret_cast<char*>(data), length);
}

size_t DiskBase::size()
{
    return this->_fileSize;
}
