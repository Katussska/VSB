#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <regex>

using Parser = std::function<const char *(const char *)>;

Parser create_char_parser(char);

Parser regex_match(const std::string &);

Parser skip_ws();

Parser any_of(const std::vector<Parser> &);

Parser sequence(const std::vector<Parser> &);

Parser repeat(const Parser &, int);

Parser create_word_parser(const std::string &word);