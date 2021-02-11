#include <iostream>
#include "functions.h"
#include <string>
using namespace std;
int main() 
{
	string equation;
	char choose = 's';
	while (choose != 'e')
	{
		cout << "Enter 'c' to calculate or 'e' to exit" << endl;;
		cin >> choose;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		switch (choose)
		{
		case 'c':
		{
			cout << endl;
			cout << "Enter expression: " << endl;
			getline(cin, equation);
			cout << endl;
			if (Postfix_eq::correct_eq(equation))
			{
				cout << "Expression is correct!" << endl;
				cout << "Result of exspression: " << Postfix_eq(equation).counting_eq() << endl<<endl;
			}
			else
			{
				cout << "Expression is not correct, counting was broke." << endl<<endl;
			}
			continue;
		}
		case 'e':
		{
			cout << "Program closed." << endl;
			break;
		}
		default:
		{
			cout << "Wrong enter, try again." << endl;
		}
		}
	}
	exit(0);
}