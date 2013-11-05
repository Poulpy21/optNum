
#include <list>
#include <plplot/plplot.h>
#include <plplot/plstream.h>
#include <blitz/array.h>
#include <queue>
#include "simulateur.h"
#include "types.h"

#ifndef LOGPLOT_H
#define LOGPLOT_H

class LogPlot 
{
	
	public:
		LogPlot(Simulateur *s, list<list<Vectorr>> graphList, char* titre, char **label, int nlabel, bool logx);


	private:
		void generateData(PLFLT **iteration, PLFLT ***graphData, int *nbGraphe, int **nbPoints, PLFLT *xmax, PLFLT *ymin, PLFLT *ymax, Simulateur *s, list<list<Vectorr>> graphList, bool logx);
};

	
#endif
