#include <iostream>

using namespace std;

template<typename T>
struct Scalar
{
	T m_data;
	Scalar(T data):m_data(data) {}

	T operator[] (int i)
	{
		return m_data;
	}
};

template<typename T>
struct Array;

template<typename T>
struct Product
{
	Array<T> m_data;
	Product(const Array<T> &data):m_data(data) {}	

	template<typename D>
	T operator* (Product<D> right)
	{
		T product = 0;
		for(int i = 0; i < m_data.getN();i++)
			product += m_data[i] * right.m_data[i];

		return product;
	}
};

struct Plus {
	template <typename T>
	static T apply(T left, T right) {
		return left + right;
	}
};

struct Minus {
	template <typename T>
	static T apply(T left, T right) {
		return left - right;
	}
};

template<typename T>
struct Mult {
	static T apply(T left, T right) {
		return left * right;
	}
};



// the node in the parse tree.
template <typename Left, typename Op, typename Right, typename T>
struct X
{
	Left m_left;
	Right m_right;
	X( Left t1, Right t2) : m_left(t1), m_right(t2) { }
	T operator[](int i)
	{
		return Op::apply( m_left[i], m_right[i] );
	}

	template <typename Right>
	X<X, Plus, Right, T> operator+(Right b)
	{
		return X<X, Plus, Right, T>(*this,b);
	};

	template <typename Right>
	X<X, Minus, Right, T> operator-(Right b)
	{
		return X<X, Minus, Right, T>(*this,b);
	};

	template <typename Right>
	X<X, Mult<T>, Scalar<Right>, T> operator*(Right b)
	{
		return X<X, Mult<T>, Scalar<Right>, T>(*this,Scalar<Right>b);
	};

	template <typename LeftExpr>
	friend X<Scalar<LeftExpr>, Mult<T>, X, T> operator*(LeftExpr b, X<X, Op, Right, T> rigth)
	{
		return X<Scalar<LeftExpr>, Mult<T>, X, T>(Scalar<LeftExpr>b, rigth);
	};
};



template <typename T>
struct Array
{
	T *m_data;
	int m_N;
	// constructor
	Array( T *data, int N) : m_data(data), m_N(N) { }

	// assign an expression to the array
	template <typename Left, typename Op, typename Right>
	void operator=( X<Left,Op,Right, T> expr)
	{
		for ( int i = 0; i < m_N; ++i)
		m_data[i] = expr[i];
	}

	int getN()
	{
		return m_N;
	}

	template <typename Right>
	X<Array<T>, Plus, Right, T> operator+(Right b)
	{
		return X<Array<T>, Plus, Right, T>(*this,b);
	};

	template <typename Right>
	X<Array<T>, Minus, Right, T> operator-(Right b)
	{
		return X<Array<T>, Minus, Right, T>(*this,b);
	};

	template <typename Right>
	X<Array<T>, Mult<T>, Scalar<Right>, T> operator*(Right b)
	{
		return X<Array<T>, Mult<T>, Scalar<Right>, T>(*this,Scalar<Right>(b));
	};

	template <typename Left>
	friend X<Scalar<Left>, Mult<T>, Array<T>, T> operator*(Left b, Array<T> rigth)
	{
		return X<Scalar<Left>, Mult<T>, Array<T>, T>(Scalar<Left>(b), rigth);
	};

	template<typename E>
	T operator*(Product<E> r)
	{
		return (Product<T>(*this) * r);
	}

	Product<T> operator*() const
	{
		return Product<T>(*this);
	}

	T operator[](int i)
	{
		return m_data[i];
	}

	void print() const {
		int l = 0; cout << '[';
		if (m_N > 0) cout << m_data[l++];
		while(l < m_N) {
			cout << ',' << m_data[l++];
		}
		cout << ']' << endl;
	}

};




