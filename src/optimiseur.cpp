
#include "optimiseur.h"
#include "funcs.h"
#include <unistd.h>
#include <blitz/array.h>

Optimiseur::Optimiseur(Vector x0, Simulateur *s, double epsilon) : x0(x0){

	this->s = s;
	this->epsilon = epsilon;
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
	dq0 = scalarProduct(s->getGradient(x0), transpose(d)); 

	x = x0 + t * d;
	
	cout << "\n\n\nWOLFE\n\n\n";
	cout << "x = x0 + t * d\nx = " << x << "\nx0 = " << x0 << "\nt = " << t << "\nd = " << d;

	q = s->getValue(x);
	dq = scalarProduct(transpose(s->getGradient(x)), d); 

	while(1) {
		
		if ((q <= q0 + m1 * t * q0) && (dq >= m2 * dq0)) {
				break;
		}
		else if (dq > q0 + m1 * t * dq0) { 
			td = t;
		}
		else {
			tg = t;
		}
		
		if (td == DOUBLE_INFINITY) 
			t = 2*tg;
		else 
			t = (tg + td)/2.0;

		x = x0 + t * d;

		q = s->getValue(x);
		dq = scalarProduct(transpose(s->getGradient(x)), d); 
	}

	return t;	
}


std::list<Vector *> Optimiseur::getPoints() {

	return this->points;
}

Vector *Optimiseur::getLastPoint() {

	return this->points.back();
}
