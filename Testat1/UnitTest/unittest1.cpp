#include "stdafx.h" 
#include "CppUnitTest.h" 
#include "MyString.h" 
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest { 
	TEST_CLASS(MyString) {
	
	public: 
		TEST_METHOD(Construction) { 
			String s0; 
			String s1(""); 
			String s2("abc"); 
			String s00(s0); 
			String s11(s1); 
			String s22(s2);
		}

		TEST_METHOD(CharAt) {
			String s("abcdef");
			Assert::IsTrue(s.charAt(0) == 'a');
			Assert::IsTrue(s.charAt(3) == 'd');
			Assert::IsTrue(s.charAt(5) == 'f');
			try {
				s.charAt(6);
				Assert::Fail();
			} catch (...) {
			}
		}

		TEST_METHOD(CompareTo) {
			String s0;
			String s1("bbb");
			String s2("bbc");
			String s3("bb");

			Assert::IsTrue(s0.compareTo(s0)==0);
			Assert::IsTrue(s1.compareTo(s1)==0);
			Assert::IsTrue(s0.compareTo(s1)==-1);
			Assert::IsTrue(s1.compareTo(s0)==1);
			Assert::IsTrue(s1.compareTo(s2)==-1);
			Assert::IsTrue(s2.compareTo(s1)==1);
			Assert::IsTrue(s1.compareTo(s3)==1);
			Assert::IsTrue(s3.compareTo(s1)==-1);
		}

		TEST_METHOD(ConcatChar) {
			String s0("abcde");
			String s1("abcdef");
			String s2;
			String s3("a");
			Assert::IsTrue(s1.compareTo(s0.concat('f'))==0);
			Assert::IsTrue(s3.compareTo(s2.concat('a'))==0);
		}

		TEST_METHOD(ConcatString) {
			String s0("abc");
			String s1("def");
			String s2("abcdef");
			String s3;
			String s4;

			Assert::IsTrue(s2.compareTo(s0.concat(s1))==0);
			Assert::IsTrue(s0.compareTo(s0.concat(s3))==0);
			Assert::IsTrue(s0.compareTo(s3.concat(s0))==0);
			s4 = s2.substring(3,5);
			Assert::IsTrue(s2.compareTo(s0.concat(s4))==0);
		}

		TEST_METHOD(Length) { 
			Assert::IsTrue(String().length() == 0); 
			Assert::IsTrue(String("").length() == 0); 
			Assert::IsTrue(String("abc").length() == 3); 
		} 

		TEST_METHOD(Substring) {
			String s0("abcdefgh");
			String s1("abc");
			String s2("d");
			String s3("gh");
			Assert::IsTrue(s0.compareTo(s0.substring(0,7))==0);
			Assert::IsTrue(s1.compareTo(s0.substring(0,2))==0);
			Assert::IsTrue(s2.compareTo(s0.substring(3,3))==0);
			Assert::IsTrue(s3.compareTo(s0.substring(6,7))==0);

			try {
				s0.substring(0,8);
				Assert::Fail();
			} catch (...) {}

			try {
				s0.substring(5,4);
				Assert::Fail();
			} catch (...) {}
		
		}

		
		TEST_METHOD(ToCString) {
			String s0;
			String s1("abcd");

			Assert::IsTrue(std::strcmp(s0.toCString().get(),"")==0);
			Assert::IsTrue(std::strcmp(s1.toCString().get(),"abcd")==0);
		}

		TEST_METHOD(ValueOf) {
			String s0("-1");
			Assert::IsTrue(s0.compareTo(String::valueOf(-1))==0);
		}
	}; 
}