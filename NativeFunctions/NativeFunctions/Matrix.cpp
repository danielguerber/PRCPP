#include "Matrix.h"
#include <iostream>
#include <iterator>
#include <windows.h>

using namespace std;

jdouble* multiply(jdouble* matrixA, jdouble* matrixB, jint n, jint m, jint p) {
	jdouble* matrixC = new jdouble[n*p];

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

	 return matrixC;
}

JNIEXPORT void JNICALL Java_Matrix_multiplyC
  (JNIEnv * env, jobject, jdoubleArray arrayA, jdoubleArray arrayB, jdoubleArray arrayC, jint n, jint m, jint p){
	jboolean isCopyA, isCopyB, isCopyC;

	jdouble* matrixA = env->GetDoubleArrayElements(arrayA,&isCopyA);
	jdouble* matrixB = env->GetDoubleArrayElements(arrayB,&isCopyB);
	jdouble* matrixC = env->GetDoubleArrayElements(arrayC,&isCopyC);

	jdouble* matrixR = multiply(matrixA, matrixB,n,m,p);

	std::copy(matrixR, matrixR + (n*p), stdext::checked_array_iterator<jdouble*>( matrixC, m*m ));

	if (isCopyA==JNI_TRUE)
		env->ReleaseDoubleArrayElements(arrayA, matrixA, JNI_ABORT);
	if (isCopyB==JNI_TRUE)
		env->ReleaseDoubleArrayElements(arrayB, matrixB, JNI_ABORT);
	if (isCopyC==JNI_TRUE)
		env->ReleaseDoubleArrayElements(arrayC, matrixC, 0);
}

JNIEXPORT void JNICALL Java_Matrix_powerC
  (JNIEnv * env , jobject, jdoubleArray arrayM, jdoubleArray arrayR, jint m, jint k){
	jboolean isCopyM, isCopyR;

	jdouble* matrixM = env->GetDoubleArrayElements(arrayM,&isCopyM);
	jdouble* matrixR = env->GetDoubleArrayElements(arrayR,&isCopyR);
	jdouble* matrixTemp = new jdouble[m*m];

	std::copy(matrixM, matrixM + (m*m), stdext::checked_array_iterator<jdouble*>( matrixTemp, m*m ));

	for (jint i = 0; i < k-1; i++)
		matrixTemp = multiply(matrixTemp, matrixM, m,m,m);

	std::copy(matrixTemp, matrixTemp + (m*m), stdext::checked_array_iterator<jdouble*>( matrixR, m*m ));

	if (isCopyM==JNI_TRUE)
		env->ReleaseDoubleArrayElements(arrayM, matrixM, JNI_ABORT);
	if (isCopyR==JNI_TRUE)
		env->ReleaseDoubleArrayElements(arrayR, matrixR, 0);
}