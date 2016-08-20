//
// Created by iensen on 8/16/16.
//

#ifndef PLOG_PLATFORM_H
#define PLOG_PLATFORM_H



#if defined(_MSC_VER) && _MSC_VER >= 1200
#if _MSC_VER >= 1600
#include <stdint.h>
#endif
#elif defined(__GNUC__) && __GNUC__ >= 3
#include <inttypes.h>
typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef int16_t   int16;
typedef int32_t   int32;
typedef uint32_t  uint32;
typedef uint64_t  uint64;
typedef int64_t   int64;
typedef uintptr_t uintp;
#else
#error unknown compiler or platform. Please add typedefs manually.
#endif
#endif //PLOG_PLATFORM_H
