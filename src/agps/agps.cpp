#include <agps/agps.h>
#include <cstring>
namespace agps {
Argument::Argument() {
	set(nullptr, Type::FLAG, 0, nullptr, nullptr, false, Value{0}, nullptr,
		false, Value{0});
}
Argument::Argument(Argument *next_argument, Type type, char short_name,
				   const char *long_name, const char *infomation,
				   bool is_necessary, const Value &default_value,
				   bool (*check_func)(const Value &), bool is_exist,
				   const Value &real_valuel) {
	set(next_argument, type, short_name, long_name, infomation, is_necessary,
		default_value, check_func, is_exist, real_valuel);
}
void Argument::set(Argument *next_argument, Type type, char short_name,
				   const char *long_name, const char *infomation,
				   bool is_necessary, const Value &default_value,
				   bool (*check_func)(const Value &), bool is_exist,
				   const Value &real_valuel) {
	this->type = type;
	this->short_name = short_name;
	this->long_name.set(long_name);
	this->infomation.set(infomation);
	this->is_necessary = is_necessary;
	this->default_valuel = default_valuel;
	this->check_func = check_func;
	this->next_argument = next_argument;
	this->is_exist = is_exist;
	this->real_valuel = real_valuel;
}
Parser::Parser() {
	_b_sucess = false;
	_argument_list = nullptr;
	_pc_usage = nullptr;
}
Parser::~Parser() { reset(); }
void Parser::add(Type type, char short_name, const char *long_name,
				 const char *infomation, bool is_necessary,
				 const Value &default_value,
				 bool (*check_func)(const Value &)) {
	Argument *p_new_arg = new Argument(nullptr, type, short_name, long_name,
									   infomation, is_necessary, default_value,
									   check_func, false, default_value);
	if (_argument_list == nullptr)
		_argument_list = p_new_arg;
	else {
		Argument *pointer = _argument_list;
		while (pointer->next_argument != nullptr) {
			pointer = pointer->next_argument;
		}
		pointer->next_argument = p_new_arg;
	}
	return;
}
void Parser::parse(int srgc, const char **argv) {}
bool Parser::success() const { return _b_sucess; }
Value Parser::get(char short_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (pointer->short_name == short_name)
			return pointer->real_valuel;
		pointer = pointer->next_argument;
	}
	return Value{0};
}
Value Parser::get(const char *long_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (!strcmp(pointer->long_name.cstr(), long_name))
			return pointer->real_valuel;
		pointer = pointer->next_argument;
	}
	return Value{0};
}
bool Parser::is_exist(char short_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (pointer->short_name == short_name)
			return pointer->is_exist;
		pointer = pointer->next_argument;
	}
	return false;
}
bool Parser::is_exist(const char *long_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (!strcmp(pointer->long_name.cstr(), long_name))
			return pointer->is_exist;
		pointer = pointer->next_argument;
	}
	return false;
}
void Parser::reset() {
	Argument *head = _argument_list;
	while (head != nullptr) {
		_argument_list = head->next_argument;
		delete head;
		head = _argument_list;
	}
	_b_sucess = false;
	_pc_usage = nullptr;
	return;
}
void Parser::clean() {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		pointer->is_exist = false;
		pointer->real_valuel = pointer->default_valuel;
		pointer = pointer->next_argument;
	}
	return;
}
} // namespace agps