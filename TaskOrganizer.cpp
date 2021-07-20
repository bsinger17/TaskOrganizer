// TaskOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "TaskOrganizer.h"
#include "Task.h"

enum class TaskState { complete, in_progress, on_hold, new_task };

std::map<TaskState, std::string> TaskStateToString{ {TaskState::complete, "complete"},
    {TaskState::in_progress, "in_progress"}, {TaskState::on_hold, "on_hold"}, {TaskState::new_task, "new_task"} };

std::map<std::string, TaskState> StringToTaskState{ {"complete", TaskState::complete},
    {"in_progress", TaskState::in_progress}, {"on_hold", TaskState::on_hold}, {"new_task", TaskState::new_task} };

tm stringToTm(std::stringstream& stream)
{
    int value = 0;
    std::vector<int> read_buffer;
    tm due_date;
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
        due_date.tm_mon = read_buffer[0] - 1; //tm_mon is indexed at 0
        due_date.tm_mday = read_buffer[1]; //day of month
        due_date.tm_year = read_buffer[2] - 1900; //tm_year is number of years after 1900
    
        //need these members to be nonzero to print a tm
        due_date.tm_sec = 1;
        due_date.tm_min = 1;
        due_date.tm_hour = 1;
        return due_date;
    }
}




//reads in string from user and returns a tm with corresponding month, day, year
tm readDueDateFromUser()
{
    std::string input_string = "";

    std::cout << "\nEnter a due date for the new task. Please use (mm/dd/yyyy) format: ";
    std::getline(std::cin, input_string);
    std::stringstream stream(input_string);

    return stringToTm(stream);
}


Task createTask()
//prompts user for info needed to create a new task. Returns that task.
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

    return Task(name, tm_date, priority, ts, 0);
}

int main()
{
    //open and read contents from file
    std::string file_line;
    std::string file_task_name;
    std::string file_task_date; //convert to tm
    int file_task_priority;
    std::string file_task_state; //convert to TaskState
    int file_task_id;

    std::ifstream fileInput;
    fileInput.open("task_file.txt");

    //read data in and store in a data structure
    std::vector<Task> task_store{};
    while (std::getline(fileInput, file_line))
    {
        std::stringstream ss(file_line);
        ss >> file_task_name >> file_task_date >> file_task_priority >> file_task_state >> file_task_id;

        std::stringstream ss_date(file_task_date);
        task_store.push_back(Task(file_task_name, stringToTm(ss_date), file_task_priority, StringToTaskState[file_task_state], file_task_id));
    }

    //TODO: sort tasks by priority value
    //std::cout << task_store[1].get_due_date().tm_mon << "\n";

    //TODO: use string stream formatting to fix user_prompt
    std::string user_prompt = "Welcome to Ben's Task Organizer!\n\nTo begin, please enter one of the following commands:\n1) View Current Task List\n2) Create a new Task\n3) Update the status of a Task\n4) Check Tasks Status\nh) For help\nq) To terminate program\n";

    std::cout << "Welcome to Ben's Task Organizer!\n\nTo begin, please enter one of the following commands:\n"
        << "1) View Current Task List\n"
        << "2) Create a new Task\n"
        << "3) Update the status of a Task\n"
        << "4) Check Tasks Status\n"
        << "h) For help\n"
        << "q) To terminate program\n"
        << "\n>>";

    char input;

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
            temp.set_task_id_number(task_store.size() + 100); //tasks will be organized as 100,101,102,etc.
            task_store.push_back(temp);
            temp.print_task_details();
            break;
        }
        case '3':
            //update a task
            //tasks in the "completed" state should deleted
            std::cout << "\nSelect a task to update:\n";
            break;
        case '4':
            //check and print tasks status
            std::cout << "\nThe following tasks are past due: \n";
            for (auto i : task_store)
            {
                if (i.is_past_due())
                {
                    i.print_task_details();
                }
            }
            std::cout << "\nThe following tasks are due within 10 days: \n";
            for (auto i : task_store)
            {
                if (i.days_remaining() < 10 && !(i.is_past_due()))
                {
                    i.print_task_details();
                }
            }
            break;
        case 't':
            //testing case
            task_store[task_store.size() - 1].days_remaining();
        case 'h':
            //help instructions
            std::cout << user_prompt;
            break;
        case 'q':
            //quit program       
            goto terminate_task_org;
        default:
            std::cout << "\nno valid input, enter \'h\' for help\n";
            break;
        }
        std::cout << "\n>>";
    }

terminate_task_org:
    //file output
    std::ofstream fileOutput;
    fileOutput.open("task_file.txt");

    //write data to txt file
    for (auto j : task_store)
    {
        if (!(j.get_task_state() == TaskState::complete)) //omit tasks that are in "complete" state
        {
            //convert date to printable time
            std::string date_output = std::to_string(j.get_due_date().tm_mon + 1) + "/" + std::to_string(j.get_due_date().tm_mday) + "/" + (std::to_string(j.get_due_date().tm_year + 1900));

            //ExampleTask1 01/01/2030 1 new_task 100
            fileOutput << j.get_task_name() << " "
                << date_output << " "
                << j.get_task_priority() << " "
                << TaskStateToString[j.get_task_state()] << " "
                << j.get_task_id_number() << "\n";
        }
    }
    fileOutput.close();
    return 0;
}


