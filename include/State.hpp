#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "Rule.hpp"

/**
 * @brief A state the machine can be in.
 * 
 */
class State
{
public:
	/**
	 * @brief Construct a new State
	 * 
	 */
	State();

	/**
	 * @brief Set the state rules.
	 * 
	 * @param new_rule The rule to set.
	 * 
	 * @remarks If the 'from' value of the rule is already set,
	 * this overwrites it.
	 */
	void setRule(Rule new_rule);

	/**
	 * @brief Get the rule from the given input value.
	 * 
	 * @param from The value to convert
	 * @return Rule* The rule that converts from the `from` value.
	 */
	Rule* getRule(signed char from);

	/**
	 * @brief Set the name of the state
	 * 
	 * @param new_name the new name of the state.
	 */
	void setName(std::string new_name);

	/**
	 * @brief Get the Name of the state.
	 * 
	 * @return std::string The state's name.
	 */
	std::string getName();

private:
	/**
	 * @brief The state rules.
	 * 
	 */
	std::vector<Rule> mRules;

	/**
	 * @brief The state's name.
	 * 
	 */
	std::string mName;
};