#pragma once
#include "stdafx.h"

inline void ReportCleanup(const std::string &clsname) {
	std::cout << clsname << " cleaned up." << std::endl;
}

/** Simulates a RAII class such as a smart pointer */
class SmartResource {
public:
	SmartResource(char _id): m_allocated(true), m_id(_id) {

	}

	~SmartResource() {
		// dealloc
		m_allocated = false;

		std::string report("SmartResource ");
		report.push_back(m_id);
		ReportCleanup(report);
	}

private:
	bool m_allocated;
	char m_id;

};