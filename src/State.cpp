#include "State.hpp"

State::State()
{
}

void State::setName(std::string new_name)
{
	mName = new_name;
}

std::string State::getName()
{
	return mName;
}

void State::setRule(Rule new_rule)
{
	//Try to find the rule.
	auto found = std::find_if(mRules.begin(), mRules.end(), [&new_rule](Rule& rule) {
		return rule.from == new_rule.from;
	});

	//If it's not there, push it.
	if (found == mRules.end())
	{
		mRules.push_back(new_rule);
	}
	else   //Otherwise, just set the existing value.
	{
		*found = new_rule;
	}
}

Rule* State::getRule(signed char from)
{
	//Try to find the rule.
	auto found = std::find_if(mRules.begin(), mRules.end(), [&from](Rule& rule) {
		return rule.from == from;
	});

	//If it's not there, return nullptr.
	if (found == mRules.end())
	{
		return nullptr;
	}
	//Otherwise, return the found object.
	else
	{
		return &(*found);
	}
}