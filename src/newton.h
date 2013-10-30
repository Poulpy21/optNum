

#include <list>
#include "simulateur.h"
#include "types.h"

#ifndef NEWTON_H
#define NEWTON_H

#include <blitz/array.h>

class Newton : public Optimiseur

{
	
	public:
		double t;

		Newton(Vector x0, double t, Simulateur *s, double epsilon) : Optimiseur(x0, s, epsilon) { 
			
			this->t = t;
		};

		void run() {
		
			TinyVector<int,2> dim = x0.shape();
			Vector x(dim), g(dim), d(dim);
			Vector *xx;

			firstIndex i;
			secondIndex j;
			
			x = x0;
			g = s->getGradient(x);

			while(sqrt(scalarProduct(g,transpose(g))) > epsilon) {
				
				xx = new Vector(dim);
				*xx = x;

				points.push(*xx);
				
				g = s->getGradient(x);
				
				d = - mult(inverseMatrix(s->getHessian(x)), g);
				
				//t = Wolfe(x, d); 
				
				cout << "\n" << x << " f(x) = " << s->getValue(x) << " ||g||^2 = " << scalarProduct(g,transpose(g));
				x = x + t*d;
			}	
			
			xx = new Vector(dim);
			*xx = x;
			points.push(*xx);
		}

		
};

#endif
