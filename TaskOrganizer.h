#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <map>
//#include <cmath>
//#include <list>
//#include <forward_list>
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

