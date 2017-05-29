#ifndef PROGRAMHANDLER_H
#define PROGRAMHANDLER_H
#include "ProgramBox.h"
#include "Robot.h"
#include "Grid.h"

class ProgramHandler
{
private:
    // Program boxes containing the actions
    ProgramBox* m_program_main;
    ProgramBox* m_program_p1;
    ProgramBox* m_program_p2;
    Robot* m_robot;
    Grid* m_grid;
    // Attribute used to reset the jump of the robot if it went forward
    // (the robots lands only when it goes forward)
    bool m_robot_jumped_before;

    // Used to move the robot forward (called in runProgram)
    int moveForward(int result);

    // RESULT ->
    // -4 = ALL CELLS ARE NOT TURNED ON
    // -3 = FAILED (cell way too high)
    // -2 = FAILED (had to jump)
    // -1 = FAILED (out of the grid)
    // 0 = IT'S FINE FOR THE MOMENT (MAIN)
    // 1 = IT'S FINE FOR THE MOMENT (PROGRAM 1)
    // 2 = IT'S FINE FOR THE MOMENT (PROGRAM 2)

public:
    ProgramHandler(ProgramBox *program_main, ProgramBox *program_p1, ProgramBox *program_p2, Robot *robot, Grid* grid);

    int runProgram(ProgramBox* program, const unsigned int &index, int result, Theme* defaultTheme, Theme* currentActionTheme);
};

#endif // PROGRAMHANDLER_H
