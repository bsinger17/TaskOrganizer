#pragma once
#include "TaskOrganizer.h"

double const ONE_DAY = 86400;

class Task
{
public:
	Task(std::string name, std::tm date, int priority, TaskState state, int id=0);

	//TODO: update these to use pointers?
	//getters
	void print_task_details() const;
	std::string get_task_name() const;
	tm get_due_date() const;
	int get_task_priority() const;
	TaskState get_task_state() const;
	int get_task_id_number() const;

	//setters
	void set_task_due_date(int year, int month, int day);
	void set_task_priority(int priority_value);
	void set_task_state(TaskState ts);
	void set_task_id_number(int id);

	//helper functions
	bool is_past_due() const;
	int days_remaining() const;

private:
	int task_id_number;
	std::string task_name;
	std::tm due_date;
	int task_priority = 0;
	TaskState task_state; 
};

