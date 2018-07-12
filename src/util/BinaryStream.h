#pragma once

#include <inttypes.h>

class BinaryStream
{
private:
  int offset;
  int count;
  uint8_t *buffer;

public:
  BinaryStream(int size);

  int getOffset();
  void setOffset(int offset);
  int getCount();
  uint8_t *getBuffer();

  char *getAsCharArray();

  int getByte();
  void putByte(int b);

  int getInt();
  void putInt(int i);

  long getLong();
  void putLong(long l);

  float getFloat();
  void putFloat(float f);

private:
  static float intBitsToFloat(int i);
  static int floatToIntBits(float f);
};