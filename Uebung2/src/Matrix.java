public class Matrix {
	private double[] matrix;
	private int heigth;
	private int width;
	
	public Matrix(int heigth, int width) {
		this.heigth=heigth;
		this.width=width;
		this.matrix=new double[heigth*width];
		
		for (int i = 0; i < matrix.length; i++) {
			matrix[i] = Math.random();
		}
	}
	
	public Matrix(int heigth, int width, int value) {
		this.heigth=heigth;
		this.width=width;
		this.matrix=new double[heigth*width];
		
		for (int i = 0; i < matrix.length; i++) {
			matrix[i] = value;
		}
	}
	
	private Matrix(int heigth, int width, double[] matrix) {
		this.heigth=heigth;
		this.width=width;
		this.matrix=matrix;
	}
	
	private Matrix multiplyNative(Matrix m) {
		long start = System.currentTimeMillis();
		
		double[] result = new double[this.heigth*m.width];
		multiplyC(this.matrix, m.matrix, result, this.heigth, this.width, m.width);
		
		System.out.println("C++(Release) multiplication and JNI call:\n" + (System.currentTimeMillis()-start) + " ms");
		
		return new Matrix(this.heigth, m.width, result);
	}
	
	private double[] multiplyArray(double[] matrixA, double[] matrixB, int n,int m,int p) {
		double[] matrixC = new double[n*p];
		for (int iN = 0; iN < n; iN++)
		  {
			  for (int iP = 0; iP < p; iP++)
			  {
				  double sum = 0.0;
				  for (int iM = 0; iM < m; iM++)
					  sum+=matrixA[iN*m+iM]*matrixB[iM*p+iP];
				  matrixC[iN*p+iP]=sum;
			  }
		  }
		return matrixC;
	}
	
	private Matrix multiplyJava(Matrix m) {
		long start = System.currentTimeMillis();
		double[] matrixC = new double[this.heigth*m.width];  
		
		double[] matrixA = this.matrix;
		double[] matrixB = m.matrix; 

		matrixC=multiplyArray(matrixA, matrixB,  this.heigth, this.width, m.width);
		
		System.out.println("Java multiplication:\n" + (System.currentTimeMillis()-start) + " ms");
		  
		return new Matrix(this.heigth, m.width, matrixC);
	}
	
	public Matrix multiply(Matrix m) {
		if  (this.width!=m.heigth)
			throw new IllegalArgumentException("The heigth of the second matrix must match the witdh of the first!");
		
		Matrix resultCpp;
		Matrix resultJava;
		
		resultCpp=this.multiplyNative(m);
		
		resultJava=this.multiplyJava(m);
		
		if (resultJava.equals(resultCpp)) {
			System.out.println("The results are equal!");
			return resultJava;
		}
		else {
			System.out.println("The results are not equal!");
			return null;
		}
	}
	
	boolean equals(Matrix m) {
		if (m==null || m.heigth!=this.heigth || m.width!=this.width)
			return false;
		
		for (int i = 0; i < this.matrix.length; i++) {
			if (this.matrix[i] != m.matrix[i]) 
				return false;
		}
		return true;
	}
	
	public Matrix power(int k) {
		if (this.heigth!=this.width)
			throw new IllegalArgumentException("The matrix must be quadratic!");
		
		Matrix resultCpp;
		Matrix resultJava;
		
		resultCpp=this.powerNative(k);
		
		resultJava=this.powerJava(k);
		
		if (resultJava.equals(resultCpp)) {
			System.out.println("The results are equal!");
			return resultJava;
		}
		else {
			System.out.println("The results are not equal!");
			return null;
		}
	}
	
	public Matrix powerNative(int k) {
		long start = System.currentTimeMillis();
		
		double[] result = new double[this.heigth*this.width];
		powerC(this.matrix, result, this.heigth, k);
		
		System.out.println("C++(Release) power and JNI call:\n" + (System.currentTimeMillis()-start) + " ms");
		
		return new Matrix(this.heigth, this.width, result);
	}
	
	public Matrix powerJava(int k) {
		long start = System.currentTimeMillis();
		
		double[] matrixR = new double[this.heigth*this.width];
		

		System.arraycopy(this.matrix, 0, matrixR, 0, matrixR.length);
		
		for (int i = 0; i < k-1; i++) 
			matrixR=multiplyArray(matrixR, this.matrix, this.heigth,this.heigth,this.heigth);

		
		System.out.println("Java power:\n" + (System.currentTimeMillis()-start) + " ms");
		  
		return new Matrix(this.heigth, this.width, matrixR);
	}
	
	@Override
	public String toString() {
		StringBuilder sOut = new StringBuilder("Matrix:\n");
		for (int y = 0; y < this.heigth; y++) {
			sOut.append("|");
			for (int x = 0; x < this.width; x++) {
				sOut.append(this.matrix[y*this.width+x] + "\t");
			}
			sOut.append("|\n");
		}
		return sOut.toString();
	};
	
	native void powerC(double[] a, double[] r, int m, int k);
	
	native void multiplyC(double[] a, double[] b, double[] r, int i, int j, int k);
	
	static {
		System.loadLibrary("NativeFunctions");
	}
}
