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
			state = process_tag(doc,state, node->val);
			break;
		case Parser::Node::NodeType::text:
			process_text(doc, node->val, state);
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
	std::string font = "standard; name=Helvetica;" + std::string(" size=") + std::to_string(state.font_size);

	auto courier = doc.font_load(font.c_str());
	auto _text = state.space + text;
	doc.page().canvas().text_font(courier);

	doc.page().canvas().color("f", state.r,state.g,state.b);
	doc.page().canvas().text_rise(state.text_rise);
	doc.page().canvas().text(state.curr_x, state.curr_y, _text.c_str());
}

#define CHECK(name) check(name) and is_tag_with_arg(tag)
State TagProcessor::process_tag(Document& doc, 
								const State& state,
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
		return move_down(state);
	}
	else if (tag == "<rs>") return reset(state);
	else if (tag == "<hr>")
	{
		doc.page().canvas().rectangle(START_X, state.curr_y-10, 500, 1);
		char* m = new char('s');
		doc.page().canvas().path_paint(m);
		delete m;
		return move_down(state);
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
	else if (CHECK("str"))
	{
		auto arg = extract_tag_arguments(tag);
		if (is_number(arg))
		{
			int number = atoi(arg.c_str());
			
			State update(state);
			update.text_rise = number;
			return update;
		}
	}
	else if (CHECK("fs"))
	{
		auto arg = extract_tag_arguments(tag);
		if (is_number(arg))
		{
			auto size = atoi(arg.c_str());
			if (size < 0)error(arg + " must be a positive number!");

			State update(state);
			update.font_size = size;
			return update;
		}
		else
		{
			error(arg + " is not a number!");
		}
	}
	else if (CHECK("fc"))
	{
		auto arg = extract_tag_arguments(tag)+",";
		std::vector<std::string> codes = Parser::split(arg, ",");
		for (auto n = codes.begin(); n != codes.end(); n++)
			if ((*n) == ",")codes.erase(n);
		codes.erase(--codes.end());

		if (codes.size() != 3)error("incorrect number of color codes!");
		for (auto c : codes)if (!is_number(c))error("code isn't number!");
		
		int r = atoi(codes[0].c_str());
		int g = atoi(codes[1].c_str());
		int b = atoi(codes[2].c_str());

		State update(state);
		update.r = (double)r/255;
		update.g = (double)g/255;
		update.b = (double)b/255;
		return update;

	}
	else
	{
		error(tag + " is incorrect!");
	}
}
State TagProcessor::move_down(const State& state)
{
	State update(state);
	update.curr_y -= 10;
	update.curr_x = START_X;
	return update;
}
State TagProcessor::reset(const State& state)
{
	auto x = state.curr_x;
	auto y = state.curr_y;

	return State(x, y);
}
bool TagProcessor::is_number(const std::string& number)
{
	for (int i = 0;i<number.size();i++)
	{
		auto n = number[i];
		if (i != 0) { if (!isdigit(n)) return false; }
		else if (n != '-' and !isdigit(n)) return false;

	}
	return true;
}
void TagProcessor::error(const std::string& text)
{
	std::cout << "error:" << text;
	exit(-1);
}
