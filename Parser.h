#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include<string>
#include<regex>
#include<functional>
#include<utility>
namespace Parser
{
	typedef std::pair<std::vector<std::string>, std::string> tags_str;

	std::string put_new_line_ch(const std::string& line);
	tags_str get_tag(const std::string& line);
};
#endif //PARSER_H