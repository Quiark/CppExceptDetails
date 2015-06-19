#pragma once
#include "stdafx.h"

class DestThrow {
public:
	~DestThrow() {
		// this is generally not allowed but it may pass if 
		// no other exception is currently happening
		throw std::runtime_error("oops");
	}
};

void DoubleException() {
	DestThrow resource;

	throw std::invalid_argument("first exception");
}
