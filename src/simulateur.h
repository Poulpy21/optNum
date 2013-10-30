
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <blitz/array.h>

#include "types.h"

#ifndef SIMULATEUR_H
#define SIMULATEUR_H

using namespace blitz;

class Simulateur {
	
	public:
		virtual double getValue(const Vector &x) = 0;
		virtual Vector getGradient(const Vector &x) = 0;
		virtual Matrix getHessian(const Vector &x) = 0;
};
	
#endif
