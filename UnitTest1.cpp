#include "pch.h"
#include "CppUnitTest.h"
#include "../KursRab_Ushin/functions.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CourseWorkUnitTest
{
	TEST_CLASS(CourseWorkUnitTest)
	{
	public:
		TEST_METHOD(TestStack) {
			Stack<char> stack;
			const size_t sz = 26;
			for (size_t i = 0; i < sz; i++)
				stack.push('A' + i);
			Assert::AreEqual(stack.top(), 'Z');
			for (size_t i = 0; i < sz; i++)
				Assert::AreEqual(stack.pop(), char('Z' - i));
			Assert::IsTrue(stack.empty());
			for (size_t i = 0; i < sz; i++)
				stack.push('A' + i);
			stack.clear();
			Assert::IsTrue(stack.empty());
		}
		TEST_METHOD(TestPostfix) 
		{
			Assert::AreEqual(priority('*'), priority('/'));
			Assert::AreEqual(priority('+'), priority('-'));
			Assert::IsFalse(priority('*') == priority('^'));
			Assert::IsFalse(priority('*') < priority('-'));
			Assert::IsTrue(priority('/') >= priority('+'));
			Assert::IsTrue(Postfix_eq::correct_eq("sqrt(3+622)"));
			Assert::IsTrue(Postfix_eq::correct_eq("(10-15)*3+5"));
			Assert::IsTrue(Postfix_eq::correct_eq("tg(3*pi/4) * ln(e) - tg(0)"));
			Assert::IsTrue(Postfix_eq::correct_eq("(((cos(3*pi/4) + 1) - 2 * 19)* 3)"));
			Assert::IsTrue(Postfix_eq::correct_eq("(-12 * tg (pi/4) - sin(2*pi/3))^5 + ln(5)"));
			Assert::IsTrue(Postfix_eq::correct_eq("sqrt(abs(cos(19)^2 - sin(19)^2))"));
			Assert::IsTrue(Postfix_eq::correct_eq("sin(8)"));
			Assert::IsTrue(Postfix_eq::correct_eq("sin(tg(18))"));
			Assert::IsTrue(Postfix_eq::correct_eq("ln(5) + tg(0)"));
			Assert::IsFalse(Postfix_eq::correct_eq("sqr(-2)"));
		}
	};
}