#ifndef UTILS_H
#define UTILS_H
#include <ctime>
#include <string>

class Utils
{
public:
    // Absolute value
    static float abs(float value);
    // Get the time for the outputs
    static std::string getTime();
    // Get PI (same method as Math.h)
    static constexpr float PI = 3.14159265358979323846; // This wrote like that in the math library btw
    // State class is defined here to be used in any other class
    enum class State { HOME, CREDITS, LEVEL_SELECTION, IN_GAME, LEVEL_EDITOR, END_GAME, IDLE};

private:
    Utils() = default;
};

#endif // UTILS_H
