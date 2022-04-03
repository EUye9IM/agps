#include <agps/agps.h>
#include <cstdio>
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
				   const Value &real_value) {
	set(next_argument, type, short_name, long_name, infomation, is_necessary,
		default_value, check_func, is_exist, real_value);
}
void Argument::set(Argument *next_argument, Type type, char short_name,
				   const char *long_name, const char *infomation,
				   bool is_necessary, const Value &default_value,
				   bool (*check_func)(const Value &), bool is_exist,
				   const Value &real_value) {
	this->type = type;
	this->short_name = short_name;
	this->long_name.set(long_name);
	this->infomation.set(infomation);
	this->is_necessary = is_necessary;
	this->default_value = default_value;
	this->check_func = check_func;
	this->next_argument = next_argument;
	this->is_exist = is_exist;
	this->real_value = real_value;
}
Parser::Parser() {
	_b_sucess = false;
	_argument_list = nullptr;
	_pc_usage = nullptr;
	_rest_list = nullptr;
}
Parser::~Parser() { reset(); }
void Parser::add(Type type, char short_name, const char *long_name,
				 const char *infomation, bool is_necessary,
				 const Value &default_value,
				 bool (*check_func)(const Value &)) {
	Argument *p_new_arg;
	if (Type::FLAG == type)
		p_new_arg =
			new Argument(nullptr, type, short_name, long_name, infomation,
						 false, VALUE_NONE, nullptr, false, VALUE_NONE);
	else
		p_new_arg = new Argument(nullptr, type, short_name, long_name,
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
bool static _checkIfArgumentIsMatchRule(const char *arg, const Argument *rule) {
	if (strlen(arg) < 2 || arg[0] != '-')
		return false;
	if (0 == rule->short_name || arg[1] != rule->short_name || 0 != arg[2])
		if (nullptr == rule->long_name.cstr() || '-' != arg[1])
			if (strcmp(arg + 2, rule->long_name.cstr()))
				return false;
	return true;
}
void Parser::parse(int argc, const char **argv) {
	_b_sucess = true;
	int pos = 1;
	// parse arguments
	while (pos < argc && _b_sucess) {
		const char *the_arg = argv[pos];
		bool is_in_rest_set = true;
		// check if it is -*
		if (strlen(the_arg) >= 2 && the_arg[0] == '-') {
			// find the rule
			Argument *p_rule = _argument_list;
			while (p_rule != nullptr && _b_sucess) {
				if (_checkIfArgumentIsMatchRule(the_arg, p_rule)) {
					p_rule->is_exist = true;
					switch (p_rule->type) {
					case Type::INT:
						pos++;
						if (pos >= argc) {
							_b_sucess = false;
							break;
						}
						the_arg = argv[pos];
						int ret, val;
						ret = sscanf(the_arg, "%d", &val);
						if (1 != ret)
							_b_sucess = false;
						else
							p_rule->real_value.Int = val;
						break;

					case Type::STR:
						pos++;
						if (pos >= argc) {
							_b_sucess = false;
							break;
						}
						the_arg = argv[pos];
						p_rule->real_value.Str = the_arg;
						break;

					case Type::FLAG:
					default:
						p_rule->real_value.Exist = true;
						break;
					} // switch rule type
					is_in_rest_set = false;
					break;
				}
				p_rule = p_rule->next_argument;
			}				  // rule_list loop : to find which rule to match
		}					  // check if arg[pos] like -*
		if (is_in_rest_set) { // match failed
							  // 	restSetAdd();
		}
		// success
		pos++;
	} // arg_list loop

	// check all argument is ok
	Argument *p_rule = _argument_list;
	while (p_rule != nullptr && _b_sucess) {
		if (p_rule->is_necessary && p_rule->is_exist == false)
			_b_sucess = false;
		if (p_rule->check_func != nullptr &&
			!(p_rule->check_func(p_rule->real_value)))
			_b_sucess = false;
		p_rule = p_rule->next_argument;
	}
}
bool Parser::success() const { return _b_sucess; }
Value Parser::get(char short_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (pointer->short_name == short_name)
			return pointer->real_value;
		pointer = pointer->next_argument;
	}
	return VALUE_NONE;
}
Value Parser::get(const char *long_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (!strcmp(pointer->long_name.cstr(), long_name))
			return pointer->real_value;
		pointer = pointer->next_argument;
	}
	return VALUE_NONE;
}
bool Parser::isExist(char short_name) const {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		if (pointer->short_name == short_name)
			return pointer->is_exist;
		pointer = pointer->next_argument;
	}
	return false;
}
bool Parser::isExist(const char *long_name) const {
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
	if (_rest_list != nullptr)
		delete[] _rest_list;
	while (head != nullptr) {
		_argument_list = head->next_argument;
		delete head;
		head = _argument_list;
	}
	_b_sucess = false;
	_pc_usage = nullptr;
	_rest_list = nullptr;
	return;
}
void Parser::clean() {
	Argument *pointer = _argument_list;
	while (pointer != nullptr) {
		pointer->is_exist = false;
		pointer->real_value = pointer->default_value;
		pointer = pointer->next_argument;
	}
	_b_sucess = false;
	_pc_usage = nullptr;
	_rest_list = nullptr;
	return;
}
} // namespace agps