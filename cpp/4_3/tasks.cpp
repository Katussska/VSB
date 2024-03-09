#include <cstring>
#include "tasks.h"

Parser create_char_parser(char c) {
    return Parser([c](const char *input) -> const char * {
        if (input && *input == c) {
            return input + 1;
        }
        return nullptr;
    });
}

Parser regex_match(const std::string &str) {
    std::regex regex(str);

    return Parser([=](const char *input) {
        std::cmatch match;

        if (std::regex_search(input, match, regex) && match.position() == 0) {
            return input + match.length();
        }

        return static_cast<const char *>(nullptr);
    });
}


Parser skip_ws() {
    return Parser([](const char *input) -> const char * {
        for (int i = 0; input[i] != '\0'; ++i) {
            if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n' && input[i] != '\r') {
                return input + i;
            }
        }

        return input + strlen(input);
    });
}

Parser any_of(const std::vector<Parser> &parsers) {
    return Parser([parsers](const char *input) -> const char * {
        for (const auto &parser: parsers) {
            auto result = parser(input);
            if (result)
                return result;
        }
        return nullptr;
    });
}

Parser sequence(const std::vector<Parser> &parsers) {
    return Parser([parsers](const char *input) -> const char * {
        auto remaining = input;

        for (const auto &parser: parsers) {
            auto result = parser(remaining);

            if (!result)
                return nullptr;

            remaining = result;
        }
        return remaining;
    });
}

Parser repeat(const Parser &parser, int multiple) {
    return Parser([parser, multiple](const char *input) -> const char * {
        auto remaining = input;

        for (int i = 0; i < multiple; ++i) {
            auto result = parser(remaining);

            if (!result)
                return nullptr;

            remaining = result;
        }
        return remaining;
    });
}

Parser create_word_parser(const std::string &word) {
    return Parser([=](const char *input) -> const char * {
        for (size_t i = 0; i < word.size(); ++i) {
            if (input[i] != word[i]) {
                return nullptr;
            }
        }

        return input + word.size();
    });
}