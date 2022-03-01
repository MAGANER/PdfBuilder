#ifndef TAG_PROCESSOR_H
#define TAG_PROCESSOR_H
#include<regex>
#include<string>
#include<vector>
#include<iostream>
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
		}
		State(int curr_x, int curr_y)
		{
			this->curr_x = curr_x;
			this->curr_y = curr_y;
		}
		~State(){}
		int curr_x, curr_y;
		std::string space;
	};

	inline Document init(const std::string& document_name)
	{
		return Document(pdf::create_file(document_name.c_str()));
	}

	void process_parsed_script(const std::string& document_name,
							   const std::vector<Parser::Node*>& nodes);

	State process_tag(const State& state, const std::string& tag);
	State reset(const State& state);//reset everything except pos
	void process_text(Document& doc,const std::string& text, const State& state);

	std::string extract_tag_arguments(const std::string& tag);

	bool is_number(const std::string& number);
	void error(const std::string& text);

};
#endif