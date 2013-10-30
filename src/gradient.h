
#include <list>
#include <blitz/array.h>

#include "simulateur.h"
#include "types.h"

#ifndef GRADIENT_H
#define GRADIENT_H


class Gradient : public Optimiseur

{
	
	public:
		double t;

		Gradient(Vector x0, double t, Simulateur *s, double epsilon) : Optimiseur(x0, s, epsilon) { 
			
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
				d = -g;
				
				t = Wolfe(x, d); 
				
				x = x + t*d;
			}	
			
			xx = new Vector(dim);
			*xx = x;
			points.push(*xx);
		}

		
};

#endif
