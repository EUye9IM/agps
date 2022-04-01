#pragma once
#ifndef AGPS
#define AGPS

namespace agps {
	enum class Type {
		INT,
		STR
	};
	union Value {
		int Int;
		const char* Str;
	}
	class Parser {
		public:
			Parser();
			~Parser();
			void add(
					Type type,
					char short_name,
					const char *long_name,
					bool is_necessary = true,
					Value default_value = 0,
					bool (*check_func)(Value) = nullptr
					);
			void parse(int srgc, const char **argv);
			bool success();
			// void clear();
		private:
	} // class Parser
} // namespace agps

#endif
