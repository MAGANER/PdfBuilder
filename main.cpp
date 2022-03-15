#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
#include<functional>
#include"ArgumentReader.h"
#include"TagProcessor.h"
using namespace std;

vector<string> read_script(const string& path);
int main(int argc, char** argv)
{
	ArgumentReader::Args* args = ArgumentReader::read_args(argc, argv);
	if (args == nullptr)
	{
		cout << "incorrect arguments!";
		return -1;
	}
	else
	{
		auto macro_table = make_mt;
		if (!args->macro_file.empty())
		{
			auto script = read_script(args->macro_file);
			auto parsed = Parser::parse_script(script);
			macro_table = TagProcessor::process_macro_script(parsed);
		}
		
		auto script = read_script(args->script_path);
		auto parsed = Parser::parse_script(script);
		TagProcessor::process_parsed_script(args->document_path, parsed,macro_table);
	}

	delete args;
	return 0;
}
vector<string> read_script(const string& path)
{
	vector<string> script;

	ifstream file(path);
	string line;
	while (getline(file, line)) script.push_back(line);

	return script;
}