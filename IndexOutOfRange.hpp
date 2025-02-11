#ifndef LR2_INDEX_OUT_OF_RANGE
#define LR2_INDEX_OUT_OF_RANGE

#include <string>
using namespace std;
class IndexOutOfRange : public std::exception {
    std::string message_;

public:
    explicit IndexOutOfRange(const std::string &message) : message_(message) {}

    explicit IndexOutOfRange(const char *message) : message_(message) {}

    const char *what() const noexcept override {
        return message_.c_str();
    }
};
#endif
