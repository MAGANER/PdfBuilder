#include"Parser.h"
using namespace Parser;


std::string Parser::prepare(const std::string& line)
{
	
	using namespace std;
	regex reg_right(">");
	regex reg_left("<");

	string updated = line;
	if (regex_search(updated.c_str(), reg_right))
		updated = regex_replace(updated, reg_right, "> ");
	if (regex_search(updated.c_str(), reg_left))
		updated = regex_replace(updated, reg_left, " <");

	return updated;
}
tags_str Parser::get_tag(const std::string& line)
{
	using namespace std;

	regex reg("[<][^<>]*[>]");

	vector<string> result;
	string text;
	function<void(const string&, vector<string>&)> _gt = [&](const string& _line,
		vector<string>& result)
	{
		auto line = put_new_line_ch(prepare(_line));
		cmatch m;
		regex_search(line.c_str(), m, reg);
		if (m.empty())
		{
			text = line;
			return;
		}
		else
		{
			result.push_back(*m.begin());
			auto updated = regex_replace(line, regex((*m.begin()).str()), DELIM);
			_gt(updated, result);
		}
	};
	_gt(line, result);

	return make_pair(result,change_spaces(text));
}
std::string Parser::put_new_line_ch(const std::string& line)
{
	auto reg = std::regex("<br>");
	return std::regex_replace(line.c_str(), reg, "\n");
}
std::vector<std::string> Parser::split(std::string s, std::string delimiter)
{
	using namespace std;
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) 
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}
std::vector<Node*> Parser::parse(const std::string& line)
{
	using namespace std;
	auto tag = get_tag(line);
	auto splitted_text = split(return_spaces(tag.second), " ");

	vector<Node*> result;
	int tag_counter = 0;
	for (auto token : splitted_text)
	{
		auto _ = regex_replace(token.c_str(), regex("_"), " ");
		if (!is_spaceful(_))
		{
			bool is_tag = regex_search(_.c_str(), regex(".*[#$#].*"));
			if (is_tag)
			{
				result.push_back(make_tag(tag.first[tag_counter]));
				tag_counter++;
			}
			else
			{
				result.push_back(make_text(_));
			}
		}
	}

	return result;
}
bool Parser::is_spaceful(const std::string& line)
{
	using namespace std;
	regex space("[ \t\r\n\f]{"+to_string(line.size())+"}");
	if (regex_match(line.c_str(), space)) return true;
	else return false;
}
std::string Parser::change_spaces(const std::string& line)
{
	using namespace std;
	string result;
	for (auto& n : line)
	{
		if (isspace(n))result += "_";
		else result += n;
	}
	return result;
}
std::string Parser::return_spaces(const std::string& line)
{
	using namespace std;

	regex reg_left("_{2,}");
	regex reg_right("_{2,}");

	auto updated = regex_replace(line.c_str(), reg_left, "_ ");
	return regex_replace(updated.c_str(), reg_right, " _");
}