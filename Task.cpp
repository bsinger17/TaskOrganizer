#include "Task.h"

Task::Task(std::string name, tm date, int priority, TaskState state, int id)
	:task_name{ name }, due_date{ date }, task_priority{ priority }, task_state{ state }, task_id_number{ id }
{
}

void Task::print_task_details() const //TODO: make this sort the data structure by priority value
{
	tm date_output = due_date; //making a copy
	std::mktime(&date_output);

	std::cout << "\nTask ID: " << task_id_number
		<< "\nTask Name: " << task_name 
		<< "\nTask Due Date: " << (std::asctime(&date_output))
		<< "Task Priority Value: " << std::to_string(task_priority)
		<< "\nTask State: " << TaskStateToString[task_state] << std::endl;
}

//getters
std::string Task::get_task_name() const
{
	return task_name;
}

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

int Task::get_task_id_number() const
{
	return task_id_number;
}

//setters
void Task::set_task_due_date(int year, int month, int day)
//handling years since 1900, month 0 indexing in this function. Data will be entered the conventional way:
//for example, year will be entered as 2021, month of june will be entered as 6
{
	due_date.tm_year = year-1900;
	due_date.tm_mon = month - 1;
	due_date.tm_mday = day;
}

void Task::set_task_priority(int priority_value)
//1 is considered highest priority
//forces a value between 1 and 5
{
	if(priority_value < 1) task_priority = 1;
	else if(priority_value > 5) task_priority = 5;
	else task_priority = priority_value;
}

void Task::set_task_state(TaskState ts)
{
	task_state = ts;
}

void Task::set_task_id_number(int id)
{
	task_id_number = id;
}

//helper functions
bool Task::is_past_due() const
{
	//get and print current time in string format
	const std::time_t current_time = std::time(nullptr);
	//std::cout << std::asctime(std::localtime(&current_time));

	std::tm ddate{ due_date }; //make copy of due_date since the member is const
	time_t converted_ddate = std::mktime(&ddate);

	return (0 >= std::difftime(converted_ddate, current_time)); //task is past due if diff < 0
}

int Task::days_remaining() const
//returns a negative value if past due
{
	//get current time
	const std::time_t current_time = std::time(nullptr);

	std::tm ddate{ due_date }; //make copy of due_date since the member is const
	time_t converted_ddate = std::mktime(&ddate);

	//we never want to round up here so that tasks are completed ahead of the due_date
	return int((std::difftime(converted_ddate, current_time)) / ONE_DAY); 
}