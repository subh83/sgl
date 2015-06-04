
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

// utils
#include "sgl_utils/stl_utils.h"
#include "sgl_utils/gl_utils.h"
#include "sgl_utils/gl_transformation_util.h"

// objects
#include "sgl_objects/figure.h"
#include "sgl_objects/point.h"
#include "sgl_objects/line.h"

