
#include "funcs.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>

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

Matrix inverseMatrix(const Matrix &M) {
	
	TinyVector<int,2> dim = M.shape();
	unsigned int n = dim(0);

	if (dim(0) != dim(1)) {
		cout << "Inversion d'une matrice non carrée !";
		assert(false);
	}

	Matrix W = Matrix(dim);

	int s;
	gsl_matrix m = gsl_matrix_view_array((double *)M.data(), n, n).matrix;
	gsl_matrix w = gsl_matrix_view_array((double *)W.data(), n, n).matrix;

	gsl_permutation *perm = gsl_permutation_alloc (n);
	gsl_linalg_LU_decomp (&m, perm, &s);
	gsl_linalg_LU_invert (&m, perm, &w);

	return W;
}

