#pragma once
#include "TaskOrganizer.h"


class Task
{
public:
	Task(std::string name, std::string date, int priority, TaskState state);

	//TODO: update these to use pointers?
	//getters
	void print_task_details() const;
	std::string get_due_date(const std::string& name) const;
	int get_task_priority(const std::string& name) const;
	TaskState get_task_state(const std::string& name) const;

	//setters
	std::string set_task_due_date(std::string& name);
	int set_task_priority(std::string& name);
	TaskState set_task_state(std::string& name);

	//helper functions
	bool is_past_due(const std::string& name) const;
	int days_remaining(const std::string& name) const;


private:
	std::string task_name;
	std::string due_date; //implement a date class? how will you compare this to other dates?
	int task_priority;
	TaskState task_state;
};

