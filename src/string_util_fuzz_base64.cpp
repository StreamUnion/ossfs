#include <stddef.h>
#include <limits>
#include <stdint.h>
#include <string>
#include <iostream>

#include "string_util.h"
#include "test_util.h"

using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  size_t len;
  char *base64;
  unsigned char *decode_base64;

  base64 = s3fs_base64(reinterpret_cast<const unsigned char *>(Data), Size);
  decode_base64 = s3fs_decode64(base64, &len);

  char* dataStr = (char*)malloc(Size+1);
  memcpy(dataStr, Data, Size);
  dataStr[Size] = '\0';

  char* decodeStr = (char*)malloc(len+1);
  memcpy(decodeStr, decode_base64, len);
  decodeStr[len] = '\0';

  ASSERT_STREQUALS(dataStr, decodeStr);

  free(base64);
  free(dataStr);
  free(decodeStr);
  free(decode_base64);

  return 0;
}
