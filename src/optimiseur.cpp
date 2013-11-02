
#include "optimiseur.h"
#include "funcs.h"
#include <unistd.h>
#include <blitz/array.h>
#include <time.h>

Optimiseur::Optimiseur(Simulateur *s) {
	this->s = s;
	this->points = new list<Vector>;
}

double Optimiseur::Wolfe(Vector &x0, Vector &d, double m1, double m2) {

	double t, tg, td;
	double q0, dq0, q, dq;
	
	TinyVector<int, 2> dim = x0.shape();
	Vector x(dim);
	
	t = 1.0;

	tg = 0.0;
	td = DOUBLE_INFINITY;
	
	q0 = s->getValue(x0);
	dq0 = scalarProduct(transpose(s->getGradient(x0)), d); 
	
	while(1) {
		
		x = x0 + t * d;
		
		q = s->getValue(x);
		dq = scalarProduct(transpose(s->getGradient(x)), d); 

		if ((q <= q0 + m1 * t * dq0) && (dq >= m2 * dq0)) {
				break;
		}
		else if (q > q0 + m1 * t * dq0) { 
			td = t;
		}
		else {
			tg = t;
		}
		
		if (td == DOUBLE_INFINITY) 
			t = 10*tg;
		else 
			t = (tg + td)/2.0;
	}

	return t;	
}


std::list<Vector> Optimiseur::getPoints() {

	return *this->points;
}

Vector Optimiseur::getLastPoint() {

	return this->points->back();
}

int Optimiseur::getNbIterations() {
	return this->nbIterations;
}

double Optimiseur::getDuree() {
	return (1000*this->duree)/CLOCKS_PER_SEC;
}
