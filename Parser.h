#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include<string>
#include<regex>
#include<functional>
#include<utility>
#include<iostream>
namespace Parser
{
	static const std::string DELIM = "#$#";
	typedef std::pair<std::vector<std::string>, std::string> tags_str;

	struct Node
	{
		enum class NodeType { tag, text };
		NodeType type;
		std::string val;
	};
	struct Tag: public Node
	{
		Tag(const std::string& val)
		{
			this->val = val;
			type = NodeType::tag;
		}
		~Tag(){}
	};
	struct Text : public Node
	{
		Text(const std::string& val)
		{
			this->val = val;
			type = NodeType::text;
		}
	};
	static Node* make_text(const std::string& val)
	{ 
		return  new Text(val);
	}
	static Node* make_tag(const std::string& val)
	{
		return new Tag(val);
	}

	std::string change_spaces(const std::string& line);
	std::string return_spaces(const std::string& line);
	std::vector<Node*> parse(const std::string& line);
	std::vector<std::string> split(std::string s, std::string delimiter);
	std::string put_new_line_ch(const std::string& line);
	std::string prepare(const std::string& line);
	tags_str get_tag(const std::string& line);
	bool is_spaceful(const std::string& line);
};
#endif //PARSER_H