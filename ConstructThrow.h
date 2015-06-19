#pragma once
#include "stdafx.h"
#include "common.h"

class ConsThrow {
public:
	ConsThrow(): m_smartptr('A') {
		// allocate resource 1
		m_resource1 = true;

		// process something, throw exception
		throw std::runtime_error("oops");

		// allocate resource 2
		m_resource2 = true;
	}

	~ConsThrow() {
		// cleanup, never happens, resources are leaked
		// m_smartptr is still cleaned though
		m_resource1 = false;
		m_resource2 = false;

		ReportCleanup("ConsThrow");
	}

private:
	bool m_resource1;
	bool m_resource2;
	SmartResource m_smartptr;
};


class NoThrowBaseClass {
public:
	NoThrowBaseClass() {
		m_resource1 = 42; // magic number
	}

	~NoThrowBaseClass() {
		m_resource1 = 0; // fake cleanup, is called because this class doesn't throw
		ReportCleanup("NoThrowBaseClass");
	}

protected:
	int m_resource1;

};

class ConsThrowSubclass : public NoThrowBaseClass {
public:
	ConsThrowSubclass() {
		// allocate something
		m_resource2 = 128;

		// fail
		throw std::runtime_error("oops");
	}

	~ConsThrowSubclass() {
		// this destructor fails to run because of the exception
		m_resource2 = 0;
		ReportCleanup("ConsThrowSubclass");
	}
protected:
	int m_resource2;
};