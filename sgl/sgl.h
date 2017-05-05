#ifndef _SGL_y7483fhcbcyg88c_H
#define _SGL_y7483fhcbcyg88c_H
namespace sgl {
}

// Macros
#define SINGLE_ARG(...) __VA_ARGS__

// Any type
#ifndef sgl_any
    // boost::any
    #include <boost/any.hpp>
    #define sgl_any                     boost::any
    #define sgl_any_cast(type,anyvar)   boost::any_cast< type >(anyvar)
#endif

// ===============================

#include "sgl_utils/simple_lock.h"

typedef enum {SGL_DRAW_LOCK, SGL_MEM_LOCK} sglLockStates;
SimpleLock<LOCK_RECURSIVE,sglLockStates> sglDrawLock;

// ===============================

// utils
#include "sgl_utils/stl_utils.h"
#include "sgl_utils/gl_utils.h"
#include "sgl_utils/gl_transformation_util.h"

// objects
#include "sgl_objects/figure.h"
#include "sgl_objects/point.h"
#include "sgl_objects/line.h"
#include "sgl_objects/box.h"
#include "sgl_objects/sphere.h"

// }
#endif
