#include <iostream>
#include "CppExceptionWithCallstack.h"

using namespace std;

int inner(const int n) {
	if (n < 0) {
		throw CppExceptionWithCallstack{"Error"};
	}
	return n * n;
}

int outer(const int n) {
	return inner(n);
}

int main() {
	try {
		cout << outer(-5) << "\n";
	}
	catch (const CppExceptionWithCallstack& except) {
		cout << except.GetCallstack() << std::endl;
	}
}
