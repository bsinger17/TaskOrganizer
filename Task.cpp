#include "Task.h"

Task::Task(std::string name, std::string date, int priority, TaskState state)
	:task_name{ name }, due_date{ date }, task_priority{ priority }, task_state{ state }
{
}


void Task::print_task_details() const
{
	std::cout << "\nTask Name: " << task_name
		<< "\nTask Due Date: " << due_date
		<< "\nTask Priority Value: " << std::to_string(task_priority)
		<< "\nTask State: " << TaskStateToString[task_state] 
		<< std::endl;
}

//getters
std::string Task::get_due_date() const
{
	return due_date;
}

int Task::get_task_priority() const
{
	return task_priority;
}

TaskState Task::get_task_state() const
{
	return task_state;
}

//setters
void Task::set_task_due_date(const std::string& date) //TODO: implement with a Date class
{
	due_date = date;
}

void Task::set_task_priority(int priority_value)
{
	if(priority_value < 0) task_priority = 0;
	else if(priority_value > 5) task_priority = 5;
	else task_priority = priority_value;
}

void Task::set_task_state(TaskState ts)
{
	task_state = ts;
}


//TODO: implement helper function
//bool is_past_due() const
//{
//
//}

//TODO: implement helper function
//int days_remaining(const std::string& name) const
//{
//
//}