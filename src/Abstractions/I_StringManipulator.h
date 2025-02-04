#ifndef I_STRINGMANIPULATOR_H
#define I_STRINGMANIPULATOR_H
#include <string>

class I_StringManipulator {
public:
    virtual ~I_StringManipulator() = default;

    virtual void manipulate(std::string &srt) const = 0;
};
#endif
