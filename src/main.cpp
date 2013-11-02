
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

#ifdef PL_USE_NAMESPACE
using namespace std;
#endif

using namespace blitz;


void bench(int nbPoints);
void graphicBench();
bool comparePoints(Vector p1, Vector p2, double epsilon);
list<Vector> generateUniformPoints(double xmin, double xmax, double ymin, double ymax, int nbPoints);

int main () {

	rand_init();
	
	//graphicBench();
	bench(10);

	return 0;
}

void bench(int nbPoints) {
	

	list<list<Vector>> *graphes = new list<list<Vector>>();

	list<Vector> pts;
	const double epsilon = 10e-9;
	const double epsilonPoint = 10e-2;
	const int nbIterationsMax = 10e6;

	Vector minPoint = Vector(2,1);

	Simulateur *rosenbrock = new Rosenbrock();
	minPoint = 1.0, 1.0;

	//Optimiseur *opt = new Newton(rosenbrock);
	Optimiseur *opt = new Gradient(rosenbrock, 0.001);

	pts = generateUniformPoints(-1,2,-1,2,nbPoints);
	long nbIterations = 0, nbConvergence = 0;
	double tempsTotal = 0, tempsConvergent = 0;

	for (std::list<Vector>::iterator it = pts.begin(); it != pts.end(); it++) {

		if(opt->run(*it, epsilon, nbIterationsMax) && comparePoints(opt->getLastPoint(), minPoint, epsilonPoint)) {
			graphes->push_back(opt->getPoints());
			nbIterations += opt->getNbIterations();
			tempsConvergent += opt->getDuree();
			nbConvergence++;
		}
		
		tempsTotal += opt->getDuree();
	}

	cout << "\n" << nbConvergence << " convergences sur " << nbPoints << " points.";
	cout << "\nTemps moyen d'execution " << tempsTotal/nbPoints << " ms";
	cout << "\nTemps moyen d'excecution convergente : " << tempsConvergent/(nbPoints) << " ms";

	LogPlot *plot = new LogPlot(rosenbrock, *graphes, "lol");
}

void graphicBench() {

	const double epsilon = 10e-9;
	const int nbIterationsMax = 10e6;
	const int nbPoints = 1000;

	Vector *x0;
	Simulateur *sim;
	Optimiseur *opt;
	char titre[100];
	plot *graph;
	
	int fonction = 3 ;

	switch(fonction) {	
		case 1: {
			
			sim = new Rosenbrock();
			x0 = new Vector(2,1);
			*x0 = -0.9, 1.2;

			opt = new Gradient(sim, 10e-4);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du gradient a pas constant  t=10e-4"); 
			graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			opt = new Gradient(sim, 10e-6);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du Gradient a pas constant  t=10e-6"); 
			graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			opt = new Gradient(sim, -1);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du Gradient avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			//opt = new BFGS(sim);
			//opt->run(*x0, epsilon, nbIterationsMax);
			//sprintf(titre, "Methode BFGS"); 
			//graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());

			opt = new Newton(sim);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton"); 
			graph = new plot(sim, true, nbPoints,nbPoints, 20, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;
			
			opt = new Newton(sim, true);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, true, nbPoints,nbPoints, 50, -1.0,2.0,-1.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			break;
		}

		case 2: {
			
			sim = new F1(2);
			x0 = new Vector(2,1);
			*x0 = 1.5, 1.5;

			opt = new Gradient(sim, 10e-4);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du gradient a pas constant  t=10e-4"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			opt = new Gradient(sim, 10e-6);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du Gradient a pas constant  t=10e-6"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 20, -2.0,2.0,-2.0,2.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

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
			x0 = new Vector(2,1);
			*x0 = -2.5, -3.0;

			opt = new Gradient(sim, 10e-4);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du gradient a pas constant  t=10e-4"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			opt = new Gradient(sim, 10e-6);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode du Gradient a pas constant  t=10e-6"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

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

			opt = new Newton(sim);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;
			
			opt = new Newton(sim, true);
			opt->run(*x0, epsilon, nbIterationsMax);
			sprintf(titre, "Methode de Newton avec recherche lineaire de Wolfe"); 
			graph = new plot(sim, false, nbPoints,nbPoints, 50, -5.0,5.0,-5.0,5.0, opt->getPoints(), titre, opt->getNbIterations());
			delete graph;

			break;
		}
	}
}

list<Vector> generateUniformPoints(double xmin, double xmax, double ymin, double ymax, int nbPoints) {

	Vector *xx;
	double x, y;
	list<Vector> pts;

	for (int i = 0; i < nbPoints; i++) {
		x = random_double(xmin,xmax);
		y = random_double(ymin,ymax);

		xx = new Vector(2,1);
		*xx = x, y;

		pts.push_back(*xx);
	}

	return pts;
}

bool comparePoints(Vector p1, Vector p2, double epsilon) {

	assert(p1.size() == p2.size());

	int n = p1.size();

	for (int i = 0; i < n; i++) {
		if (! (abs(p1(i,0) - p2(i,0)) < epsilon))
			return false;
	}

	return true;
}

