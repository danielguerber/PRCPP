public class TestClass {
	public static void main(String[] args) {
		Matrix matrixA = new Matrix(400,6000);
		Matrix matrixB = new Matrix(6000,300);
		
		matrixA.multiply(matrixB);
		
		Matrix matrixC = new Matrix(200,200);
		
		matrixC.power(50);
		
		Matrix matrixD = new Matrix(2,2,2);
		System.out.println(matrixD);
		System.out.println(matrixD.powerJava(3));
	}
	
//	    C++(Debug) multiplication and JNI call:
//		5950 ms
//		Java multiplication:
//		3881 ms
//		The results are equal!
//		C++(Debug) powers and JNI call:
//		1291 ms
//		Java power:
//		511 ms
//		The results are equal!
//		Matrix:
//		|2.0	2.0	|
//		|2.0	2.0	|
//
//		Java power:
//		0 ms
//		Matrix:
//		|128.0	128.0	|
//		|128.0	128.0	|
	
	
//		C++(Release) multiplication and JNI call:
//		3901 ms
//		Java multiplication:
//		3902 ms
//		The results are equal!
//		C++(Release) power and JNI call:
//		361 ms
//		Java power:
//		470 ms
//		The results are equal!
//		Matrix:
//		|2.0	2.0	|
//		|2.0	2.0	|
//
//		Java power:
//		0 ms
//		Matrix:
//		|128.0	128.0	|
//		|128.0	128.0	|
	
	
	
	
}
