#pragma once

#include <string>

/**
 * @brief A data structure for a rule.
 * 
 */
struct Rule
{
	signed char from;
	signed char to;
	std::string next;
};