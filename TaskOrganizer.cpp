// TaskOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "TaskOrganizer.h"
#include "Task.h"


enum class TaskState { complete, in_progress, on_hold, new_task };

std::map<TaskState, std::string> TaskStateToString{ {TaskState::complete, "complete"},
    {TaskState::in_progress, "in_progress"}, {TaskState::on_hold, "on_hold"}, {TaskState::new_task, "new_task"} };

Task createTask()
//prompts user to info used to create a new task. Returns that task.
{
    std::string name;
    std::string date = "";
    int priority = 0;
    TaskState ts = TaskState::new_task;

    std::cout << "\nEnter a name for the new task: ";
    std::getline(std::cin, name);
    std::cout << "\nEnter a due date for the new task: ";
    std::getline(std::cin, date);
    std::cout << "\nEnter a priority value (0 thru 5, 5 being highest priority) for the new task: ";
    std::cin >> priority;

    return Task(name, date, priority, ts);
}

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
    Task t2{ "task2","2/2/2022",2,TaskState::in_progress };
    Task t3{ "task3","10/19/2021",0,TaskState::on_hold };

    //TODO: store tasks in a file and read into a data structure
    //for now store them in a vector:

    std::vector<Task> task_store = { t1, t2, t3 };
    std::string name;

    //std::time_t result = std::time(nullptr);
    //std::cout << std::asctime(std::localtime(&result));

    while (std::cin>>input)
    {
        std::cin.ignore(1); //ignore the newline character
        switch (input)
        {
        case '1':
            for (auto i : task_store)
            {
                i.print_task_details();
            }                
            break;
        case '2':
        {
            //std::cin.ignore(1); //ignore the newline character
            //add new task to the data structure
            Task temp = createTask();
            task_store.push_back(temp);
            temp.print_task_details();
            break;
        }
        case '3':
            //update a task
            //tasks in the "completed" state should deleted
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


