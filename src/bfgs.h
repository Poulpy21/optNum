

#include <list>
#include "simulateur.h"
#include "types.h"

#ifndef BFGS_H
#define BFGS_H

#include <blitz/array.h>

class BFGS : public Optimiseur

{
	
	public:
		BFGS(Simulateur *s) : Optimiseur(s) { };

		bool run(Vector x0, double epsilon, int nbIterationsMax) {

			delete points;
			points = new list<Vector>;
		
			nbIterations = 0;
			clock_t start, end;
			
			start = clock();
		

			TinyVector<int,2> dim = x0.shape();
			Vector xk(dim), xk1(dim), dk(dim), gk(dim), gk1(dim), sk(dim), yk(dim);
			double tk;

			firstIndex i;
			secondIndex j;
			Matrix W(x0.size(), x0.size());
			W = (i == j);	
			
			xk = x0;
			gk = s->getGradient(x0);
			
			while(scalarProduct(gk,transpose(gk)) > epsilon && nbIterations < nbIterationsMax) {
				
				points->push_back(*new Vector(xk));

				dk = - mult(W, gk);
				
				tk = Wolfe(xk, dk);

				xk1 = xk + tk * dk;
				gk1 = s->getGradient(xk1);

				sk = xk1 - xk;
				yk = gk1 - gk;
				
				computeMatrix(W, sk, yk); 
				
				xk = xk1;
				gk = gk1;

				nbIterations++;
			}	
				
			points->push_back(* new Vector(xk));
			
			end = clock();
			duree = (double) (end - start);

			return (nbIterations <= nbIterationsMax);	
		}

	private:
		void inline computeMatrix(Matrix &W, Vector &s, Vector &y) {

			double p = scalarProduct(transpose(y), s); 
			
			cout << "\n\n" << W;

			W = W 
				- (mult(s,mult(transpose(y), W)) + mult(mult(W, y),transpose(s)))/p +
				+ (1 + mult(transpose(y), mult(W, y)) / p) * scalarProduct(transpose(s), s) / p;

		}
		
};

#endif
