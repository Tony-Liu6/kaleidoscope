#include <iostream>
#include <string>
#include <cassert>
#include "Json.h"
using namespace MyJson;
using namespace std;

int main() {
    string str=R"({"name": "John Doe", "age": 18, "address": {"country" : "china", "zip-code": "10000"}, "hobby": ["basketball", "swimming"]})";
    Json json{str};
    json.readJson();
    return 0;
}
