

#include "plot.h"

plot::plot(Simulateur *s, bool logDraw, int ptx, int pty, int nlevel, float xmin, float xmax, float ymin, float ymax, list<Vector> optimPts, char *titre, int nbIterations) {

	this->s = s;
	this->logDraw = logDraw;

	this->ptx = ptx;
	this->pty = pty;
	this->pt = ptx*pty;

	this->nlevel = nlevel;

	this->xmin = (PLFLT) xmin;
	this->xmax = (PLFLT) xmax;
	this->ymin = (PLFLT) ymin;
	this->ymax = (PLFLT) ymax;

	PLFLT lzm, lzM;
	PLFLT *clevel;

	plstream *pls = new plstream();

	this->x = new PLFLT[pt];
	this->y = new PLFLT[pt];
	pls->Alloc2dGrid(&z,ptx, pty);

	generateOptimPoints(optimPts);

	generateData();
	averageNan();
	computeMinMax();


	//colormap init
	PLFLT b[2], h[2], l[2], p[2];

	b[0] = 0.0;         // left boundary
	b[1] = 1.0;         // right boundary

	h[0] = 240;         // blue -> green -> yellow ->
	h[1] = 0;           // -> red

	l[0] = 0.6;
	l[1] = 0.6;

	p[0] = 0.8;
	p[1] = 0.8;

	pls->scmap1n( 256 );
	pls->scmap1l( false, 2, b, h, l, p);
	/////////////:
	
	pls->scolbg(255,255,255);
	pls->init();
	pls->col0(9);



	lzm = zmin;
	lzM = zmax;

	lzm = lzm - 0.01;
	lzM = lzM + 0.01;

	clevel = new PLFLT[nlevel];
	for ( i = 0; i < nlevel; i++ )
		clevel[i] = lzm + ( lzM - lzm ) / ( nlevel - 1 ) * i;

	pls->env0( xmin, xmax, ymin, ymax, 2, 0 );
	pls->col0( 9 );
	pls->lab( "X", "Y", titre );
	pls->shades( z, ptx, pty, NULL, xmin, xmax, ymin, ymax,
			clevel, nlevel, 1.0, 0, 1.0, pls->fill, true, NULL, NULL );

	//tracé des points
	pls->col0(10);
	pls->sym(ptopt, xopt, yopt, 900);
	
	pls->col0(1);
	pls->line(ptopt, xopt, yopt );

	char buffer[50];
	pls->col0(9);
	sprintf(buffer, "Nombre d'iterations : %i", nbIterations);
	pls->ptex( xmin + (xmax-xmin)/2, 0.9*ymax, 1,0, 0.5, buffer);
	
	delete pls;
}

void plot::generateData() {

	Vector v = Vector(2,1); 

	PLFLT *xi, *yi;

	xi = x;
	yi = y;

	for (i = 0; i < ptx; i++) {
		for (j = 0; j < pty; j++) {
			*xi = xmin + (xmax - xmin) * i / ptx;
			*yi = ymin + (ymax - ymin) * j / pty;

			v(0,0) = *xi;
			v(1,0) = *yi;

			if (!logDraw)
				z[i][j] = (PLFLT) s->getValue(v);
			else
				z[i][j] = (PLFLT) log(s->getValue(v));


			if(i == 0 && j == 0) {
				zmin = z[i][j];
				zmax = z[i][j];
			}

			if(z[i][j] > zmax)
				zmax = z[i][j];
			else if(z[i][j] < zmin)
				zmin = z[i][j];

			xi++; yi++;
		}
	}
}


void plot::averageNan() {

	int   ii, jj;
	PLFLT dist, d;

	for ( i = 0; i < ptx; i++ )
	{
		for ( j = 0; j < pty; j++ )
		{
			if ( std::isnan( z[i][j] ) || std::isinf( z[i][j] ) ) // average (IDW) over the 8 neighbors

			{
				z[i][j] = 0.; dist = 0.;

				for ( ii = i - 1; ii <= i + 1 && ii < ptx; ii++ )
				{
					for ( jj = j - 1; jj <= j + 1 && jj < pty; jj++ )
					{
						if ( ii >= 0 && jj >= 0 && !std::isnan( z[ii][jj] ) && !std::isinf( z[i][j] ) )
						{
							d         = ( abs( ii - i ) + abs( jj - j ) ) == 1 ? 1. : 1.4142;
							z[i][j] += z[ii][jj] / ( d * d );
							dist     += d;
						}
					}
				}
				if ( dist != 0. )
					z[i][j] /= dist;
				else
					z[i][j] = zmin;
			}

		}
	}
}

void plot::generateOptimPoints(list<Vector> pointList) {

	PLFLT *xi, *yi;
	Vector v = Vector(2,1);

	ptopt = pointList.size();
	xi = xopt = new PLFLT[ptopt];
	yi = yopt = new PLFLT[ptopt];
	
	for(list<Vector>::iterator it = pointList.begin(); it != pointList.end(); it++) {
		v = *it;

		*xi = (PLFLT) v(0,0);
		*yi = (PLFLT) v(1,0);

		xi++; yi++;
	}


}


void plot::computeMinMax() {

	zmin = z[0][0];
	zmax = z[0][0];

	for (i = 0; i < ptx; i++) {
		for (j = 0; j < pty; j++) {
			zmin = z[i][j] < zmin ? z[i][j] : zmin;
			zmax= z[i][j] > zmax ? z[i][j] : zmax;
		}
	}

	cout << "\n\n\nMINMAX min = " << zmin << " max = " << zmax;
}
