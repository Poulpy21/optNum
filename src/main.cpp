#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <plplot/plplot.h>
#include <plplot/plstream.h>
#include <math.h>
#include <queue>

#include <blitz/array.h>

#include "types.h"
#include "funcs.h"
#include "simulateur.h"
#include "optimiseur.h"
#include "plot.h"

#include "bfgs.h"
#include "newton.h"
#include "gradient.h"

#ifdef PL_USE_NAMESPACE
using namespace std;
#endif

using namespace blitz;

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
		
		Matrix getHessian(const Vector &x) {
			Matrix H = Matrix(2,2);

			double x0 = x(0,0);
			double x1 = x(1,0);

			H(0,0) = 2*(600*x0*x0 - 200*x1 + 1);
			H(0,1) = -400*x0; 
			H(1,0) = -400*x0;
			H(1,1) =  200;

			return H;
		}
};

class Himmelblau : public virtual Simulateur
{

	public:

		double getValue(const Vector &x) {

			double x0 = x(0,0);
			double x1 = x(1,0);

			return pow((x0*x0 + x1 - 11),2) + pow((x0 + x1*x1 -7),2);
		}

		Vector getGradient(const Vector &x) {

			Vector v = Vector(2,1); 
			double x0 = x(0,0);
			double x1 = x(1,0);

			v(0,0) = x0*(4*x0*x0 - 42) + x1*(4*x0 + 2*x1) - 14;	 
			v(1,0) = x0*(2*x0 + 4*x1) + x1*(4*x1*x1 -26) - 22;

			return v;
		}
		
		Matrix getHessian(const Vector &x) {
			Matrix H = Matrix(2,2);

			double x0 = x(0,0);
			double x1 = x(1,0);

			H(0,0) = 2*(6*x0*x0 + 4*x1 -21);
			H(0,1) = 4*(x0 + x1);
			H(1,0) = 4*(x0 + x1);
			H(1,1) = 2*(2*x0 + 6*x1*x1 -13);

			return H;
		}
};

int main () {

	Vector x0(2,1);
	x0 = -0.5, -0.5;

	Simulateur *rosenbrock = new Rosenbrock();
	Simulateur *himmelblau = new Himmelblau();

	//Newton newton = Newton(x0, 1, rosenbrock, 0.00000001);
	//Newton newton = Newton(x0, 1, himmelblau, 10e-12);
	//newton.run();
	//plot *test = new plot(rosenbrock, true, 1000,1000, 20, -1.0,2.0,-1.0,2.0, newton.getPoints());
	//plot *test = new plot(himmelblau, true, 100,100, 20, -6.0,6.0,-6.0,6.0, newton.getPoints());
	
	//BFGS bfgs = BFGS(x0, rosenbrock, 10e-12);
	//bfgs.run();
	//plot *test = new plot(logRosenbrock, 100,100, 20, -1.0,2.0,-1.0,2.0, bfgs.getPoints());
	
	Gradient gradient = Gradient(x0, 0.01, rosenbrock, 10e-12);
	gradient.run();
	//plot *test = new plot(rosenbrock, true, 1000,1000, 20, -1.0,2.0,-1.0,2.0, gradient.getPoints());

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


