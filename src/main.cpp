
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <list>

#include <blitz/array.h>

#include "random2.h"
#include "types.h"
#include "funcs.h"
#include "plot.h"
#include "logplot.h"

#include "simulateur.h"
#include "optimiseur.h"

#include "gradient.h"
#include "bfgs.h"
#include "newton.h"

#include "himmelblau.h"
#include "rosenbrock.h"
#include "f1.h"

using namespace blitz;


void bench(int nbPoints);
void logbench();
void graphicBench();
bool comparePoints(Vectorr p1, Vectorr p2, double epsilon);
list<Vectorr> generateUniformPoints(double xmin, double xmax, double ymin, double ymax, int nbPoints);

int main () {

	rand_init();
	
	//graphicBench();
	logbench();
	//bench(1000);

	return 0;
}

void bench(int nbPoints) {
	list<list<Vectorr>> *graphes = new list<list<Vectorr>>();

	list<Vectorr> pts;
	const double epsilon = 10e-6;
	const double epsilonPoint = 10e-3;
	const int nbIterationsMax = 10e6;

	Vectorr minPoint = Vectorr(2,1);

	Simulateur *rosenbrock = new Rosenbrock();
	minPoint = 1.0, 1.0;

	//Optimiseur *opt = new Newton(rosenbrock);
	Optimiseur **opts = new Optimiseur*[6];
	Optimiseur *opt;
	opts[0] = new Gradient(rosenbrock, 1);
	opts[1] = new Gradient(rosenbrock, 10e-3);
	opts[2] = new Gradient(rosenbrock, 10e-4);
	opts[3] = new Gradient(rosenbrock, -1);
	opts[4] = new Newton(rosenbrock);
	opts[5] = new Newton(rosenbrock, true);

	char **noms = new char*[6];
	noms[0] = "Methode du gradient a pas constant t = 1";
	noms[1] = "Methode du gradient a pas constant t = 10e-3";
	noms[2] = "Methode du gradient a pas constant t = 10e-4";
	noms[3] = "Methode du gradient avec Wolfe";
	noms[4] = "Methode de newton";
	noms[5] = "Methode de newton avec Wolfe";

	
	pts = generateUniformPoints(-1,2,-1,2,nbPoints);

	//for (int i = 0; i < 6; i++) {

		//long nbIterations = 0, nbConvergence = 0;
		//double tempsTotal = 0, tempsConvergent = 0;
		//opt = opts[i];

		//delete graphes;
		//graphes = new list<list<Vectorr>>();
		
		//int j = 0;
		//

		opt = opts[2];
		for (std::list<Vectorr>::iterator it = pts.begin(); it != pts.end(); it++) {
			
			opt->run(*it, epsilon, nbIterationsMax);
			//if(opt->run(*it, epsilon, nbIterationsMax) && comparePoints(opt->getLastPoint(), minPoint, epsilonPoint)) {
				//if(j% 100 == 0)
					//graphes->push_back(opt->getPoints());
				//nbIterations += opt->getNbIterations();
				//tempsConvergent += opt->getDuree();
				//nbConvergence++;
			//}
			
			//tempsTotal += opt->getDuree();
			//j++;
		}
		
		//cout << "\n\n" << noms[i];
		//cout << "\n" << nbConvergence << " convergences sur " << nbPoints << " points.";
		//cout << "\nTemps moyen d'execution " << tempsTotal/nbPoints << " ms";

		//if (nbConvergence != 0) {
			//cout << "\nTemps moyen d'excecution convergente : " << tempsConvergent/(nbPoints) << " ms";
			//cout << "\nNombre moyen d'iterations convergente " << nbIterations/nbConvergence << " ms\n";
		//}
		
		//if (i >= 2) {
			//LogPlot *plot = new LogPlot(rosenbrock, *graphes, noms[i], NULL, 0, (i<4));
		//}
	//}

}

void graphicBench() {

	const double epsilon = 10e-9;
	const int nbIterationsMax = 10e6;
	const int nbPoints = 1000;

	Vectorr *x0;
	Simulateur *sim;
	Optimiseur *opt;
	char titre[100];
	plot *graph;
	
	int fonction = 3 ;

	switch(fonction) {	
		case 1: {
			
			sim = new Rosenbrock();
			x0 = new Vectorr(2,1);
			*x0 = -0.2, 1.2;

			//opt = new Gradient(sim, 10e-4);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode du gradient a pas constant  t=10e-4"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			//opt = new Gradient(sim, 0);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode du Gradient a pas constant  t=10e-6"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			//opt = new Gradient(sim, -1);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode du Gradient avec recherche lineaire de Wolfe"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			//opt = new BFGS(sim);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode BFGS"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());

			//opt = new Newton(sim);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode de Newton"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;
			
			//opt = new Newton(sim, true);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode de Newton avec recherche lineaire de Wolfe"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 50, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			break;
		}

		case 2: {
			
			sim = new F1(2);
			x0 = new Vectorr(2,1);
			*x0 = 1.8, 1.8;

			opt = new Gradient(sim, 10e-4);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du gradient a pas constant  t=10e-4"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			//opt = new Gradient(sim, 10e-6);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode du Gradient a pas constant  t=10e-6"); 
			//graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			opt = new Gradient(sim, -1);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du Gradient avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			//opt = new BFGS(sim);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode BFGS"); 
			//graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			opt = new Newton(sim);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;
			
			opt = new Newton(sim, true);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;
			
			break;
		}

		case 3: {
			sim = new Himmelblau();
			x0 = new Vectorr(2,1);
			*x0 = 1.0, 1.0;

			//opt = new Gradient(sim, 10e-4);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode du gradient a pas constant  t=10e-4"); 
			//graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			//opt = new Gradient(sim, 10e-6);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode du Gradient a pas constant  t=10e-6"); 
			//graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			opt = new Gradient(sim, -1);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du Gradient avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			//opt = new BFGS(sim);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode BFGS"); 
			//graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;

			//opt = new Newton(sim);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode de Newton"); 
			//graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			//delete graph;
			
			opt = new Newton(sim, true);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;
			
			*x0 = 0.0, 0.0;
			opt = new Newton(sim);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			

			break;
		}
	}
}

list<Vectorr> generateUniformPoints(double xmin, double xmax, double ymin, double ymax, int nbPoints) {

	Vectorr *xx;
	double x, y;
	list<Vectorr> pts;

	for (int i = 0; i < nbPoints; i++) {
		x = random_double(xmin,xmax);
		y = random_double(ymin,ymax);

		xx = new Vectorr(2,1);
		*xx = x, y;

		pts.push_back(*xx);
	}

	return pts;
}

bool comparePoints(Vectorr p1, Vectorr p2, double epsilon) {

	assert(p1.size() == p2.size());

	int n = p1.size();

	for (int i = 0; i < n; i++) {
		if (! (abs(p1(i,0) - p2(i,0)) < epsilon))
			return false;
	}

	return true;
}


void logbench() {
	list<list<Vectorr>> *graphes = new list<list<Vectorr>>();

	list<Vectorr> pts;
	const double epsilon = 10e-6;
	const int nbIterationsMax = 10e6;

	Vectorr minPoint = Vectorr(2,1);

	Simulateur *rosenbrock = new Rosenbrock();
	minPoint = 1.0, 1.0;

	//Optimiseur *opt = new Newton(rosenbrock);
	Optimiseur **opts = new Optimiseur*[6];
	Optimiseur *opt;
	opts[2] = new Gradient(rosenbrock, 10e-4);
	opts[3] = new Gradient(rosenbrock, -1);
	opts[4] = new Newton(rosenbrock);
	opts[5] = new Newton(rosenbrock, true);
	
	char **noms = new char*[6];
	noms[0] = "Gradient a pas constant";
	noms[1] = "Gradient a pas constant";
	noms[2] = "Gradient a pas constant";
	noms[3] = "Gradient avec Wolfe";
	noms[4] = "Newton";
	noms[5] = "Newton avec Wolfe";

	Vectorr *pt = new Vectorr(2,1); 
	*pt = -0.2, 1.2; 
	pts.push_back(*pt);

	for (int i = 2; i < 6; i++) {
		opt = opts[i];

		for (std::list<Vectorr>::iterator it = pts.begin(); it != pts.end(); it++) {

			opt->run(*it, epsilon, nbIterationsMax);
			graphes->push_back(opt->getPoints());
		}
	}
			LogPlot *plot = new LogPlot(rosenbrock, *graphes, "Comparaisons des méthodes pour un point", &(noms[2]), 4, true);
}
