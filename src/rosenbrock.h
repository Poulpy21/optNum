

#ifndef ROSENBROCK_H
#define ROSENBROCK_H

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




#endif
