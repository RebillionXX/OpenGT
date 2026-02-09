#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <iostream>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <unistd.h>

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef float       f32;
typedef double      f64;

#define         MAKE_RGB(r, g, b)                       (((u32)(r) << 8) + ((u32)(g) << 16) + ((u32)(b) << 24))
#define         MAKE_RGBA(r, g, b, a)                   (((u32)(r) << 8) + ((u32)(g) << 16) + ((u32)(b) << 24) + ((u32)(a)))
                        
#define         GET_BLUE(p)                             ( (p)               >> 24)
#define         GET_GREEN(p)                            (((p) & 0x00FF0000) >> 16)
#define         GET_RED(p)                              (((p) & 0x0000FF00) >>  8)
#define         GET_ALPHA(p)                            ( (p) & 0x000000FF       )
                        
#define         SAFE_RELEASE(p)                         { if(p != NULL) { (p).release();   (p)=NULL; } }
#define         SAFE_FREE(p)                            { if(p != NULL) { free(p);          (p)=NULL; } }
#define         SAFE_DELETE_ARRAY(p)                    { if(p != NULL) { delete[] (p);     (p)=NULL; } }
#define         SAFE_DELETE(p)                          { if(p != NULL) { delete (p);       (p)=NULL; } }

#define			SETBIT( a, b)							((a) |= (b))
#define			UNSETBIT( a, b)							((a) &= ~(b))
#define			TESTBIT( a, b)							((a) & (b))

#define			MIN( a, b)								( (a) > (b) ? (b) : (a))
#define			MAX( a, b)								( (a) > (b) ? (a) : (b))
#define			MINMAX( _min_, _v_, _max_ )				( MIN( MAX( (_min_), (_v_) ), (_max_) ) )

// Returns The current working directory of the application, with a trailing '/'
std::string GetAppPath();

// Returns The path where application data should be saved
// !! Currently returns an empty string !!
std::string GetSavePath();

// Returns A 32-bit timer that accumulates milliseconds since the program started
// The value increments in a monotonic fashion
u32 GetSystemTimeTick();

// Returns A 64-bit timer in milliseconds since the program started
// Useful for long-running timers to avoid overflow
u64 GetSystemTimeTickLong();

// Returns The current system time in milliseconds as a double.
// Provides a slightly more precise timer than GetSystemTimeTick()
f64 GetSystemTimeAccurate();

// Returns The current local time formatted as "HH:MM:SS"
std::string GetTimeAsString();

// Returns The current local date and time formatted as "DD/MM HH:MM:SS"
std::string GetDateAndTimeAsString();

// Retrieves the current local date and time components
// Outputs: monthOut, dayOut, yearOut, hourOut, minOut, secOut
void GetDateAndTime(i32* monthOut, i32* dayOut, i32* yearOut, i32* hourOut, i32* minOut, i32* secOut);