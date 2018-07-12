#include <inttypes.h>
#include "BinaryStream.h"
#include "Util.h"

BinaryStream::BinaryStream(int size)
{
    this->offset = 0;
    this->count = 0;
    this->buffer = new uint8_t[size];
    for(int i = 0; i < size; i++){
        this->buffer[i] = 0;
    }
}

int BinaryStream::getOffset()
{
    return this->offset;
}

void BinaryStream::setOffset(int offset)
{
    this->offset = offset;
}

int BinaryStream::getCount()
{
    return this->count;
}

uint8_t *BinaryStream::getBuffer(){
    return this->buffer;
}

char *BinaryStream::getAsCharArray()
{
    char realBuffer[this->offset];
    for(int i = 0; i < this->offset; i++){
        realBuffer[i] = this->buffer[i];
    }
    return realBuffer;
}

int BinaryStream::getByte()
{
    return this->buffer[this->offset++] & 0xff;
}

void BinaryStream::putByte(int b)
{
    this->buffer[this->offset++] = b;
}

int BinaryStream::getInt()
{
    return ((this->buffer[this->offset++] & 0xff) << 24) +
           ((this->buffer[this->offset++] & 0xff) << 16) +
           ((this->buffer[this->offset++] & 0xff) << 8) +
           (this->buffer[this->offset++] & 0xff);
}

void BinaryStream::putInt(int i)
{
    this->buffer[this->offset++] = (i >> 24) & 0xFF;
    this->buffer[this->offset++] = (i >> 16) & 0xFF;
    this->buffer[this->offset++] = (i >> 8) & 0xFF;
    this->buffer[this->offset++] = i & 0xFF;
}

long BinaryStream::getLong()
{
    return ((long)(this->buffer[this->offset++] << 56) +
            (long)(this->buffer[this->offset++] & 0xFF << 48) +
            (long)(this->buffer[this->offset++] & 0xFF << 40) +
            (long)(this->buffer[this->offset++] & 0xFF << 32) +
            (long)(this->buffer[this->offset++] & 0xFF << 24) +
            ((this->buffer[this->offset++] & 0xFF) << 16) +
            ((this->buffer[this->offset++] & 0xFF) << 8) +
            ((this->buffer[this->offset++] & 0xFF)));
}

void BinaryStream::putLong(long l)
{
    this->buffer[this->offset++] = l >> 56;
    this->buffer[this->offset++] = l >> 48;
    this->buffer[this->offset++] = l >> 40;
    this->buffer[this->offset++] = l >> 32;
    this->buffer[this->offset++] = l >> 24;
    this->buffer[this->offset++] = l >> 16;
    this->buffer[this->offset++] = l >> 8;
    this->buffer[this->offset++] = l;
}

float BinaryStream::getFloat()
{
    return intBitsToFloat(this->getInt());
}

void BinaryStream::putFloat(float f)
{
    this->putInt(floatToIntBits(f));
}

float BinaryStream::intBitsToFloat(int i)
{
    union {
        int i;
        float f;
    } u;
    u.i = i;
    return u.f;
}

int BinaryStream::floatToIntBits(float f)
{
    union {
        int i;
        float f;
    } u;
    u.f = f;
    return u.i;
}
