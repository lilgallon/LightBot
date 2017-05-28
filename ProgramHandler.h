#ifndef PROGRAMHANDLER_H
#define PROGRAMHANDLER_H
#include "ProgramBox.h"
#include "Robot.h"
#include "Grid.h"

class ProgramHandler
{
private:
    ProgramBox* m_program_main;
    ProgramBox* m_program_p1;
    ProgramBox* m_program_p2;
    Robot* m_robot;
    Grid* m_grid;
    bool m_robot_jumped_before;

    int moveForward(int result);
    //void runSubProgram(std::vector<Button *> actions);

public:
    ProgramHandler(ProgramBox *program_main, ProgramBox *program_p1, ProgramBox *program_p2, Robot *robot, Grid* grid);

    //int runProgram(ProgramBox *program);
    int runProgram(ProgramBox* program, const unsigned int &index, int result, Theme* defaultTheme, Theme* currentActionTheme);
};

#endif // PROGRAMHANDLER_H
