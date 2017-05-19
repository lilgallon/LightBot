#ifndef PROGRAMHANDLER_H
#define PROGRAMHANDLER_H
#include "ProgramBox.h"
#include "Robot.h"
#include "Grid.h"

class ProgramHandler
{
private:
    ProgramBox* m_program;
    Robot* m_robot;
    bool m_robot_jumped;
    Grid* m_grid;

    void moveForward();

public:
    ProgramHandler(ProgramBox *program, Robot *robot, Grid* grid);

    void runProgram();
};

#endif // PROGRAMHANDLER_H
