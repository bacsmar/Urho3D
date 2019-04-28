// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_TYPES_H
#define TB_TYPES_H

// Include <tb_config.h> so it may be overridden in application directory.
// The default "tb_config.h" (local) will be used if there is no other match.
#include "tb_config.h"

#include <string.h>

namespace tb {

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

// Note: defining templates for commonly used math functions just sux. 
// way to screw your customers downstream. Max,Min,Abs,Clamp,ClampClipMax
// Adding TB prefix --JM

template <class T>
T TBMax(const T& left, const T& right) { return left > right ? left : right; }

template <class T>
T TBMin(const T& left, const T& right) { return left < right ? left : right; }

template <class T>
T TBAbs(const T& value) { return value < 0 ? -value : value; }

template <class T>
T TBClamp(const T& value, const T& min, const T& max)
{ return (value > max) ? max : ((value < min) ? min : value); }

/** Returns value clamped to min and max. If max is greater than min,
    max will be clipped to min. */
template <class T>
T TBClampClipMax(const T& value, const T& min, const T& max)
{
    return (value > max)
            ? (max > min ? max : min)
            : ((value < min) ? min : value);
}

#ifndef TBMAX
/** This is deprecated! Use Max(a, b)! */
#define TBMAX(a, b) TBMax(a, b)
#endif

#ifndef TBMIN
/** This is deprecated! Use Min(a, b)! */
#define TBMIN(a, b) TBMin(a, b)
#endif

#ifndef TBABS
/** This is deprecated! Use Abs(value)! */
#define TBABS(value) TBAbs(value)
#endif

#ifndef TBCLAMP
/** This is deprecated! Use Clamp(value, min, max)! */
#define TBCLAMP(value, min, max) TBClamp(value, min, max)
#endif

/** Makes it possible to use the given enum types as flag combinations.
    That will catch use of incorrect type during compilation, that wouldn't be caught
    using a uint32 flag. */
#define MAKE_ENUM_FLAG_COMBO(Enum) \
    inline Enum operator | (Enum a, Enum b)  { return static_cast<Enum>(static_cast<uint32>(a) | static_cast<uint32>(b)); } \
    inline Enum operator & (Enum a, Enum b)  { return static_cast<Enum>(static_cast<uint32>(a) & static_cast<uint32>(b)); } \
    inline Enum operator ^ (Enum a, Enum b)  { return static_cast<Enum>(static_cast<uint32>(a) ^ static_cast<uint32>(b)); } \
    inline void operator |= (Enum &a, Enum b) { a = static_cast<Enum>(static_cast<uint32>(a) | static_cast<uint32>(b)); } \
    inline void operator &= (Enum &a, Enum b) { a = static_cast<Enum>(static_cast<uint32>(a) & static_cast<uint32>(b)); } \
    inline void operator ^= (Enum &a, Enum b) { a = static_cast<Enum>(static_cast<uint32>(a) ^ static_cast<uint32>(b)); } \
    inline Enum operator ~ (Enum a)  { return static_cast<Enum>(~static_cast<uint32>(a)); }

}; // namespace tb

#endif // TB_TYPES_H
