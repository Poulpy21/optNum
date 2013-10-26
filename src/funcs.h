

#ifndef FUNCS_H
#define FUNCS_H

#include <blitz/array.h>
#include "types.h"

//A*B

Matrix mult(const Matrix &A,  const Matrix &B);
Vector transpose(const Vector v);

double scalarProduct(const Vector &v1, const Vector &v2);

void arrayInfo(const Array<double, 2> &a);

#endif
