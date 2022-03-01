#include"TagProcessor.h"
using namespace TagProcessor;


void TagProcessor::process_parsed_script(const std::string& document_name,
										 const std::vector<Parser::Node*>& nodes)
{
	auto doc = TagProcessor::init(document_name);
	doc.page_start(PAGE_WIDTH, PAGE_HEIGHT);

	State state(START_X, START_Y);

	for (auto& node : nodes)
	{
		switch (node->type)
		{
		case Parser::Node::NodeType::tag:
			state = process_tag(state, node->val);
			break;
		case Parser::Node::NodeType::text:
		{
			process_text(doc, node->val, state);
			state = reset(state);
		}
			break;
		}
	}

	doc.page_end();
	doc.finalize();
}
std::string TagProcessor::extract_tag_arguments(const std::string& tag)
{
	auto start = tag.find(":")+1;
	auto end = tag.find(">");

	std::string arg;
	for (int i = start; i < end; i++)
	{
		arg += tag[i];
	}
	return arg;
}
void TagProcessor::process_text(Document& doc, const std::string& text, const State& state)
{
	auto _text = state.space + text;
	std::cout << "_text" << _text << std::endl;
	doc.page().canvas().text(state.curr_x, state.curr_y, _text.c_str());
}

#define CHECK(name) check(name) and is_tag_with_arg(tag)
State TagProcessor::process_tag(const State& state,
								const std::string& tag)
{
	auto is_tag_with_arg = [&](const std::string& tag)
	{
		return tag.find(":") != std::string::npos;
	};
	auto check = [&](const std::string& tag_name)
	{
		return tag.find(tag_name) != std::string::npos;
	};
	if (tag == "<br>")
	{
		State update(state);
		update.curr_y -= 10;
		update.curr_x = START_X;
		return update;
	}
	else if (CHECK("ss"))
	{
		auto arg = extract_tag_arguments(tag);
		if (is_number(arg))
		{
			int number = atoi(arg.c_str());
			std::string space;
			for (int i = 0; i < number; i++)space += " ";


			State update(state);
			update.space = space;
			return update;
		}
		else
		{
			error(arg + " is not a number!");
		}
	}
	else
	{
		error(tag + " is incorrect!");
	}
}
State TagProcessor::reset(const State& state)
{
	auto x = state.curr_x;
	auto y = state.curr_y;

	return State(x, y);
}
bool TagProcessor::is_number(const std::string& number)
{
	for (auto& n : number)
	{
		if (!isdigit(n)) return false;
	}
	return true;
}
void TagProcessor::error(const std::string& text)
{
	std::cout << "error:" << text;
	exit(-1);
}