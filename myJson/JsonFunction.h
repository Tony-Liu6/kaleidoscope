#ifndef MYJSON_JSONFUNCTION_H
#define MYJSON_JSONFUNCTION_H

#include <iostream>
#include <string>
#include <algorithm>

namespace MyJson{
void printSpace(int n);
bool isDigit(std::string &str);
bool isBool(const std::string &str);
bool isString(const std::string &str);
}   //end namespace MyJson


#endif //MYJSON_JSONFUNCTION_H
