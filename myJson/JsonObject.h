#ifndef MYJSON_JSONOBJECT_H
#define MYJSON_JSONOBJECT_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cassert>

using std::vector;
using std::string;
using std::map;



namespace MyJson{
class JsonArray;
class JsonObject {
public:
    JsonObject() = default;
    explicit JsonObject(vector<string> _token): token(_token){}
    JsonObject(const JsonObject& rhs): token(rhs.token){}
    JsonObject& operator=(const JsonObject &rhs);
    bool parseObject();
    void readObject(int n, bool isEnter);
    void showObject();
    void clear();
    JsonObject& object(const string &index);
    JsonArray& array(const string &index);
private:
    vector<string> token{};
    vector<string> value{};
    map<string, string> valueString{};
    map<string, JsonObject> valueJObject{};
    map<string, JsonArray> valueJArray{};
};  //end class JsonObject
}   //end namespace MyJson



#endif //MYJSON_JSONOBJECT_H
