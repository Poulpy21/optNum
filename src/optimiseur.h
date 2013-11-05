
#include <list>

#include "simulateur.h"
#include "types.h"


#ifndef OPTIMISEUR_H
#define OPTIMISEUR_H

using namespace std;

class Optimiseur 

{
	
	public:
		Optimiseur(Simulateur *s);

		virtual bool run(Vectorr x0, double epsilon, int nbIterationsMax) = 0;
		
		list<Vectorr> getPoints();
		Vectorr getLastPoint();

		int getNbIterations();
		double getDuree();

	
	protected:
		Simulateur *s;
		int nbIterations;
		double duree;

		list<Vectorr> *points;
		
		double Wolfe(Vectorr &point, Vectorr &direction, double m1 = 0.1, double m2 = 0.9); 
};

#endif
