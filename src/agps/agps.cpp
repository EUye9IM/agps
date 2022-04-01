#include <agps/agps.h>

namespace agps {
Parser::Parser(){};
Parser::~Parser(){};
void Parser::add(Type type, char short_name, const char *long_name,
				 bool is_necessary, Value default_value,
				 bool (*check_func)(Value)){};
void Parser::parse(int srgc, const char **argv){};
bool Parser::success() { return _b_sucess; };
} // namespace agps