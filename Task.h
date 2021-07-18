#pragma once
#include "TaskOrganizer.h"


class Task
{
public:
	Task(std::string name, std::tm date, int priority, TaskState state, int id=0);

	//TODO: update these to use pointers?
	//getters
	void print_task_details() const;
	tm get_due_date() const;
	int get_task_priority() const;
	TaskState get_task_state() const;
	int get_task_id_number() const;

	//setters
	void set_task_due_date(int year, int month, int day); //TODO: implement with a Date class
	void set_task_priority(int priority_value);
	void set_task_state(TaskState ts);
	void set_task_id_number(int id);

	//helper functions
	bool is_past_due() const;
	int days_remaining() const;


private:
	int task_id_number;
	std::string task_name;
	std::tm due_date; //TODO: implement a date class? how will you compare this to other dates?
	int task_priority = 0; //TODO: make it so this can only be a value b/t 0-5
	TaskState task_state; 
};

