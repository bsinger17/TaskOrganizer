#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
//#include <cmath>
//#include <list>
//#include <forward_list>
#include <map>
//#include <algorithm>
//#include <array>
//#include <regex>
//#include <random>
//#include <stdexcept>

extern enum class TaskState;
extern std::map<TaskState, std::string> TaskStateToString;


//std::string getStringForTaskState(TaskState state_val)
//{
//	std::vector<std::string> enum_strings = { "complete", "in_progress", "on_hold", "new_task" }; //bad
//	return enum_strings[int(state_val)];
//}

