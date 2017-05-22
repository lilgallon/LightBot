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
    bool m_robot_jumped;
    Grid* m_grid;

    void moveForward();
    //void runSubProgram(std::vector<Button *> actions);

public:
    ProgramHandler(ProgramBox *program_main, ProgramBox *program_p1, ProgramBox *program_p2, Robot *robot, Grid* grid);

    void runProgram(ProgramBox* program);
};

#endif // PROGRAMHANDLER_H
