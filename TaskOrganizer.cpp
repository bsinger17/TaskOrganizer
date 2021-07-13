// TaskOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "TaskOrganizer.h"
#include "Task.h"


enum class TaskState { complete, in_progress, on_hold, new_task };

std::map<TaskState, std::string> TaskStateToString{ {TaskState::complete, "complete"},
    {TaskState::in_progress, "in_progress"}, {TaskState::on_hold, "on_hold"}, {TaskState::new_task, "new_task"} };


//reads in string from user and returns a tm with corresponding month, day, year
tm readDueDateFromUser()
{
    std::string input_string = "";
    std::string temp = "";
    int value = 0;
    std::vector<int> read_buffer;
    tm due_date;

    std::cout << "\nEnter a due date for the new task. Please use (mm/dd/yyyy) format: ";
    std::getline(std::cin, input_string);
    std::stringstream stream(input_string);

    while (stream >> value)
    {
        read_buffer.push_back(value);
        if (stream.peek() == '/')
            stream.ignore();

    }

    if (read_buffer.size() != 3)
    {
        //error, return empty tm
        due_date.tm_mday = 1;
        return due_date;
    }
    else
    {
        due_date.tm_mon = read_buffer[0]-1; //tm_mon is indexed at 0
        due_date.tm_mday = read_buffer[1]; //day of month
        due_date.tm_year = read_buffer[2]-1900; //tm_year is number of years after 1900
        
        //need these members to be nonzero to print a tm
        due_date.tm_sec = 1;
        due_date.tm_min = 1;
        due_date.tm_hour = 1;
        return due_date;
    }
}


Task createTask()
//prompts user to info used to create a new task. Returns that task.
{
    std::string name;
    std::string date = "";
    int priority = 0;
    TaskState ts = TaskState::new_task;

    std::cout << "\nEnter a name for the new task: ";
    std::getline(std::cin, name);
    tm tm_date = readDueDateFromUser();
    std::cout << "\nEnter a priority value (0 thru 5, 5 being highest priority) for the new task: ";
    std::cin >> priority;

    return Task(name, tm_date, priority, ts);
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

    Task t1{ "task1",tm{ 0, 0, 0, 1, 1, 121 },2,TaskState::new_task };
    Task t2{ "task2",tm{ 0, 0, 0, 19, 2, 122 },2,TaskState::in_progress };
    Task t3{ "task3",tm{ 0, 0, 0, 29, 10, 122 },0,TaskState::on_hold };

    //TODO: store tasks in a file and read into a data structure
    //for now store them in a vector:

    std::vector<Task> task_store = { t1, t2, t3 };
    std::string name;

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


