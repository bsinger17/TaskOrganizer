#include "Task.h"

Task::Task(std::string name, tm date, int priority, TaskState state)
	:task_name{ name }, due_date{ date }, task_priority{ priority }, task_state{ state }
{
}


void Task::print_task_details() const
{
	tm date_output = due_date; //making a copy
	std::mktime(&date_output);
	//time_t converted_ddate = std::mktime(&date_output); //dont need this?
	//std::string dd_out = std::asctime(&date_output);

	std::cout << "\nTask Name: " << task_name 
		<< "\nTask Due Date: " << (std::asctime(&date_output))
		<< "Task Priority Value: " << std::to_string(task_priority)
		<< "\nTask State: " << TaskStateToString[task_state] << std::endl;
}

//getters
std::tm Task::get_due_date() const
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
void Task::set_task_due_date(int year, int month, int day) //TODO: implement with a Date class
//handling years since 1900, month 0 indexing in this function. Data will be entered the conventional way:
//for example, year will be entered as 2021, month of june will be entered as 6
{
	due_date.tm_year = year-1900;
	due_date.tm_mon = month - 1;
	due_date.tm_mday = day;
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
//bool Task::is_past_due() const
//{
//	//get and print current time in string format
//	const std::time_t current_time = std::time(nullptr);
//	std::cout << std::asctime(std::localtime(&current_time));
//
//	std::tm ddate{};
//	ddate.tm_year = 2020 - 1900;
//	ddate.tm_mon = 6;
//	ddate.tm_mday = 11;
//	std::mktime(&ddate);
//	time_t converted_ddate = std::mktime(&ddate);
//	std::cout << std::asctime(&ddate);
//
//	std::cout << std::difftime(current_time, converted_ddate);
//
//
//
//}

//TODO: implement helper function
//int days_remaining(const std::string& name) const
//{
//
//}