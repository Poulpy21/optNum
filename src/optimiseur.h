
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

		virtual bool run(Vector x0, double epsilon, int nbIterationsMax) = 0;
		
		list<Vector> getPoints();
		Vector getLastPoint();

		int getNbIterations();
		double getDuree();

	
	protected:
		Simulateur *s;
		int nbIterations;
		double duree;

		list<Vector> *points;
		
		double Wolfe(Vector &point, Vector &direction, double m1 = 0.1, double m2 = 0.9); 
};

#endif
