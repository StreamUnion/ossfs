/*
 * s3fs - FUSE-based file system backed by Aliyun OSS
 *
 * Copyright 2014 Andrew Gaul <andrew@gaul.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <limits>
#include <stdint.h>
#include <string>

#include "string_util.h"
#include "test_util.h"

void test_trim()
{
  ASSERT_EQUALS(std::string("1234"), trim("  1234  "));
  ASSERT_EQUALS(std::string("1234"), trim("1234  "));
  ASSERT_EQUALS(std::string("1234"), trim("  1234"));
  ASSERT_EQUALS(std::string("1234"), trim("1234"));

  ASSERT_EQUALS(std::string("1234  "), trim_left("  1234  "));
  ASSERT_EQUALS(std::string("1234  "), trim_left("1234  "));
  ASSERT_EQUALS(std::string("1234"), trim_left("  1234"));
  ASSERT_EQUALS(std::string("1234"), trim_left("1234"));

  ASSERT_EQUALS(std::string("  1234"), trim_right("  1234  "));
  ASSERT_EQUALS(std::string("1234"), trim_right("1234  "));
  ASSERT_EQUALS(std::string("  1234"), trim_right("  1234"));
  ASSERT_EQUALS(std::string("1234"), trim_right("1234"));

  ASSERT_EQUALS(std::string("0"), str(0));
  ASSERT_EQUALS(std::string("1"), str(1));
  ASSERT_EQUALS(std::string("-1"), str(-1));
  ASSERT_EQUALS(std::string("9223372036854775807"), str(std::numeric_limits<int64_t>::max()));
  ASSERT_EQUALS(std::string("-9223372036854775808"), str(std::numeric_limits<int64_t>::min()));
  ASSERT_EQUALS(std::string("0"), str(std::numeric_limits<uint64_t>::min()));
  ASSERT_EQUALS(std::string("18446744073709551615"), str(std::numeric_limits<uint64_t>::max()));
}

void test_base64()
{
  size_t len;
  char *base64;
  unsigned char *decode_base64;
  ASSERT_STREQUALS(s3fs_base64(NULL, 0), NULL);
  ASSERT_STREQUALS(reinterpret_cast<const char *>(s3fs_decode64(NULL, &len)), NULL);
  ASSERT_STREQUALS(s3fs_base64(reinterpret_cast<const unsigned char *>(""), 0), NULL);
  ASSERT_STREQUALS(reinterpret_cast<const char *>(s3fs_decode64("", &len)), NULL);

  base64 = s3fs_base64(reinterpret_cast<const unsigned char *>("1"), 1);
  ASSERT_STREQUALS(base64, "MQ==");
  free(base64);
  decode_base64 = s3fs_decode64("MQ==", &len);
  ASSERT_STREQUALS(reinterpret_cast<const char *>(decode_base64), "1");
  ASSERT_EQUALS(len, static_cast<size_t>(1));
  free(decode_base64);

  base64 = s3fs_base64(reinterpret_cast<const unsigned char *>("12"), 2);
  ASSERT_STREQUALS(base64, "MTI=");
  free(base64);
  decode_base64 = s3fs_decode64("MTI=", &len);
  ASSERT_STREQUALS(reinterpret_cast<const char *>(decode_base64), "12");
  ASSERT_EQUALS(len, static_cast<size_t>(2));
  free(decode_base64);

  base64 = s3fs_base64(reinterpret_cast<const unsigned char *>("123"), 3);
  ASSERT_STREQUALS(base64, "MTIz");
  free(base64);
  decode_base64 = s3fs_decode64("MTIz", &len);
  ASSERT_STREQUALS(reinterpret_cast<const char *>(decode_base64), "123");
  ASSERT_EQUALS(len, static_cast<size_t>(3));
  free(decode_base64);

  base64 = s3fs_base64(reinterpret_cast<const unsigned char *>("1234"), 4);
  ASSERT_STREQUALS(base64, "MTIzNA==");
  free(base64);
  decode_base64 = s3fs_decode64("MTIzNA==", &len);
  ASSERT_STREQUALS(reinterpret_cast<const char *>(decode_base64), "1234");
  ASSERT_EQUALS(len, static_cast<size_t>(4));
  free(decode_base64);

  // TODO: invalid input
}

int main(int argc, char *argv[])
{
  test_trim();
  test_base64();
  return 0;
}
