#include "Machine.hpp"

Machine::Machine()
{
}

void Machine::loadStates(std::vector<State> states)
{
	mStates = states;
}

void Machine::setTape(std::vector<signed char> new_tape)
{
	mTape = new_tape;
}

std::string Machine::getTape()
{
	std::stringstream ret;
	for (auto& item : mTape)
	{
		ret << (item == -1 ? '.' : (item == 0 ? '0' : '1'));
	}
	return ret.str();
}

void Machine::setPosition(size_t pos)
{
	mHead = pos;
}

void Machine::setState(std::string name)
{
	if (name != mCState)
	{
		setPosition(0);
	}
	mCState = name;
}

void Machine::step()
{
	mRunning		  = true;
	signed char* head = get();
	State& cstate	 = getState(mCState);
	Rule& r			  = *cstate.getRule(*head);
	set(r.to);

	next();

	if (r.next != "halt")
	{
		setState(r.next);
	}
	else
	{
		mRunning = false;
	}
}

void Machine::run()
{
	mRunning = true;
	while (isRunning())
	{
		step();
	}
}

bool Machine::isRunning()
{
	return mRunning;
}

signed char* Machine::next()
{
	//Increment the head.
	mHead++;
	//Return the pointer to the tape element.
	return get();
}

signed char* Machine::prev()
{
	//Decrement the head.
	mHead--;
	//Return the
	return get();
}

signed char* Machine::get()
{
	//If we're lower than 0..
	if (mHead < 0)
	{
		//Wrap around
		mHead = WRAP;
	}
	//otherwise, if we're above wrap...
	else if (mHead > WRAP)
	{
		//Loop to 0.
		mHead = 0;
	}
	//Push blanks until there's an elem at mHead.
	while (mHead >= (signed)mTape.size())
	{
		mTape.push_back(-1);
	}
	//Return the element.
	return &mTape[mHead];
}

void Machine::set(signed char n)
{
	*(get()) = n;
}

State& Machine::getState(std::string state_name)
{
	for (auto& i : mStates)
	{
		if (i.getName() == state_name)
		{
			return i;
		}
	}
	throw std::out_of_range("Invalid state " + state_name + "\n");
}