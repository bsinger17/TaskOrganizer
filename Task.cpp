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


//std::string get_due_date(const std::string& name) const;
//int get_task_priority(const std::string& name) const;
//TaskState get_task_state(const std::string& name) const;
//
////setters
//std::string set_task_due_date(std::string& name);
//int set_task_priority(std::string& name);
//TaskState set_task_state(std::string& name);
//
////helper functions
//bool is_past_due(const std::string& name) const;
//int days_remaining(const std::string& name) const;