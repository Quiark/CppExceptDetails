// CppExceptDetails.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConstructThrow.h"
#include "DestructThrow.h"
#include "PerfTest.h"

using namespace std;

#define EAT_EXC(code) \
	try { code; } \
	catch (...) {};

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "============== Throwing exceptions in constructors =======" << endl;
	EAT_EXC(ConsThrow t);
	EAT_EXC(ConsThrowSubclass t);

	LaterThrow *t = nullptr;
	EAT_EXC(t = new LaterThrow[4]);
	// t stays NULL here

	cout << "============== Timing =======" << endl;
	cout << "Exceptions: " << timing(run_exc) << endl;
	cout << "Err codes: " << timing(run_errcode) << endl;

	// keep it at the end because it's going to crash
	cout << "============== Throwing exceptions in destructors =======" << endl;
	EAT_EXC(DestThrow t);
	EAT_EXC(DoubleException());   // <-- crash here. Comment out to get a clean run
	
	// wait for user input
	cout << "Press Enter to exit" << endl;
	char val;
	cin >> val;
	return 0;
}

