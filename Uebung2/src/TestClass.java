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
//		6030 ms
//		Java multiplication:
//		3921 ms
//		The results are equal!
//		C++(Debug) power and JNI call:
//		1281 ms
//		Java power:
//		471 ms
//		The results are equal!
//		Matrix:
//		|2.0	2.0	|
//		|2.0	2.0	|
//
//		Java power:
//		0 ms
//		Matrix:
//		|32.0	32.0	|
//		|32.0	32.0	|
	
	
//	    C++(Release) multiplication and JNI call:
//		3697 ms
//		Java multiplication:
//		3729 ms
//		The results are equal!
//		C++(Release) power and JNI call:
//		376 ms
//		Java power:
//		390 ms
//		The results are equal!
//		Matrix:
//		|2.0	2.0	|
//		|2.0	2.0	|
//
//		Java power:
//		0 ms
//		Matrix:
//		|32.0	32.0	|
//		|32.0	32.0	|


	
	
	
	
}
