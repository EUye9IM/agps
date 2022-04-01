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
			 const char *long_name, const char *infomation, bool is_necessary,
			 const Value &default_value, bool (*check_func)(const Value &),
			 bool is_exist, const Value &real_valuel);
	void set(Argument *next_argument, Type type, char short_name,
			 const char *long_name, const char *infomation, bool is_necessary,
			 const Value &default_value, bool (*check_func)(const Value &),
			 bool is_exist, const Value &real_valuel);
	Type type;
	char short_name;
	ConstStr long_name;
	ConstStr infomation;
	bool is_necessary;
	Value default_valuel;
	bool (*check_func)(const Value &);
	Argument *next_argument;

	bool is_exist;
	Value real_valuel;
};
class Parser {
public:
	Parser();
	~Parser();
	void add(Type type, char short_name, const char *long_name,
			 const char *infomation, bool is_necessary = true,
			 const Value &default_value = Value{0},
			 bool (*check_func)(const Value &) = nullptr);
	void parse(int srgc, const char **argv);
	bool success() const;
	Value get(char short_name) const;
	Value get(const char *long_name) const;
	bool is_exist(char short_name) const;
	bool is_exist(const char *long_name) const;
	void reset();
	void clean();

private:
	bool _b_sucess;
	Argument *_argument_list;
	char *_pc_usage;

}; // class Parser
} // namespace agps

#endif
