
#include "logplot.h"

LogPlot::LogPlot(Simulateur *s, list<list<Vectorr>> graphList, char* titre, char **labels, int nlabels, bool logx) {
	
	PLFLT **iteration = new PLFLT*;
	PLFLT ***graphData = new PLFLT**;
	int *nbGraphes = new int;
	int **nbPoints = new int*;

	PLFLT *xmax, *ymin, *ymax;
	ymin = new PLFLT;
	ymax = new PLFLT;
	xmax = new PLFLT;

	generateData(iteration, graphData, nbGraphes, nbPoints, xmax, ymin, ymax, s, graphList, logx);

	plstream *pls = new plstream();
	pls->scolbg(255,255,255);
    pls->init();
	pls->col0(9);

    // Create a labelled box to hold the plot.
	//
    pls->env( 0, *xmax, *ymin, *ymax, 0, 0 );

	if (logx)
		pls->lab( "log(k)", "y=log(f(xk))", titre );
	else
		pls->lab( "k", "y=log(f(xk))", titre );


    // Plot the data that was prepared above.
	
	for(int i = 0; i < *nbGraphes; i++) {
		pls->col0((i+1)%15);
		pls->line( (*nbPoints)[i], *iteration, (*graphData)[i] );
	}
	
	for(int i = 0; i < *nbGraphes; i++) {
		pls->col0((i+1)%15);
		pls->sym( (*nbPoints)[i], *iteration, (*graphData)[i], 900);
	}
	

	if(nlabels != 0) {
		PLFLT *lineWidths = new PLFLT[nlabels];
		PLINT *lineColors = new PLINT[nlabels];
		PLINT *textColors = new PLINT[nlabels];
		PLINT *lineStyles = new PLINT[nlabels];
		PLFLT *symbolScales = new PLFLT[nlabels];
		PLINT *symbolColors = new PLINT[nlabels];
		PLINT *symbolNumbers = new PLINT[nlabels];
		PLINT *opt = new PLINT[nlabels];
		for(int i = 0; i < nlabels; i++) {
			lineColors[i] = (i+1)%15;
			textColors[i] = (i+1)%15;
			lineStyles[i] = 0;
			lineWidths[i] = 1.0;
			symbolScales[i] = 1.0;
			symbolNumbers[i] = 900;
			symbolColors[i] = (i+1)%15;
			opt[i] = PL_LEGEND_LINE;
		}
		
		double w,h;
		pls->scol0a( 15, 32, 32, 32, 0.70 );
		pls->legend( &w, &h,
			PL_LEGEND_BACKGROUND | PL_LEGEND_BOUNDING_BOX,
			PL_POSITION_RIGHT | PL_POSITION_BOTTOM,
			0.0, 0.0, 0.10, 15,
			9, 9, 0, 0,
			nlabels, opt,
			1.0, 1.0, 2.0,
			1., textColors, labels,
			NULL, NULL, NULL, NULL,
			lineColors, lineStyles, lineWidths,
			symbolColors, symbolScales, symbolNumbers,
			NULL );
	}


    // In C++ we don't call plend() to close PLplot library
    // this is handled by the destructor
    delete pls;

}


void LogPlot::generateData(PLFLT **iteration, PLFLT ***graphData, int *nbGraphe, int **nbPoints, PLFLT *xmax, PLFLT *ymin, PLFLT *ymax, Simulateur *s, list<list<Vectorr>> graphList, bool logx) {

	cout << "\ntaille :" << graphList.size() << "\n";
	*nbGraphe = graphList.size();
	*nbPoints = new int[graphList.size()];
	*graphData = new PLFLT*[graphList.size()];

	*ymax = -9999;
	*ymin = 9999;

	unsigned int max = 0;

	int i = 0;
	for(list<list<Vectorr>>::iterator graphe = graphList.begin(); graphe != graphList.end(); graphe++) {
		(*nbPoints)[i] = graphe->size();
		(*graphData)[i] = new PLFLT[graphe->size()];

		if (max < graphe->size())
			max = graphe->size();
		
		int j = 0;
		for(list<Vectorr>::iterator pt = graphe->begin(); pt != graphe->end(); pt++) {

			(*graphData)[i][j] = (PLFLT) log10(s->getValue(*pt));

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
		if (logx)
			(*iteration)[i] = (PLFLT) log10((i+1));
		else
			(*iteration)[i] = (PLFLT) (i+1);
	}
	
	if (logx)
		*xmax = log10(max);
	else
		*xmax = max;

}

