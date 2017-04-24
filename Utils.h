#ifndef UTILS_H
#define UTILS_H
#include <ctime>
#include <string>

class Utils
{
public:
    static float abs(float value);
    static std::string getTime();
    static constexpr float PI = 3.14159265358979323846; // This wrote like that in the math library btw
    enum class State { HOME, CREDITS, LEVEL_SELECTION, IN_GAME, LEVEL_EDITOR, END_GAME, IDLE};

private:
    Utils() = default;
};

#endif // UTILS_H
