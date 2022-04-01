#include <agps/const_str.h>
#include <cstring>
namespace agps {
ConstStr::ConstStr() { _str_pointer = nullptr; };
ConstStr::ConstStr(const char *str) {
	_str_pointer = nullptr;
	set(str);
};
ConstStr::~ConstStr() {
	if (_str_pointer)
		delete _str_pointer;
};
void ConstStr::set(const char *str) {
	if (_str_pointer)
		delete _str_pointer;
	if (!str)
		_str_pointer = nullptr;
	else {
		int str_len = strlen(str) + 1;
		_str_pointer = new char[strlen(str) + 1];
		strncpy(_str_pointer, str, str_len);
	}
	return;
};
const char *ConstStr::cstr() { return (const char *)(_str_pointer); };
} // namespace agps