


#ifndef F1_H
#define F1_H

class F1 : public virtual Simulateur
{

	public :

		int n;

		F1(int n) {
		this->n = n;
		}

		double getValue(const Vectorr &x) {
			
			double res = 0;
			
			for (int i = 0; i < n; i++)
				res += (i+1)*x(i,0)*x(i,0);

			return res;
		}

		Vectorr getGradient(const Vectorr &x) {

			Vectorr v = Vectorr(n,1); 

			for (int i = 0; i < n; i++)
				v(i,0) =  2*(i+1)*x(i,0);

			return v;
		}

		Matrix getHessian(const Vectorr &x) {
			Matrix H = Matrix(n,n);
				
			firstIndex i;
			secondIndex j;
			H = 2*(i+1)*(i == j);

			return H;
		}
};




#endif
