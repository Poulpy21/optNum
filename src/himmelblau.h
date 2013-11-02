
#ifndef HIMMELBLAU_H
#define HIMMELBLAU_H


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

#endif
