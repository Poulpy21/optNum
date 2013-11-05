

#include <list>
#include "simulateur.h"
#include "types.h"
#include "time.h"

#ifndef NEWTON_H
#define NEWTON_H

#include <blitz/array.h>

class Newton : public Optimiseur

{

	public:
		
		bool wolfe;

		Newton(Simulateur *s) : Optimiseur(s) { 
			this->wolfe = false;
		};
		
		Newton(Simulateur *s, bool wolfe) : Optimiseur(s) { 
			this->wolfe = wolfe;
		};

		bool run(Vectorr x0, double epsilon, int nbIterationsMax) {

			delete points;
			points = new list<Vectorr>;

			nbIterations = 0;
			clock_t start, end;

			start = clock();

			TinyVector<int,2> dim = x0.shape();
			Vectorr x(dim), g(dim), d(dim);
			Vectorr *xx;

			x = x0;
			g = s->getGradient(x);

			while(sqrt(scalarProduct(g,transpose(g))) > epsilon && nbIterations < nbIterationsMax) {

				xx = new Vectorr(dim);
				*xx = x;

				points->push_back(*xx);

				g = s->getGradient(x);

				d = - mult(inverseMatrix(s->getHessian(x)), g);
				
				if (wolfe) {
					double t = Wolfe(x, d);
					x = x + t*d;
				}
				else
					x = x + d;

				nbIterations++;
			}	

			xx = new Vectorr(dim);
			*xx = x;
			points->push_back(*xx);

			end = clock();
			duree = (double) (end - start);

			return (nbIterations <= nbIterationsMax);	
		
		}
};
#endif
