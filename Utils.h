#ifndef UTILS_H
#define UTILS_H
#include <ctime>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Utils
{
public:
    // Absolute value
    static float abs(const float &value);
    // Get the time for the outputs
    static std::string getTime();
    // Get PI (same method as Math.h)
    static constexpr float PI = 3.14159265358979323846; // It is wrote like that in the math library btw
    // State class is defined here to be used in any other classes
    enum class State { HOME, CREDITS, LEVEL_SELECTION, IN_GAME, LEVEL_EDITOR, END_GAME, IDLE };
    // Action class of action, used un other classes
    enum class Action { FORWARD, TURN_CLOCKWISE, TURN_COUNTERCLOCK, LIGHT, JUMP, PROG_P1, PROG_P2, NONE};
    // Orientation of the robot
    enum class Orientation { UP, DOWN, UP_LEFT, DOWN_LEFT, UP_RIGHT, DOWN_RIGHT, NONE};
    // Type prog
    enum class TypeProg {MAIN, P1, P2};

    // Repertories
    static const std::string FONT_PATH ;//= "resources/fonts/";
    static const std::string IMG_PATH ;//= "resources/images/";
    static const std::string LEVELS_PATH ;//= "levels/";

    // Splits a string into a container
    static std::vector<std::string> split(const std::string& str, const std::string& delim);

    // Change easily the orientation
    static Orientation turn_clockwise(Orientation actual_orientation);
    static Orientation turn_counterclock(Orientation actual_orientation);

    static sf::Vector2f positionToPixel(const sf::Vector2f &pos_in_index, const sf::Vector2f &gap, const int &radius);
private:
    Utils() = default;
};

//std::string Utils::FONT_PATH = "resources/fonts/";
//std::string Utils::IMG_PATH = "resources/images/";
//std::string Utils::LEVELS_PATH = "levels/";

#endif // UTILS_H
