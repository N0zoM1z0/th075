// Original complete SDK provider and ordinary operation alternatives.
#include "../../.tools/msvc710/Vc7/crt/src/string.cpp"
struct OrdinaryStringFailure {
    void invalid_position() const;
    void excessive_length() const;
};
void OrdinaryStringFailure::invalid_position() const {
    throw std::out_of_range("invalid string position");
}
void OrdinaryStringFailure::excessive_length() const {
    throw std::length_error("string too long");
}
extern const unsigned long StringExceptionLayout[] = {
    sizeof(std::_String_base), sizeof(OrdinaryStringFailure),
    sizeof(std::string), sizeof(std::out_of_range), sizeof(std::length_error)
};
