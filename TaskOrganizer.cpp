// TaskOrganizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TaskOrganizer.h"
#include "Task.h"

enum class TaskState { complete, in_progress, on_hold, new_task };

//string <--> TaskState converters
std::map<TaskState, std::string> TaskStateToString{ {TaskState::complete, "complete"},
    {TaskState::in_progress, "in_progress"}, {TaskState::on_hold, "on_hold"}, {TaskState::new_task, "new_task"} };
std::map<std::string, TaskState> StringToTaskState{ {"complete", TaskState::complete},
    {"in_progress", TaskState::in_progress}, {"on_hold", TaskState::on_hold}, {"new_task", TaskState::new_task} };

//for displaying late and upcoming tasks
void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//converts string user input to tm
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

//prompts user for info needed to create a new task. Returns that task.
Task createTask()
{
    std::string name;
    std::string date = "";
    int priority = 0;
    TaskState ts = TaskState::new_task;

    std::cout << "\nEnter a name for the new task: ";
    std::getline(std::cin, name);
    tm tm_date = readDueDateFromUser();
    std::cout << "\nEnter a priority value (1 thru 5, 1 being highest priority) for the new task: ";
    std::cin >> priority;

    return Task(name, tm_date, priority, ts, 0);
}

//displays important task status to user
//TODO: only display the prompts if something is due? would require looping twice
void checkTaskStatus(const std::vector<Task>& task_store)
{
    std::cout << "\nThe following tasks are past due: \n\n";
    color(4); //red text
    for (auto i : task_store)
    {
        if (i.is_past_due())
        {
            i.print_task_details_lite();
        }
    }
    color(7); //white text
    std::cout << "\nThe following tasks are due within 10 days: \n\n";
    color(11);
    for (auto i : task_store)
    {
        if (i.days_remaining() < 10 && !(i.is_past_due()))
        {
            i.print_task_details_lite();
        }
    }
    color(7); //cyan text
}

//sorts Tasks by priority value
void sortTasks(std::vector<Task>& task_store)
{
    std::sort(task_store.begin(), task_store.end(), [](Task a, Task b) {return a.get_task_priority() < b.get_task_priority(); });
}

//read contents from file into vector and return it
std::vector<Task> readFileData(std::string filename) 
{
    std::string file_line;
    std::string file_task_name;
    std::string file_task_date; //convert to tm
    int file_task_priority;
    std::string file_task_state; //convert to TaskState
    int file_task_id;

    std::ifstream fileInput;
    fileInput.open(filename);

    //read data in and store in a data structure
    std::vector<Task> task_store{};
    while (std::getline(fileInput, file_line))
    {
        std::stringstream ss(file_line);
        ss >> file_task_name >> file_task_date >> file_task_priority >> file_task_state >> file_task_id;

        std::stringstream ss_date(file_task_date);
        task_store.push_back(Task(file_task_name, stringToTm(ss_date), file_task_priority, StringToTaskState[file_task_state], file_task_id));
    }
    return task_store;
}

//output processed data to file
void writeFileData(std::string filename, const std::vector<Task>& task_store)
{
    std::ofstream fileOutput;
    fileOutput.open(filename);

    //write data to txt file
    for (auto j : task_store)
    {
        if (!(j.get_task_state() == TaskState::complete)) //omit tasks that are in "complete" state
        {
            //convert date to printable time
            std::string date_output = std::to_string(j.get_due_date().tm_mon + 1) + "/"
                + std::to_string(j.get_due_date().tm_mday) + "/" + (std::to_string(j.get_due_date().tm_year + 1900));

            //text file store in the format: ExampleTask1 01/01/2030 1 new_task 100
            fileOutput << j.get_task_name() << " "
                << date_output << " "
                << j.get_task_priority() << " "
                << TaskStateToString[j.get_task_state()] << " "
                << j.get_task_id_number() << "\n";
        }
    }
    fileOutput.close();
}

int main()
{
    char input;
    std::string filename = "task_file.txt";
    std::string line_break = "\n=====================================\n=====================================\n\n"; //better way to do this?
    std::string user_prompt = "Welcome to Ben's Task Organizer!\n"
        "\nTo begin, please enter one of the following commands:"
        "\n1) View Current Task List\n2) Create a new Task"
        "\n3) Update the status of a Task"
        "\n4) Check Tasks Status"
        "\nh) For help"
        "\nq) To terminate program\n";

    std::vector<Task> task_store = readFileData(filename);
    sortTasks(task_store);
    checkTaskStatus(task_store);

    //prompt the user at startup
    std::cout << line_break << user_prompt << "\n>>";

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
            sortTasks(task_store);
            break;
        }
        case '3':
            //update a task
            //tasks in the "completed" state are removed upon termination
            std::cout << "\nSelect a task to update:\n";
            break;
        case '4':
            //check and print tasks status
            checkTaskStatus(task_store);
            break;
        case 'h':
            //help instructions
            std::cout << user_prompt;
            break;
        case 'q':
            //quit program       
            goto terminate_task_org;
        default:
            std::cout << "\nInvalid input, enter \'h\' for help\n";
            break;
        }
        std::cout << "\n>>";
    }

terminate_task_org:
    writeFileData(filename, task_store);
    return 0;
}


