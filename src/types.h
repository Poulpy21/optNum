
#ifndef TYPES_H
#define TYPES_H

#include <blitz/array.h>

#define DOUBLE_INFINITY std::numeric_limits<double>::infinity()

using namespace blitz;

typedef Array<double,2> Vector;
typedef Array<double,2> Matrix;

#endif
