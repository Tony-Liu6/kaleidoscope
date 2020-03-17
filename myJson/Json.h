#ifndef MYJSON_JSON_H
#define MYJSON_JSON_H

#include <vector>
#include <string>
#include <stack>
#include <cctype>
#include <iostream>
#include <algorithm>
#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonFunction.h"

using std::vector;
using std::string;

namespace MyJson{
//class JsonObject;
//class JsonArray;
class Json {
public:
    Json()= default;
    Json(const string &str);
    Json& operator=(const Json &rhs);
    void readJson();    //以展开的方式展示json
    void showJson();    //以简洁的方式展示json
    JsonObject& object(const string &index);
    JsonArray& array(const string &index);
    void writeJson();
    void clear();

private:
    vector<string> token{};
    string json{}, jString{};
    JsonObject jObject{};
    JsonArray jArray{};
    bool check();
    bool strToToken();
    void printToken();
    bool parseJson();
    void Initial();

};  //end class Json
}   //end namespace MyJson


#endif //MYJSON_JSON_H
