

#ifndef FUNCS_H
#define FUNCS_H

#include "types.h"

using namespace blitz;

//A*B

Matrix mult(const Matrix &A,  const Matrix &B);
Vectorr transpose(const Vectorr v);

double scalarProduct(const Vectorr &v1, const Vectorr &v2);

Matrix inverseMatrix(const Matrix &M);

void arrayInfo(const Array<double, 2> &a);

#endif
