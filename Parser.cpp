#include"Parser.h"
using namespace Parser;


tags_str Parser::get_tag(const std::string& line)
{
	using namespace std;

	regex reg("[<][^<>]*[>]");

	vector<string> result;
	string text;
	function<void(const string&, vector<string>&)> _gt = [&](const string& _line,
		vector<string>& result)
	{
		auto line = put_new_line_ch(_line);
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
			auto updated = regex_replace(line, regex((*m.begin()).str()), "");
			_gt(updated, result);
		}
	};
	_gt(line, result);

	return make_pair(result,text);
}
std::string Parser::put_new_line_ch(const std::string& line)
{
	auto reg = std::regex("<br>");
	return std::regex_replace(line.c_str(), reg, "\n");
}