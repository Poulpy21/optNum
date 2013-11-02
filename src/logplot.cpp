
#include "logplot.h"

LogPlot::LogPlot(Simulateur *s, list<list<Vector>> graphList, char* titre) {
	
	PLFLT **iteration = new PLFLT*;
	PLFLT ***graphData = new PLFLT**;
	int *nbGraphes = new int;
	int **nbPoints = new int*;

	PLFLT *xmax, *ymin, *ymax;
	ymin = new PLFLT;
	ymax = new PLFLT;
	xmax = new PLFLT;

	generateData(iteration, graphData, nbGraphes, nbPoints, xmax, ymin, ymax, s, graphList);

	plstream *pls = new plstream();
	pls->scolbg(255,255,255);
    pls->init();
	pls->col0(9);

    // Create a labelled box to hold the plot.
	//
    pls->env( 0, *xmax, *ymin, *ymax, 0, 0 );
    pls->lab( "xk", "y=log(f(xk))", titre );

    // Plot the data that was prepared above.
	
	for(int i = 0; i < *nbGraphes; i++) {
		pls->col0(i%15);
		pls->line( (*nbPoints)[i], *iteration, (*graphData)[i] );
	}
	
	for(int i = 0; i < *nbGraphes; i++) {
		pls->col0(i%15);
		pls->sym( (*nbPoints)[i], *iteration, (*graphData)[i], 900 );
	}


    // In C++ we don't call plend() to close PLplot library
    // this is handled by the destructor
    delete pls;

}


void LogPlot::generateData(PLFLT **iteration, PLFLT ***graphData, int *nbGraphe, int **nbPoints, PLFLT *xmax, PLFLT *ymin, PLFLT *ymax, Simulateur *s, list<list<Vector>> graphList) {

	cout << "\ntaille :" << graphList.size() << "\n";
	*nbGraphe = graphList.size();
	*nbPoints = new int[graphList.size()];
	*graphData = new PLFLT*[graphList.size()];

	*ymax = -9999;
	*ymin = 9999;

	unsigned int max = 0;

	int i = 0;
	for(list<list<Vector>>::iterator graphe = graphList.begin(); graphe != graphList.end(); graphe++) {
		(*nbPoints)[i] = graphe->size();
		(*graphData)[i] = new PLFLT[graphe->size()];

		if (max < graphe->size())
			max = graphe->size();
		
		int j = 0;
		for(list<Vector>::iterator pt = graphe->begin(); pt != graphe->end(); pt++) {
			(*graphData)[i][j] = (PLFLT) log(s->getValue(*pt));

			if ((*graphData)[i][j] > *ymax)
				*ymax = (*graphData)[i][j];
			
			if ((*graphData)[i][j] < *ymin && !std::isinf((*graphData)[i][j]))
				*ymin = (*graphData)[i][j];

			j++;
		}
		i++;
	}

	*iteration = new PLFLT[max];
	for (unsigned int i = 0; i < max; i++) {
		(*iteration)[i] = (PLFLT) (i+1);
	}

	*xmax = max;
}

