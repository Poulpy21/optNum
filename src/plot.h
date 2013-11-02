

#include <list>
#include <plplot/plplot.h>
#include <plplot/plstream.h>
#include <blitz/array.h>
#include <queue>

#include "simulateur.h"
#include "types.h"

#ifndef PLOT_H
#define PLOT_H

#ifdef PL_USE_NAMESPACE
using namespace std;
#endif

class plot 
{
	
	public:
		plot(Simulateur *s, bool logDraw, int ptx, int pty, int nlevel, float xmin, float xmax, float ymin, float ymax, list<Vector> optimPts, char* titre, int nbIterations);

	private:
		Simulateur *s;
		bool logDraw;

		int ptx, pty, pt, ptopt;
		int i,j;
		
		int nlevel;

		PLFLT xmin, xmax, ymin, ymax, zmin, zmax;
		PLFLT *x, *y, **z;
		
		PLFLT *xopt, *yopt;

		void generateData();
		void averageNan();
		void computeMinMax();
		
		void generateOptimPoints(list<Vector> pointList);
};

	
#endif
