#ifndef TAG_PROCESSOR_H
#define TAG_PROCESSOR_H
#include<regex>
#include<string>
#include<vector>
#include<iostream>
#include<map>
#include"jagpdf/api.h" //jagpdf
#include"Parser.h"

namespace TagProcessor
{
	using namespace jag;
	using namespace pdf;

	static const int PAGE_WIDTH  = 597.6;
	static const int PAGE_HEIGHT = 848.68;

	static const int START_X = 50;
	static const int START_Y = 800;

	struct State
	{
		State(const State& state)
		{
			curr_x = state.curr_x;
			curr_y = state.curr_y;
			space = state.space;
			text_rise = state.text_rise;
			font_size = state.font_size;
			r = state.r;
			g = state.g;
			b = state.b;
			macros = state.macros;
		}
		State(int curr_x, int curr_y)
		{
			this->curr_x = curr_x;
			this->curr_y = curr_y;
			text_rise = 0;
			font_size = 12;
			r = 0;
			g = 0;
			b = 0;
		}
		~State(){}
		int curr_x, curr_y;
		int text_rise;
		int font_size;
		std::string space;

		double r, g, b;

		std::map<std::string, std::string> macros;
	};

	inline Document init(const std::string& document_name)
	{
		return Document(pdf::create_file(document_name.c_str()));
	}

	void process_parsed_script(const std::string& document_name,
							   const std::vector<Parser::Node*>& nodes);

	State process_tag(Document& doc, const State& state, const std::string& tag);
	State reset(const State& state, Document& doc);//reset everything except pos
	State move_down(const State& state);
	void process_text(Document& doc,const std::string& text, const State& state);

	std::string extract_tag_arguments(const std::string& tag);

	bool is_number(const std::string& number);
	void error(const std::string& text);
	std::string slice(const std::string& str,int begin,int end);
	std::string apply_replacing_macro(const std::string& node, const State& state);
};
#endif