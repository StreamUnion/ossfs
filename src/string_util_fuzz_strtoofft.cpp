#include <stddef.h>
#include <limits>
#include <stdint.h>
#include <string>
#include <iostream>

#include "string_util.h"
#include "test_util.h"

using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {

  char* dataStr = (char*)malloc(Size+1);
  memcpy(dataStr, Data, Size);
  dataStr[Size] = '\0';

  s3fs_strtoofft(dataStr, false);

  char *base64;
  base64 = s3fs_base64(reinterpret_cast<const unsigned char *>(Data), Size);

  s3fs_strtoofft(base64, true);

  free(dataStr);
  free(base64);
  return 0;
}
