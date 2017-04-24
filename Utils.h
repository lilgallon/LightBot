#ifndef UTILS_H
#define UTILS_H
#include <ctime>
#include <string>

class Utils
{
public:
    static float abs(float value);
    static std::string getTime();
    enum class State { HOME, CREDITS, LEVEL_SELECTION, IN_GAME, LEVEL_EDITOR, END_GAME, IDLE};

private:
    Utils() = default;
};

#endif // UTILS_H
