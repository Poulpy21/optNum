
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
		bool wolfe, inv;

		Gradient(Simulateur *s, double t) : Optimiseur(s) { 
			this->t = t;
			this->wolfe = (t < 0);
			this->inv = (t == 0);
		};

		bool run(Vector x0, double epsilon, int nbIterationsMax) {

			delete points;
			points = new list<Vector>;
		
			nbIterations = 0;
			clock_t start, end;
			
			start = clock();


			TinyVector<int,2> dim = x0.shape();
			Vector x(dim), g(dim), d(dim);
			Vector *xx;

			x = x0;
			g = s->getGradient(x);

			while(sqrt(scalarProduct(g,transpose(g))) > epsilon && nbIterations < nbIterationsMax) {
				
				xx = new Vector(dim);
				*xx = x;

				points->push_back(*xx);
				
				g = s->getGradient(x);
				d = -g;
				
				if (wolfe)
					t = Wolfe(x, d); 

				if (inv)
					t = 0.001/(nbIterations+1);
				
				x = x + t*d;

				nbIterations++;
			}	
			
			xx = new Vector(dim);
			*xx = x;
			points->push_back(*xx);
			
			end = clock();
			duree = (double) (end - start);

			return (nbIterations <= nbIterationsMax);	
		}

		
};

#endif
