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
#include <chrono>
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
extern std::map<std::string, TaskState> StringToTaskState;

