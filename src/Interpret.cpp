#include "Interpret.hpp"

void load(Machine& m, const std::vector<std::string>& code);
void loadTape(Machine& m, const std::vector<std::string>& code);
void loadStates(Machine& m, const std::vector<std::string>& code);

void interpret(std::vector<std::string> code)
{
	//Decl the turing machine.
	Machine m;
	//Load the machine
	load(m, code);

	//Run the machine.
	do
	{
		std::cout << "tape: " << m.getTape() << "\n";
		m.step();
	} while (m.isRunning());
	std::cout << "end-tape: " << m.getTape() << "\n";
}

void load(Machine& m, const std::vector<std::string>& code)
{
	//Load the tape.
	loadTape(m, code);
	loadStates(m, code);

	m.setState("main");
	m.setPosition(0);
}

void loadStates(Machine& m, const std::vector<std::string>& code)
{
	using namespace std;
	//The state matching regex.
	regex state(R"(^state\s+(.+)\s*:$)");

	//The code proceeding each state declaration.
	unordered_map<string, vector<string>> states;

	for (size_t i = 0; i < code.size(); ++i)   //Iter over all lines
	{
		string line = code.at(i);   //Get the line
		//If the line matches..
		smatch m;
		if (regex_search(line, m, state))
		{
			//Get the name of the state.
			string name = m[1];
			//Init the code in the map
			states[name] = vector<string>();
			//Continue iterating through the string, grabbing each line.
			while ((++i) < code.size() && !regex_match(code.at(i), state))
			{
				states[name].push_back(code.at(i));
			}
			--i;
		}
	}

	//The rule-matching regex.
	regex rule_regex(R"(([01\.])\s*->\s*(.*?)\s*->\s*(.*?)$)");
	//For every line of code in the state, load the rules.
	vector<State> loaded_states;
	for (auto& [name, rules] : states)
	{
		State s;
		s.setName(name);
		//For every rule..
		for (auto& rule : rules)
		{
			//If it matches..
			smatch match;
			if (regex_search(rule, match, rule_regex))
			{
				//Get the three items.
				string from, to, next;
				from = match[1];
				to   = match[2];
				next = match[3];
				Rule r;
				r.from = (from == "." ? (-1) : (from == "0" ? 0 : 1));
				r.to   = (to == "." ? (-1) : (to == "0" ? 0 : 1));
				r.next = next;
				//Append the rule.
				s.setRule(r);
			}
		}

		//Append the state.
		loaded_states.push_back(s);
	}
	//Load the states
	m.loadStates(loaded_states);
}

void loadTape(Machine& m, const std::vector<std::string>& code)
{
	using namespace std;
	regex itape(R"(^>\s*([01\.]*)$)");
	//Find the initial tape (prefixed with >)
	for (auto& line : code)
	{
		smatch res;
		//Check and get if the itape regex matches.
		if (regex_search(line, res, itape))
		{
			//Convert the string to a vector of signed chars.
			string tapestr = res[1].str();
			std::vector<signed char> tape;
			for (auto& i : tapestr)
			{
				switch (i)
				{
				default:
					throw std::runtime_error("Invalid tape character!");
					break;
				case '.':
					tape.push_back(-1);
					break;
				case '1':
					tape.push_back(1);
					break;
				case '0':
					tape.push_back(0);
					break;
				}
			}
			m.setTape(tape);
			break;
		}
	}
}