#include <iostream>
#include "CppException.h"

using namespace std;

int inner(const int n) 
{
	if (n < 0) 
	{
		throw CppException{"Error"};
	}
	return n * n;
}

int outer(const int n) 
{
	return inner(n);
}

int main() 
{
	try 
	{
		cout << outer(-5) << "\n";
	}
	catch (const CppException& except) 
	{
		cout << except.GetCallstack() << std::endl;
	}
}
