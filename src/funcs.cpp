
#include "funcs.h"

void arrayInfo(const Matrix &a) {
	
	cout << "\na = " << a;
	cout << "\nShape : " << a.shape();
	cout << "\nBase : " << a.base();
	cout << "\nDimensions : " << a.dimensions();
	cout << "\nRank : " << a.rank();
	cout << "\nSize : " << a.size();
	cout << "\nRows : " << a.rows();
	cout << "\nColumns : " << a.columns();

}



Matrix mult(const Matrix &A, const Matrix &B) {
	
	if(A.columns() != B.rows()) {
		cout << "\n\nProblème de dimensions pour la multiplication : \n\t" << A << "\n\t" << B;
		assert(false);
	}

	Matrix C = Matrix(A.rows(), B.cols());

	firstIndex i;
	secondIndex j;
	thirdIndex k;
	
	C = sum((A)(i,k) * (B)(k,j), k);

	return C;
}


double scalarProduct(const Vector &v1, const Vector &v2) {
	
	Matrix m = Matrix(1,1);
	m = mult(v1,v2);
	
	return m(0,0);
}

Vector transpose(const Vector v) {

	return v.transpose(1,0);
}
