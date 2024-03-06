#include <cstring>
#include "tasks.h"

// TODO: implement functions from tasks.h

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

Parser any_of(const std::vector<Parser> &) {
    return Parser();
}

Parser sequence(const std::vector<Parser> &) {
    return Parser();
}

Parser repeat(const Parser &, int) {
    return Parser();
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