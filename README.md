# 简介

学习C++后一直想找简单的项目练习一下，再三斟酌下，选择了JSON解析器这个项目入手。本项目旨在对用户输入的JSON数据进行格式检查，并将其格式化输出。下面我将简单介绍一下本项目。

## 构成

### `Json`类：`Json`

处理用户输入的字符串，并转化为token流。根据token流判断并生成对象或数组。

数据成员包括：

- `vector<string> token`
- `JsonObject jObject`
- `JsonArray jArray`

成员函数包括：

- `bool check()`
  格式预检查；
- `bool strToToken()`
  将数据流转化为所需要的`token`流；
- `bool parseJson()`
  对`token`流进行解析，输入到`jObject`或`jArray`中；
- `void readJson()`
  将解析完成的`Json`对象以简单的格式输出；
- `void showJson()`
  将解析完成的`Json`对象以完整的格式输出；
- `void writeJson()`
  向`Json`对象写入输入流；
- `void clear()`
  清空`Json`对象；

### 数组类：`JsonArray`

处理输入的token流。根据token流判断并生成对象或数组。

数据成员包括：

- `vector<string> token`
- `map<string, JsonObject> valueJObject`
  保存该数组中的对象；
- `map<string, JsonArray> valueJArray`
  保存该数组中的数组；

成员函数包括：

- `bool parseArray()`
  解析输入的`token`流；
- `void showArray()`
- `void clear()`
  清空`JsonArray`对象；

### 对象类：`JsonObject`

处理输入的token流。根据token流判断并生成对象或数组。

数据成员包括：

- `vector<string> token`
- `vector<string> value`
- `map<string, string> valueString`
  保存该对象中的键值对；
- `map<string, JsonObject> valueJObject`
  保存该对象中的对象；
- `map<string, JsonArray> valueJArray`
  保存该对象中的数组；

成员函数包括：

- `bool parseObject()`
  解析输入的`token`流；
- `void showObject()`
- `void clear()`
  清空`JsonObject`对象；

### 判断函数

- `bool isDigit(std::string &str)`
  检查字符串表示数字的格式；
- `bool isBool(const std::string &str)`
  检查字符串表示布尔值的格式；
- `bool isString(const std::string &str)`
  检查字符串表示"字符串"的格式；

## 功能

1. 检查`Json`数据的格式，包括{}[]是否匹配，字符串类型、`bool`值类型、数字类型是否正确；
2. 将输入`Json`数据打印到屏幕上；

## 举例

1. 
   ~~~C++
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
   //输出：
   /*
   {
       "name" : "John Doe",
       "age" : 18,
       "address" : {
           "country" : "china",
           "zip-code" : "10000"
       },
       "hobby" : [
           "basketball",
           "swimming"
       ]
   }
   */
   ~~~

2. ~~~C++
   int main() {
   	string str=R"({"name": "John Doe", "age": 18, "address": {"country" : "china", "zip-code": "10000"}, "hobby": ["basketball", "swimming"]})";    
       Json json{str};
       json.showJson();
       json.object("\"address\"");
       json.array("\"hobby\"");
       return 0;
   }
   //输出：
   /*
   {
   "name" : "John Doe",
   "age" : 18,
   "address" : object,
   "hobby" : array
   }
   {
   "country" : "china",
   "zip-code" : "10000"
   }
   [ "basketball", "swimming" ]
   */
   ~~~

3. ~~~C++
   int main() {
       Json json{};
       json.writeJson();
       json.readJson();
       return 0;
   }
   //输入：
   /*
   {"name": "John Doe", "age": 18, "address": {"country" : "china", "zip-code": "10000"}, "hobby": ["basketball", "swimming"]}
   */
   //输出：
   /*
   {
       "name" : "John Doe",
       "age" : 18,
       "address" : {
           "country" : "china",
           "zip-code" : "10000"
       },
       "hobby" : [
           "basketball",
           "swimming"
       ]
   }
   */
   ~~~

