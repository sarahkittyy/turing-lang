#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "State.hpp"

/**
 * @brief A turing machine emulator.
 * 
 */
class Machine
{
public:
	/**
	 * @brief Construct the machine object.
	 * 
	 */
	Machine();

	/**
	 * @brief Load the machine states.
	 * 
	 */
	void loadStates(std::vector<State> states);

	/**
	 * @brief Set the state of the tape.
	 * 
	 */
	void setTape(std::vector<signed char> new_tape);

	/**
	 * @brief Get a string representing the tape.
	 * 
	 * @return std::string A string representing the tape.
	 */
	std::string getTape();

	/**
	 * @brief Set the head position.
	 * 
	 * @param pos The new head position.
	 */
	void setPosition(size_t pos);

	/**
	 * @brief Set the machines state.
	 * 
	 * @param name The name of the state.
	 */
	void setState(std::string name);

	/**
	 * @brief Step the machine forward one iteration.
	 * 
	 */
	void step();

	/**
	 * @brief Step until the machine has halted.
	 * 
	 */
	void run();

	/**
	 * @brief Check if the machine has halted or not.
	 * 
	 * @return bool whether or not the machine is running.
	 */
	bool isRunning();

private:
	/**
	 * @brief The machine tape.
	 * 
	 * @remarks -1 is a blank tape item.
	 * 
	 */
	std::vector<signed char> mTape;

	/**
	 * @brief The max tape length;
	 * 
	 */
	const int WRAP = 1000;

	/**
	 * @brief The position we are in in the tape. 
	 * 
	 */
	int mHead;

	//Tape read/write functions.
	signed char* next();
	signed char* prev();
	signed char* get();
	void set(signed char n);

	/**
	 * @brief Get the State with the given name.
	 * 
	 * @param state_name The name of the state
	 * @return State& A reference to that state.
	 */
	State& getState(std::string state_name);

	/**
	 * @brief The machine states.
	 * 
	 */
	std::vector<State> mStates;

	/**
	 * @brief The currently running state.
	 * 
	 */
	std::string mCState;

	/**
	 * @brief Whether or not the machine has halted.
	 * 
	 */
	bool mRunning = false;
};