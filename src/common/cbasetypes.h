#ifndef _CBASETYPES_H_
#define _CBASETYPES_H_

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <utility>

#include "logging.h"

// The following definitions are set by CMake based on the architecture
// #define ENV64BIT
// #define ENV32BIT

// Ensure one of the definitions is set
#if !defined(ENV64BIT) && !defined(ENV32BIT)
#error "Neither ENV64BIT nor ENV32BIT is defined"
#endif

// Debug mode
#if defined(_DEBUG) && !defined(DEBUG)
#define DEBUG
#endif

// Release mode
#if !defined(_DEBUG) && !defined(RELEASE)
#define RELEASE
#endif

// define a break macro for debugging
#define XI_DEBUG_BREAK_IF(_CONDITION_) \
    static_assert(false, "Use of XI_DEBUG_BREAK_IF is deprecated. Check your conditions and log appropriately instead.")

// typedef/using
using int8  = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8  = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

template <typename T>
inline void destroy(T*& ptr)
{
    delete ptr; // cpp.sh allow
    ptr = nullptr;
}

template <typename T>
inline void destroy_arr(T*& ptr)
{
    delete[] ptr; // cpp.sh allow
    ptr = nullptr;
}

// string case comparison for *nix portability
#if !defined(_MSC_VER)
#define strcmpi strcasecmp
#define stricmp strcasecmp

// https://stackoverflow.com/questions/12044519/what-is-the-windows-equivalent-of-the-unix-function-gmtime-r
// gmtime_r() is the thread-safe version of gmtime(). The MSVC implementation of gmtime() is already thread safe,
// the returned struct tm* is allocated in thread-local storage.
// That doesn't make it immune from trouble if the function is called multiple times on the same
// thread and the returned pointer is stored.
// You can use gmtime_s() instead. Closest to gmtime_r() but with the arguments reversed

// Provide func_s implementations for Unix
#define _gmtime_s(a, b)    gmtime_r(b, a)
#define _localtime_s(a, b) localtime_r(b, a)
#else // MSVC
#define _gmtime_s(a, b)    gmtime_s(a, b)
#define _localtime_s(a, b) localtime_s(a, b)
#endif

#include <chrono>

using namespace std::literals::chrono_literals;
using server_clock = std::chrono::system_clock;
using time_point   = server_clock::time_point;
using duration     = server_clock::duration;

using hires_clock      = std::chrono::high_resolution_clock;
using hires_time_point = server_clock::time_point;
using hires_duration   = server_clock::duration;

#include <queue>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <typename T>
struct PtrGreater
{
    bool operator()(const T left, const T right)
    {
        return *left > *right;
    }
};

template <class T>
using MinHeapPtr = std::priority_queue<T, std::vector<T>, PtrGreater<T>>;

#define DISALLOW_COPY(TypeName)                    \
    TypeName(const TypeName&)            = delete; \
    TypeName& operator=(const TypeName&) = delete;

#define DISALLOW_MOVE(TypeName)               \
    TypeName(TypeName&&)            = delete; \
    TypeName& operator=(TypeName&&) = delete;

#define DISALLOW_COPY_AND_MOVE(TypeName) \
    DISALLOW_COPY(TypeName)              \
    DISALLOW_MOVE(TypeName)

#include "tracy.h"

#endif /* _CBASETYPES_H_ */
