// https://godbolt.org/z/MWfxKj43a

// cl /EHsc /nologo /W4 /std:c++latest /MTd /Od /Zi /Fdmeow.pdb meow.cpp && meow
#include <iostream>
#include "Cpp23Exception.h"

using namespace std;

int inner(const int n) 
{
	if (n < 0) 
	{
		throw Cpp23Exception{"Error"};
	}
	return n * n;
}

int outer(const int n) 
{
	return inner(n);
}

int main() {
	try 
	{
		cout << outer(-5) << "\n";
	}
	catch (const Cpp23Exception& except) 
	{
		cout << except.GetCallstack() << std::endl;
	}
}
