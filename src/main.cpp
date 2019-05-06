#include <fstream>
#include <iostream>
#include <regex>
#include <streambuf>

#include "Interpret.hpp"

void removeComments(std::string& text);
void removeWhitespace(std::string& text);
std::vector<std::string> split(std::string text);

int main(int argc, char* argv[])
{
	//Validate arguments.
	if (argc != 2)
	{
		std::cerr << "Invalid Args! Usage: " << argv[0] << " {filename}\n";
		return -1;
	}
	//Load the inputted file.
	std::ifstream file(argv[1]);
	if (!file)
	{
		std::cerr << "Could not open file " << argv[1] << ".\n";
		return -2;
	}
	//Read the text from the file
	std::string text = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	//Split and clean up the code.
	auto lines = split(text);
	std::vector<std::string> code;
	for (auto& line : lines)
	{
		removeComments(line);
		removeWhitespace(line);
		if (!line.empty())
		{
			code.push_back(line);
		}
	}

	//Pass the code onto the interpreter.
	interpret(code);

	return 0;
}

void removeComments(std::string& text)
{
	using namespace std;
	regex comment_regex(R"(^(.*?)\s*\/\/.*$)", regex::extended);
	text = regex_replace(text, comment_regex, "$1");
}

void removeWhitespace(std::string& text)
{
	using namespace std;
	regex wspace_regex(R"(^\s*(.*)\s*$)");
	text = regex_replace(text, wspace_regex, "$1");
}

std::vector<std::string> split(std::string text)
{
	using namespace std;
	regex nl(R"(\n)");
	vector<string> res;
	copy(sregex_token_iterator(text.begin(), text.end(), nl, -1), sregex_token_iterator(), back_inserter(res));
	return res;
}