

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <plplot/plplot.h>
#include <plplot/plstream.h>
#include <math.h>

#include <blitz/array.h>

#include "types.h"
#include "funcs.h"
#include "simulateur.h"
#include "optimiseur.h"
#include "bfgs.h"
#include "newton.h"

#ifdef PL_USE_NAMESPACE
using namespace std;
#endif


using namespace blitz;

class graphe {
public:
    graphe();
    void cmap_init();

private:
    plstream           *pls;

    static const int   XPTS;
    static const int   YPTS;
    static const int   LEVELS;
    static const int   opt[];
    static const PLFLT alt[];
    static const PLFLT az[];

    static const char  *title[];
};


const int   graphe::  XPTS   = 40;
const int   graphe::  YPTS   = 40;
const int   graphe::  LEVELS = 10;

const int   graphe::  opt[]  = { 3, 3 };
const PLFLT graphe::alt[] = { 0.0, 17.0 };
const PLFLT graphe::az[] = { 0.0, 115.0 };

const char  *graphe::title[] = {
    "#frPLplot Example 11 - Alt=33, Az=24, Opt=3",
    "#frPLplot Example 11 - Alt=17, Az=115, Opt=3"
};



void graphe::cmap_init()
{
    PLFLT *i   = new PLFLT[2];
    PLFLT *h   = new PLFLT[2];
    PLFLT *l   = new PLFLT[2];
    PLFLT *s   = new PLFLT[2];
    bool  *rev = new bool[2];

    i[0] = 0.0;       // left boundary
    i[1] = 1.0;       // right boundary

    h[0] = 240;       // blue -> green -> yellow ->
    h[1] = 0;         // -> red

    l[0] = 0.6;
    l[1] = 0.6;

    s[0] = 0.8;
    s[1] = 0.8;

    rev[0] = false;       // interpolate on front side of colour wheel.
    rev[1] = false;       // interpolate on front side of colour wheel.

    pls->scmap1n( 256 );
    pls->scmap1l( false, 2, i, h, l, s, rev );

    delete[] i;
    delete[] h;
    delete[] l;
    delete[] s;
    delete[] rev;
}


graphe::graphe()
{
    int   i, j, k;

    PLFLT *x = new PLFLT[ XPTS ];
    PLFLT *y = new PLFLT[ YPTS ];
    PLFLT **z;
    PLFLT zmin = 1E9, zmax = -1E-9;

    PLFLT xx, yy;
    int   nlevel  = LEVELS;
    PLFLT *clevel = new PLFLT[LEVELS];
    PLFLT step;



    pls = new plstream();

    // Parse and process command line arguments.

    //pls->parseopts( &argc, argv, PL_PARSE_FULL );


    // Initialize plplot.

    pls->init();

    //  pls->Alloc2dGrid(&z, XPTS, YPTS);
    pls->Alloc2dGrid( &z, XPTS, YPTS );

    for ( i = 0; i < XPTS; i++ )
        x[i] = 2. * (PLFLT) ( i - ( XPTS / 2 ) ) / (PLFLT) ( XPTS / 2 );

    for ( j = 0; j < YPTS; j++ ) {
		y[j] = -0.5 + j* (3.0-0.5)/YPTS;
	}

    for ( i = 0; i < XPTS; i++ )
    {
        xx = x[i];
        for ( j = 0; j < YPTS; j++ )
        {
            yy      = y[j];
            //z[i][j] = 3. * ( 1. - xx ) * ( 1. - xx ) * exp( -( xx * xx ) - ( yy + 1. ) * ( yy + 1. ) ) -
                      //10. * ( xx / 5. - pow( (double) xx, 3. ) - pow( (double) yy, 5. ) ) * exp( -xx * xx - yy * yy ) -
                      //1. / 3. * exp( -( xx + 1 ) * ( xx + 1 ) - ( yy * yy ) );

			z[i][j] = (1-xx)*(1-xx) + 100*(yy - xx*xx)*(yy - xx*xx);

            if ( false ) // Jungfraujoch/Interlaken
            {
                if ( z[i][j] < -1. )
                    z[i][j] = -1.;
            }
            if ( zmin > z[i][j] )
                zmin = z[i][j];
            if ( zmax < z[i][j] )
                zmax = z[i][j];
        }
    }

    step = ( zmax - zmin ) / ( nlevel + 1 );
    for ( i = 0; i < nlevel; i++ )
        clevel[i] = zmin + step + step * i;

    cmap_init();
    for ( k = 0; k < 2; k++ )
    {
        for ( i = 0; i < 4; i++ )
        {
            pls->adv( 0 );
            pls->col0( 1 );
            pls->vpor( 0.0, 1.0, 0.0, 0.9 );
            pls->wind( -1.0, 1.0, -1.0, 1.5 );

            pls->w3d( 1.0, 1.0, 2.0, -2.0, 2.0, -0.5, 3.0, zmin, zmax,
                alt[k], az[k] );
            
			pls->box3( "bnstu", "x axis", 0.0, 0,
                "bnstu", "y axis", 0.0, 0,
                "bcdmnstuv", "z axis", 0.0, 4 );

            pls->col0( 2 );

            // wireframe plot
            if ( i == 0 )
                pls->mesh( x, y, z, XPTS, YPTS, opt[k] );

            // magnitude colored wireframe plot
            else if ( i == 1 )
                pls->mesh( x, y, z, XPTS, YPTS, opt[k] | MAG_COLOR );

            // magnitude colored wireframe plot with sides
            else if ( i == 2 )
            {
                pls->plot3d( x, y, z, XPTS, YPTS, opt[k] | MAG_COLOR, true );
            }

            // magnitude colored wireframe plot with base contour
            else if ( i == 3 )
                pls->meshc( x, y, z, XPTS, YPTS, opt[k] | MAG_COLOR | BASE_CONT,
                    clevel, nlevel );


            pls->col0( 3 );
            pls->mtex( "t", 1.0, 0.5, 0.5, title[k] );
        }
    }

    //pls->end();

    pls->Free2dGrid( z, XPTS, YPTS );

    delete[] x;
    delete[] y;
    delete[] clevel;

    delete pls;
}

class Rosenbrock : public virtual Simulateur
{

	public:

		double getValue(const Vector &x) {

			double x0 = x(0,0);
			double x1 = x(1,0);

			return pow((1-x0),2) + 100*pow((x1-x0*x0),2);
		}

		Vector getGradient(const Vector &x) {
			
			Vector v = Vector(2,1); 
			double x0 = x(0,0);
			double x1 = x(1,0);

			v(0,0) = 2*(200*pow(x0,3) - 200*x0*x1 + x0 - 1);
			v(1,0) = 200*(x1 - x0*x0);

			return v;
		}
};

int main () {
	
	Vector x0(2,1);
	x0 = 1, 1.2;

	cout << "MAIN x0 = " << x0;

	Simulateur *rosenbrock = new Rosenbrock();
	
	//BFGS bfgs = BFGS(x0, rosenbrock, 0.00001);
	//bfgs.run();
	
	//Newton newton = Newton(x0, 0.001, rosenbrock, 0.0000000001);
	//newton.run();
    
	graphe *x = new graphe();

    delete x;

}


void testDataAllocation() {
	
	Vector *a = new Vector(1,3); 
	Vector b = Vector(1,3);
	Vector c = Vector(*a);
	Vector d = Vector(b);

	Vector e(1,3), f(1,3);
	Vector *g;
	
	g = new Vector(b);
	
	cout << "\na = " << *a << "\nb = " << b << "\nc = " << c << "\nd= " << d << "\ne = " << e << "\n f = " << f << "\ng = " << *g;

	*a = 1,2,3;
	b = 10,20,30;
	e = Vector(*a);
	f = b;

	cout << "\na = " << *a << "\nb = " << b << "\nc = " << c << "\nd= " << d << "\ne = " << e << "\n f = " << f << "\ng = " << *g;

	*a = -1,-2,-3;
	b = -2,-3,-4;

	cout << "\na = " << *a << "\nb = " << b << "\nc = " << c << "\nd= " << d << "\ne = " << e << "\n f = " << f << "\ng = " << *g;
}


