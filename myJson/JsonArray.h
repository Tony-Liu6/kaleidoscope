#ifndef MYJSON_JSONARRAY_H
#define MYJSON_JSONARRAY_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <cassert>

using std::stringstream;
using std::vector;
using std::string;
using std::map;
using std::to_string;

namespace MyJson {
class JsonObject;
class JsonArray {
public:
    JsonArray() = default;
    explicit JsonArray(vector<string> _token): token(_token){}
    JsonArray(const JsonArray &rhs): token(rhs.token){}
    JsonArray& operator=(const JsonArray &rhs);
    bool parseArray();
    void readArray(int n, bool isEnter);
    void showArray();
    void clear();
    JsonObject& object(const string &index);
    JsonArray& array(const string &index);

private:
    vector<string> token{};
    vector<string> value{};
    map<string, JsonObject> valueJObject{};
    map<string, JsonArray> valueJArray{};
};  //end class JsonArray
}   //end namespace MyJson

#endif //MYJSON_JSONARRAY_H
