// TaskOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "TaskOrganizer.h"
#include "Task.h"


enum class TaskState { complete, in_progress, on_hold, new_task };

std::map<TaskState, std::string> TaskStateToString{ {TaskState::complete, "complete"},
    {TaskState::in_progress, "in_progress"}, {TaskState::on_hold, "on_hold"}, {TaskState::new_task, "new_task"} };



int main()
{
    char input;

    //TODO: use string stream formatting to fix user_prompt
    std::string user_prompt = "Welcome to Ben's Task Organizer!\n\nTo begin, please enter one of the following commands:\n1) View Current Task List\n2) Create a new Task\n3) Update the status of a Task\nh) For help\nq) To terminate program\n";

    std::cout << "Welcome to Ben's Task Organizer!\n\nTo begin, please enter one of the following commands:\n"
        << "1) View Current Task List\n"
        << "2) Create a new Task\n"
        << "3) Update the status of a Task\n"
        << "h) For help\n"
        << "q) To terminate program\n"
        << "\n>>";

    Task t1{ "task1","1/1/2022",2,TaskState::new_task };


    while (std::cin>>input)
    {
        switch (input)
        {
        case '1':
            //view current task list
            //std::cout << "\nCurrent Task List:\n...\n...\n...";
            t1.print_task_details();
            break;
        case '2':
            //create new task
            std::cout << "\nEnter a new task:\n...\n...\n...";
            break;
        case '3':
            //update a task
            std::cout << "\nSelect a task to update:\n...\n...\n...";
            break;
        case 'h':
            //help instructions
            std::cout << user_prompt;
            break;
        case 'q':
            //quit program
            return 0;
        default:
            std::cout << "\nno valid input, enter \'h\' for help\n";
            break;
        }
        std::cout << "\n>>";




    }



}


