#include "Matrix.h"
#include <iostream>
#include <iterator>
#include <windows.h>

using namespace std;

void multiply(jdouble* matrixA, jdouble* matrixB, jdouble* matrixC, jint n, jint m, jint p) {
	 for (jint iN = 0; iN < n; iN++)
	  {
		  for (jint iP = 0; iP < p; iP++)
		  {
			  jdouble sum = 0.0;
			  for (jint iM = 0; iM < m; iM++)
				  sum+=matrixA[iN*m+iM]*matrixB[iM*p+iP];
			  matrixC[iN*p+iP]=sum;
		  }
	  }
}

JNIEXPORT void JNICALL Java_Matrix_multiplyC
  (JNIEnv * env, jobject, jdoubleArray arrayA, jdoubleArray arrayB, jdoubleArray arrayC, jint n, jint m, jint p){

	jdouble* matrixA = env->GetDoubleArrayElements(arrayA,JNI_FALSE);
	jdouble* matrixB = env->GetDoubleArrayElements(arrayB,JNI_FALSE);
	jdouble* matrixC = env->GetDoubleArrayElements(arrayC,JNI_FALSE);

	multiply(matrixA, matrixB, matrixC,n,m,p);

	env->ReleaseDoubleArrayElements(arrayA, matrixA, JNI_ABORT);
	env->ReleaseDoubleArrayElements(arrayB, matrixB, JNI_ABORT);
	env->ReleaseDoubleArrayElements(arrayC, matrixC, 0);
	 
}

JNIEXPORT void JNICALL Java_Matrix_powerC
  (JNIEnv * env , jobject, jdoubleArray arrayM, jdoubleArray arrayR, jint m, jint k){

	jdouble* matrixM = env->GetDoubleArrayElements(arrayM,JNI_FALSE);
	jdouble* matrixR = env->GetDoubleArrayElements(arrayR,JNI_FALSE);

	if (k<=1)
		std::copy(matrixM, matrixM + (m*m), stdext::checked_array_iterator<jdouble*>( matrixR, m*m ));
	else {
		for (jint i = 0; i < k-1; i++) {
			multiply(matrixM, matrixM, matrixR,m,m,m);
			std::copy(matrixR, matrixR + (m*m), stdext::checked_array_iterator<jdouble*>( matrixM, m*m ));
		}
	}

	env->ReleaseDoubleArrayElements(arrayM, matrixM, JNI_ABORT);
	env->ReleaseDoubleArrayElements(arrayR, matrixR, 0);

}