
#include <list>

#include "simulateur.h"
#include "types.h"

#ifndef OPTIMISEUR_H
#define OPTIMISEUR_H

class Optimiseur 

{
	
	public:
		Optimiseur(Vector x0, Simulateur *s, double epsilon);

		virtual void run() = 0;
		
		std::list<Vector *> getPoints();
		Vector *getLastPoint();

	
	protected:
		Simulateur *s;
		Vector x0;
		double epsilon;

		std::list<Vector *> points;
		
		double Wolfe(Vector &point, Vector &direction, double m1 = 0.1, double m2 = 0.9); 
		double Goldstein(Vector &point, Vector &direction, double m1 = 0.1, double m2 = 0.9); 

		
};

#endif
