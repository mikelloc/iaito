/** \file IaitoCommon.h
 * This file contains any definition that is useful in the whole project.
 * For example, it may contain custom types (RVA, ut64), list iterators, etc.
 */
#ifndef CUTTERCORE_H
#define CUTTERCORE_H

#include "r_core.h"
#include <QString>

// Workaround for compile errors on Windows
#ifdef Q_OS_WIN
#undef min
#undef max
#endif // Q_OS_WIN

// radare2 list iteration macros
#define IaitoRListForeach(list, it, type, x) \
    if (list) for (it = list->head; it && ((x=static_cast<type*>(it->data))); it = it->n)

#define IaitoRVectorForeach(vec, it, type) \
	if ((vec) && (vec)->a) \
		for (it = (type *)(vec)->a; (char *)it != (char *)(vec)->a + ((vec)->len * (vec)->elem_size); it = (type *)((char *)it + (vec)->elem_size))

// Global information for Iaito
#define APPNAME "Iaito"

/**
 * @brief Type to be used for all kinds of addresses/offsets in r2 address space.
 */
typedef ut64 RVA;

/**
 * @brief Maximum value of RVA. Do NOT use this for specifying invalid values, use RVA_INVALID instead.
 */
#define RVA_MAX UT64_MAX

/**
 * @brief Value for specifying an invalid RVA.
 */
#define RVA_INVALID RVA_MAX

inline QString RAddressString(RVA addr)
{
    return QString::asprintf("%#010llx", addr);
}

inline QString RSizeString(RVA size)
{
    return QString::asprintf("%#llx", size);
}

inline QString RHexString(RVA size)
{
    return QString::asprintf("%#llx", size);
}

#ifdef IAITO_SOURCE_BUILD
#define IAITO_EXPORT Q_DECL_EXPORT
#else
#define IAITO_EXPORT Q_DECL_IMPORT
#endif


#if defined(__has_cpp_attribute)
    #if __has_cpp_attribute(deprecated)
        #define IAITO_DEPRECATED(msg) [[deprecated(msg)]]
    #endif
#endif
#if !defined(IAITO_DEPRECATED)
#define IAITO_DEPRECATED(msg)
#endif

#endif // CUTTERCORE_H

