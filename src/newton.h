

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
			
			firstIndex i;
			secondIndex j;
			
			x = x0;
			g = s->getGradient(x);

			while(scalarProduct(g,transpose(g)) > epsilon) {
				
				points.push_back(&x);
				
				cout << "\n\nx = \n" << x << "\nf(x) = " << s->getValue(x);
				g = s->getGradient(x);
				d = -g;

				x = x + t*d;
			}	
				
			points.push_back(&x);
		}

		
};

#endif
