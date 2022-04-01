#pragma once
#ifndef AGPS_AGPS_H
#define AGPS_AGPS_H

#include <agps/const_str.h>

namespace agps {
enum class Type { FLAG, INT, STRING };
union Value {
	bool Exist;
	int Int;
	const char *Str;
};
class Argument {
public:
	Argument();
	Argument(Argument *next_argument, Type type, char short_name,
			 const char *long_name, bool is_necessary, Value default_value,
			 bool (*check_func)(Value));
	~Argument();
	Type type;
	char short_name;
	ConstStr long_name;
	bool is_necessary;
	Value default_valuel;
	bool (*check_func)(Value);
	Argument *next_argument;
};
class Parser {
public:
	Parser();
	~Parser();
	void add(Type type, char short_name, const char *long_name,
			 bool is_necessary = true, Value default_value = Value{0},
			 bool (*check_func)(Value) = nullptr);
	void parse(int srgc, const char **argv);
	bool success();
	Value get(char short_name);
	Value get(const char *long_name);
	void clear();

private:
	bool _b_sucess;
	Argument *_argument_list;

}; // class Parser
} // namespace agps

#endif
