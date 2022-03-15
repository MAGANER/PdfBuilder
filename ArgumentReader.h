#ifndef ARGUMENT_READER_H
#define ARGUMENT_READER_H
#include<string>
#include<iostream>
using namespace std;
namespace ArgumentReader
{
	enum class ArgType
	{
		script,
		document,
		macro_file,
		nothing,
		error,	
	};
	ArgType get_type(const std::string& arg)
	{
		if (arg.find("-s") != std::string::npos)	  return ArgType::script;
		else if (arg.find("-d") != std::string::npos) return ArgType::document;
		else if (arg.find("-m") != std::string::npos) return ArgType::macro_file;
		else if (arg.empty()) return ArgType::nothing;
		else return ArgType::error;
	}
	struct Args
	{
		Args(const std::string& sp,
			 const std::string& dp,
			 const std::string& mp)
		{
			script_path     = sp;
			document_path   = dp;
			macro_file		= mp;
		}
		~Args(){}
		std::string script_path, document_path,macro_file;
	};

	Args* read_args(int argc, char** argv)
	{
		if (argc == 1)return nullptr;
		if (argc > 4) return nullptr;
		if (argc != 3 && argc !=4)return nullptr;
		
		using namespace std;
		string args[]{ string(argv[1]),string(argv[2]), argc == 4 ? string(argv[3]) : "" };
		string script, doc, macro;

		for (int i = 0; i < 3; i++)
		{
			switch (get_type(args[i]))
			{
			case ArgType::script:      script = args[i].substr(2);  break;
			case ArgType::document:    doc    = args[i].substr(2);  break;
			case ArgType::macro_file:  macro  = args[i].substr(2);  break;
			case ArgType::error:return nullptr;
			};
		}
		if (script.empty() || doc.empty()) return nullptr; //these are very important args
		return new Args(script, doc,macro);

	}
};
#endif //ARGUMENT_READER_H
