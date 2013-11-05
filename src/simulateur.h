
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
		virtual double getValue(const Vectorr &x) = 0;
		virtual Vectorr getGradient(const Vectorr &x) = 0;
		virtual Matrix getHessian(const Vectorr &x) = 0;
};
	
#endif
