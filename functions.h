#pragma once
#include "stack_class.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;
#define PI 3.14159265358979323846
#define EPS 1e-15
typedef int ssize_t;
void void_deleter(string equation)
{
	for (size_t i = 0; i < equation.size(); i++)
	{
		if (equation[i] == ' ') 
		{
			for (size_t j = i; j < equation.size(); j++)
				equation[j] = equation[j + 1];
			equation.resize(equation.size() - 1);
			i--;
		}
	}
}
int priority(char c)
{
	if (c == '^')
		return 2;
	else if (c == '*' || c == '/')
		return 1;
	else if (c == '+' || c == '-')
		return 0;
	return -1;
}
ssize_t check_left(string equation, size_t index)
{
	ssize_t i;
	for (i = index - 1; i >= 0 && equation[i] == ' '; i--);
	return i;
}
size_t check_right(string equation, size_t index)
{
	size_t i;
	size_t size_eq = equation.size();
	for (i = index + 1; i <= size_eq && equation[i] == ' '; i++);
	return i;
}
void print_err(string equation, size_t index)
{
	index--;
	size_t size_eq = equation.size();
	cout << equation;
	cout << endl;
	size_t i;
	for (i = 0; i < index; i++)
		cout << '_';
	cout << '^';
	for (i++; i < size_eq; i++)
		cout << ' ';
	cout << endl;
}
class Postfix_eq 
{
public:
	Postfix_eq(string equation)
	{
		if (correct_eq(equation))
			inf_eq_to_post(equation);
		else
			throw invalid_argument("Incorrect string!");
	}
	static bool correct_eq(string equation)
	{
		Stack<size_t> stack;
		size_t n = equation.size();

		if (!correct_eq_part(equation))
			return false;

		for (size_t i = 0; i < n; i++)
			if (equation[i] == '.' || equation[i] >= '0' && equation[i] <= '9' || equation[i] == 'p' || equation[i] == 'e') {
				ssize_t l_ind = check_left(equation, i);
				if (l_ind >= 0)
					if (equation[l_ind] == ')') {
						cout << "Missed operator " << l_ind + 2 << ":" << endl;
						print_err(equation, l_ind + 2);
						return false;
					}
					else if (equation[l_ind] >= '0' && equation[l_ind] <= '9' || equation[l_ind] == '.'
						|| equation[l_ind] == 'i' || equation[l_ind] == 'e') {
						cout << "Extra operand " << i + 1 << ":" << endl;
						print_err(equation, i + 1);
						return false;
					}

				if (equation[i] >= '0' && equation[i] <= '9')
					for (i += 1; i < n && equation[i] >= '0' && equation[i] <= '9'; i++);

				if (i != n)
					if (equation[i] == '.') {
						size_t r_ind = check_right(equation, i);
						if (r_ind < n && equation[r_ind] == '.') {
							cout << "Extra point " << r_ind + 1 << ":" << endl;
							print_err(equation, r_ind + 1);
							return false;
						}
						i += 1;
						for (; i < n && equation[i] >= '0' && equation[i] <= '9'; i++);
					}
					else if (equation[i] == 'e')
						i += 1;
					else if (equation[i] == 'p')
						i += 2;
				size_t r_ind = (i == n ? n : check_right(equation, i - 1)); 

				if (r_ind < n && equation[r_ind] == '(') {
					cout << "Missed operator " << i + 1 << ":" << endl;
					print_err(equation, i + 1);
					return false;
				}
				else
					i--;
			}
			else if (equation[i] == '(')
				stack.push(i);
			else if (equation[i] == ')')
				if (!stack.empty())
					stack.pop();
				else {
					cout << "Missing opening bracket for closing " << i + 1 << endl;
					print_err(equation, i + 1);
					return false;
				}
			else if (equation[i] == '+' || equation[i] == '*' || equation[i] == '/' || equation[i] == '-') {
				ssize_t l_ind = check_left(equation, i);

				if (l_ind < 0)
					if (equation[i] == '-')
						continue;
					else {
						cout << "Missed operand before operator " << i + 1 << ":" << endl;
						print_err(equation, i + 1);
						return false;
					}

				if (!(equation[l_ind] == '.' || equation[l_ind] >= '0' && equation[l_ind] <= '9' ||
					equation[l_ind] == 'i' || equation[l_ind] == 'e' ||
					equation[l_ind] == ')' ||
					(equation[i] == '-' && equation[l_ind] == '('))) {
					cout << "Missed operand before operator " << i + 1 << ":" << endl;
					print_err(equation, i + 1);
					return false;
				}

				size_t r_ind = check_right(equation, i);

				if (r_ind >= n ||
					!(equation[r_ind] == '.' || equation[r_ind] >= '0' && equation[r_ind] <= '9' ||
						equation[r_ind] == '(' ||
						equation[r_ind] == 's' || equation[r_ind] == 'c' || equation[r_ind] == 't'
						|| equation[r_ind] == 'l' || equation[r_ind] == 'e'
						|| equation[r_ind] == 'p' || equation[r_ind] == 'a')) {
					cout << "Missed operand " << i + 2 << ":" << endl;
					print_err(equation, i + 2);
					return false;
				}

			}
			else if (equation[i] == 's' || equation[i] == 'c' || equation[i] == 't'
				|| equation[i] == 'l' || equation[i] == 'a') {
				ssize_t l_ind = check_left(equation, i);

				if (equation[i] == 't' || equation[i] == 'l' && equation[i + 1] == 'n')
					i += 1;
				else if (equation[i] == 's' && equation[i + 1] == 'q')
					i += 3;
				else
					i += 2;

				if (l_ind < 0)
					continue;

				if (!(equation[l_ind] == '(' || equation[l_ind] == '^' ||
					equation[l_ind] == '+' || equation[l_ind] == '-' ||
					equation[l_ind] == '*' || equation[l_ind] == '/')) {
					cout << "Missed operand before operator " << i + 1 << ":" << endl;
					print_err(equation, i + 1);
					return false;
				}

				size_t r_ind = check_right(equation, i);

				if (r_ind >= n ||
					!(equation[r_ind] == '.' || equation[r_ind] >= '0' && equation[r_ind] <= '9' ||
						equation[r_ind] == '(' ||
						equation[r_ind] == 's' || equation[r_ind] == 'c' || equation[i] == 't'
						|| equation[i] == 'l' || equation[i] == 'e' || equation[i] == 'p' || equation[i] == 'a')) {
					cout << "Missed operand " << i + 2 << ":" << endl;
					print_err(equation, i + 2);
					return false;
				}
			}
		if (!stack.empty()) {
			cout << "Missed closing brake for brake " << stack.top() + 1 << ":" << endl;
			print_err(equation, stack.top() + 1);
			return false;
		}
		return true;
	}
	double counting_eq() const {
		Stack<double> stack;
		string post_str;
		post_str.empty();
		size_t n = result.size();
		for (size_t i = 0; i < result.size(); i++)
			if (result[i] >= '0' && result[i] <= '9') {
				double number = 0;
				for (; i < n && result[i] >= '0' && result[i] <= '9'; i++)
				{
					number = number * 10 + (result[i] - '0');
					post_str += result[i];
				}
				if (i < n && result[i] == '.') {
					int divider = 1;
					for (i++; i < n && result[i] >= '0' && result[i] <= '9'; i++) {
						number = number * 10 + (result[i] - '0');
						divider *= 10;
					}
					number /= divider;
				}
				if (i < n && !result[i] == '.')
					i--;
				stack.push(number);
				post_str += ' ';
			}
			else if (result[i] == 'e')
			{
				stack.push(exp(1));
				post_str += "e";
				post_str += ' ';
			}
			else if (result[i] == 'p')
			{
				stack.push(PI);
				post_str += "pi";
				post_str += ' ';
			}
			else if (result[i] == 's' || result[i] == 'c'
				|| result[i] == 't' || result[i] == 'g'
				|| result[i] == 'o' || result[i] == 'l'
				|| result[i] == 'q' || result[i] == 'a'
				|| result[i] == '_')
			{
				double val = stack.pop();
				switch (result[i]) {
				case 's':
					stack.push(sin(val));
					post_str += "sin";
					post_str += ' ';
					break;
				case 'c':
					stack.push(cos(val));
					post_str += "cos";
					post_str += ' ';
					break;
				case 't':
					stack.push(tan(val));
					post_str += "tg";
					post_str += ' ';
					break;
				case 'g':
					stack.push(1 / tan(val));
					post_str += "ctg";
					post_str += ' ';
					break;
				case 'o':
					stack.push(log10(val));
					post_str += "log";
					post_str += ' ';
					break;
				case 'l':
					stack.push(log(val));
					post_str += "ln";
					post_str += ' ';
					break;
				case 'q':
					stack.push(sqrt(val));
					post_str += "sqrt";
					post_str += ' ';
					break;
				case 'a':
					stack.push(abs(val));
					post_str += "abs";
					post_str += ' ';
					break;
				case '_':
					stack.push(-val);
					post_str += '-';
					post_str += ' ';
					break;
				}
			}
			else if (result[i] == '+' || result[i] == '-'
				|| result[i] == '*' || result[i] == '/'
				|| result[i] == '^') {
				double val_2 = stack.pop();
				double val_1 = stack.pop();
				switch (result[i]) {
				case'+':
					stack.push(val_1 + val_2);
					post_str += '+';
					post_str += ' ';
					break;
				case '-':
					stack.push(val_1 - val_2);
					post_str += '-';
					post_str += ' ';
					break;
				case '*':
					stack.push(val_1 * val_2);
					post_str += '*';
					post_str += ' ';
					break;
				case '/':
					stack.push(val_1 / val_2);
					post_str += '/';
					post_str += ' ';
					break;
				case '^':
					stack.push(pow(val_1, val_2));
					post_str += '^';
					post_str += ' ';
					break;
				}
			}
		cout << "Postfix form of the equation is: ";
		for (int k = 0; k < post_str.size(); k++)
		{
			cout << post_str[k];
		}
		cout << endl;
		return (abs(stack.top()) < EPS ? 0 : stack.pop());
	}
private:
	static bool correct_eq_part(string equation) {
		size_t n = equation.size();
		for (size_t i = 0; i < n; i++)
			if (!(equation[i] >= '0' && equation[i] <= '9' || equation[i] == '.'
				|| equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '^'
				|| equation[i] == '(' || equation[i] == ')' || equation[i] == ' '))
				if (equation[i] == 'e' || i + 1 < n && equation[i] == 'p' && equation[++i] == 'i') {
					if (!(i + 1 == n || equation[i + 1] == ' ' ||
						equation[i] < 'A' || equation[i] > 'Z' ||
						equation[i] < 'a' || equation[i] > 'z')) {
						cout << "Incorrect command " << i + 1 << ":" << endl;
						print_err(equation, i + 1);
						return false;
					}
				}
				else {
					bool isWrongCommand = false;
					switch (equation[i]) {
					case 's':
						if (i + 2 >= n)
							isWrongCommand = true;
						else if (equation[i + 1] == 'i' && equation[i + 2] == 'n')
							i += 2;
						else
							if (i + 3 < n && equation[i + 1] == 'q' && equation[i + 2] == 'r' && equation[i + 3] == 't')
								i += 3;
							else isWrongCommand = true;
						break;
					case 'c':
						if (i + 2 >= n)
							isWrongCommand = true;
						else if (equation[i + 1] == 'o' && equation[i + 2] == 's'
							|| equation[i + 1] == 't' && equation[i + 2] == 'g')
							i += 2;
						else isWrongCommand = true;
						break;
					case 't':
						if (i + 1 >= n)
							isWrongCommand = true;
						else if (equation[i + 1] == 'g')
							i += 1;
						else isWrongCommand = true;
						break;
					case 'l':
						if (i + 1 >= n)
							isWrongCommand = true;
						else if (equation[i + 1] == 'n')
							i += 1;
						else if (i + 2 < n && equation[i + 1] == 'o' && equation[i + 2] == 'g')
							i += 2;
						else isWrongCommand = true;
						break;
					case 'a':
						if (i + 2 >= n)
							isWrongCommand = true;
						else if (equation[i + 1] == 'b' && equation[i + 2] == 's')
							i += 2;
						else isWrongCommand = true;
						break;
					default:
						cout << "Incorrect symbol " << i + 1 << ":" << endl;
						print_err(equation, i + 1);
						return false;
					}
					if (isWrongCommand || !(i + 1 == n || equation[i + 1] == ' ' ||
						equation[i] < 'A' || equation[i] > 'Z' ||
						equation[i] < 'a' || equation[i] > 'z')) {
						cout << "Incorrect command " << i + 1 << endl;
						print_err(equation, i + 1);
						return false;
					}
				}
		return true;
	}
	void inf_eq_to_post(string equation) {
		void_deleter(equation);
		Stack<char> stack;
		size_t n = equation.size();
		for (size_t i = 0; i < n; i++) {
			if (equation[i] >= '0' && equation[i] <= '9' || equation[i] == '.') {
				for (i; equation[i] >= '0' && equation[i] <= '9' || equation[i] == '.'; i++)
					result.push_back(equation[i]);
				result.push_back(' ');
				i -= 1;
			}
			else if (equation[i] == 'e')
				result.push_back('e');
			else if (equation[i] == 'p') {
				result.push_back('p');
				i += 1;
			}
			else if (equation[i] == '-' && (i == 0 || equation[i - 1] == '('))
				stack.push('_');
			else if (equation[i] == 's') {
				if (equation[i + 1] == 'i') {
					stack.push('s');
					i += 2;
				}
				else if (equation[i + 1] == 'q') {
					stack.push('q');
					i += 3;
				}
			}
			else if (equation[i] == 'c') {
				if (equation[i + 1] == 'o') {
					stack.push('c');
					i += 2;
				}
				else if (equation[i + 1] == 't') {
					stack.push('g');
					i += 2;
				}
			}
			else if (equation[i] == 't') {
				stack.push('t');
				i += 1;
			}
			else if (equation[i] == 'l') {
				if (equation[i + 1] == 'o') {
					stack.push('o');
					i += 2;
				}
				else if (equation[i + 1] == 'n') {
					stack.push('l');
					i += 1;
				}
			}
			else if (equation[i] == 'a') {
				stack.push('a');
				i += 2;
			}
			else if (equation[i] == '(')
				stack.push('(');
			else if (equation[i] == ')') {
				while (stack.top() != '(') {
					result.push_back(stack.pop());
				}
				stack.pop();
			}
			else if (equation[i] == '+' || equation[i] == '-' || equation[i] == '*' || equation[i] == '/' || equation[i] == '^') {
				while (!stack.empty()
					&& (stack.top() == 's' || stack.top() == 'c'
						|| stack.top() == 't' || stack.top() == 'g'
						|| stack.top() == 'o' || stack.top() == 'l'
						|| stack.top() == 'q' || stack.top() == 'a'
						|| stack.top() == '_'
						|| ((stack.top() == '+' || stack.top() == '-' || stack.top() == '*'
							|| stack.top() == '/' || stack.top() == '^') &&
							priority(stack.top()) >= priority(equation[i])))) {
					result.push_back(stack.pop());
				}
				stack.push(equation[i]);
			}
		}
		while (!stack.empty())
			result.push_back(stack.pop());
	}
	string result;
};