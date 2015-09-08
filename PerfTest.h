#pragma once
#include "stdafx.h"

#define ERR_POS 50
#define ROUNDS 10000000

int results;

class empty_exc {};

int fact_exc(int x) {
	if (x == ERR_POS) throw empty_exc();
	if (x == 0) return 1;
	else return x * fact_exc(x - 1);
}

int fact_errcode(int x, int *out) {
	if (x == ERR_POS) return 1;
	if (x == 0) {
		*out = 1;
		return 0;
	} else {
		int x1f;
		int err = fact_errcode(x - 1, &x1f);
		if (err) return err;
		*out = x * x1f;
		return 0;
	}
}

void run_exc() {
	for (int i = 0; i < ROUNDS; i++) {
		try {
			results = fact_exc(i % (ERR_POS + 1));
		} catch (...) {}
	}
}

void run_errcode() {
	for (int i = 0; i < ROUNDS; i++) {
		int res;
		fact_errcode(i % (ERR_POS + 1), &res);
		results = res;
	}
}

int64_t timing(void(*Fn)()) {
	auto begin = std::chrono::high_resolution_clock::now();

	Fn();

	auto end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}