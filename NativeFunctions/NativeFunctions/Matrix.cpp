#include "Matrix.h"
#include <iostream>
#include <iterator>
#include <windows.h>

using namespace std;

void multiply(jdouble* matrixA, jdouble* matrixB, jdouble* matrixC, jint n, jint m, jint p) {
	int indexA = 0;
	int indexB = 0;
	int indexC = 0;

	for (jint iN = 0; iN < n; iN++)
	  {
		  for (jint iP = 0; iP < p; iP++)
		  {
			  jdouble sum = 0.0;
			  for (jint iM = 0; iM < m; iM++) {
				  sum+=matrixA[indexA+iM]*matrixB[indexB+iP];
				  indexB += p;
			  }
			  indexB = 0;
			  matrixC[indexC+iP]=sum;
		  }
		  indexA += m;
		  indexC += p;
	  }
}

JNIEXPORT void JNICALL Java_Matrix_multiplyC
  (JNIEnv * env, jobject, jdoubleArray arrayA, jdoubleArray arrayB, jdoubleArray arrayC, jint n, jint m, jint p){
	jboolean isCopyA, isCopyB, isCopyC;

	jdouble* matrixA = env->GetDoubleArrayElements(arrayA,&isCopyA);
	jdouble* matrixB = env->GetDoubleArrayElements(arrayB,&isCopyB);
	jdouble* matrixC = env->GetDoubleArrayElements(arrayC,&isCopyC);

	multiply(matrixA, matrixB, matrixC, n,m,p);

	env->ReleaseDoubleArrayElements(arrayA, matrixA, JNI_ABORT);
	env->ReleaseDoubleArrayElements(arrayB, matrixB, JNI_ABORT);
	env->ReleaseDoubleArrayElements(arrayC, matrixC, 0);
}

JNIEXPORT void JNICALL Java_Matrix_powerC
  (JNIEnv * env , jobject, jdoubleArray arrayM, jdoubleArray arrayR, jint m, jint k){
	jboolean isCopyM, isCopyR;

	jdouble* matrixM = env->GetDoubleArrayElements(arrayM,&isCopyM);
	jdouble* matrixR = env->GetDoubleArrayElements(arrayR,&isCopyR);
	jdouble* matrixTemp = new jdouble[m*m];
	jdouble* matrixTemp2 = new jdouble[m*m];

	std::copy(matrixM, matrixM + (m*m), stdext::checked_array_iterator<jdouble*>( matrixTemp, m*m ));

	for (jint i = 0; i < k-1; i++) {
		multiply(matrixTemp, matrixM, matrixTemp2, m,m,m);
		jdouble* tempPointer = matrixTemp;
		matrixTemp = matrixTemp2;
		matrixTemp2 = tempPointer;
		tempPointer=nullptr;
	}

	std::copy(matrixTemp, matrixTemp + (m*m), stdext::checked_array_iterator<jdouble*>( matrixR, m*m ));

	delete[] matrixTemp;
	delete[] matrixTemp2;

	env->ReleaseDoubleArrayElements(arrayM, matrixM, JNI_ABORT);
	env->ReleaseDoubleArrayElements(arrayR, matrixR, 0);
}