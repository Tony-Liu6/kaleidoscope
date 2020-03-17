#include "Json.h"


namespace MyJson {

Json::Json(const string &str): json(str) {
    Initial();
}

Json & Json::operator=(const Json &rhs) {
    if(&rhs!=this){
        json=rhs.json;
        Initial();
    }
    return *this;
}

bool Json::check() {
    for(const auto &i: json){
        if(!isspace(i))
            jString.push_back(i);
    }
    //判断双引号是否成双匹配
    unsigned nDoubleQuotes=std::count(jString.begin(), jString.end(), '\"');
    if(nDoubleQuotes>0 and ((nDoubleQuotes & 1) == 1)){
        std::cout << "The \" is mismatched.\n";
        return false;
    }
    //扣掉双引号之间的内容，以免对后续判断[、{成双匹配造成干扰
    while(std::count(jString.begin(), jString.end(), '\"') > 0){
        auto p=jString.find('\"');
        auto p2=jString.find('\"', p+1);
        jString.erase(p, p2-p+1);
    }
    //判断[、{是否成双匹配
    std::stack<char> stackCurlyBraces, stackBrackets{};
    for(const auto &i: jString){
        if(i=='[')
            stackBrackets.push(i);
        else if(i==']'){
            if(stackBrackets.empty()){
                std::cout << "The ] is extra.\n";
                return false;
            } else{
                stackBrackets.pop();
            }
        } else if(i=='{')
            stackCurlyBraces.push(i);
        else if(i=='}'){
            if(stackCurlyBraces.empty()){
                std::cout << "The } is extra.\n";
                return false;
            } else{
                stackCurlyBraces.pop();
            }
        }
    }
    if(!stackBrackets.empty() or !stackCurlyBraces.empty()){
        if(!stackBrackets.empty())
            std::cout << "The [ is extra.\n";
        if(!stackCurlyBraces.empty())
            std::cout << "The { is extra.\n";
        return false;
    }
    jString.clear();
    return true;
}

bool Json::strToToken() {
    if(!check())
        return false;
    for (int i = 0; i < json.size();) {
        if (isspace(json[i])) {
            ++i;
            continue;
        } else if (json[i] == '{' or json[i] == '}' or json[i] == '[' or
                    json[i] == ']' or json[i] == ',' or json[i] == ':') {
            token.push_back(json.substr(i++, 1));
        } else if (json[i] == '\"') {
            int j=1;
            while (json[i+j] != '\"')
                ++j;
            token.push_back(json.substr(i, ++j));
            i += j;
        } else if (std::isdigit(json[i]) or json[i] == '.' or json[i] == '+' or
                    json[i] == '-') {
            int j = 0;
            while (std::isdigit(json[i+j]) or json[i+j] == '.' or json[i+j] == '+' or
                   json[i+j] == '-')
                ++j;
            std::string temp_str=json.substr(i, j);
            if(!isDigit(temp_str)){
                std::cout << "Invalid digit value: "  << json.substr(i, j) << ".\n";
                return false;
            }
            token.push_back(temp_str);
            i += j;
        } else if(std::isalpha(json[i])){
            int j=0;
            while (std::isalpha(json[i+j]))
                ++j;
            if(!isBool(json.substr(i, j))){
                std::cout << "Invalid bool value: "  << json.substr(i, j) << ".\n";
                return false;
            }
            token.push_back(json.substr(i, j));
            i += j;
        } else{
            std::cout << "Invalid input: "  << json[i] << ".\n";
            return false;
        }
    }
    return true;
}

void Json::printToken() {
    for(const auto &i: token)
        std::cout << i << " ";
    std::cout << "\nEnd Json::printToken()\n";
}

bool Json::parseJson() {
    if(token.front()=="{"){
        jObject=JsonObject{vector<string>{token.begin(), token.end()}};
        return jObject.parseObject();
    } else if(token.front()=="["){
        jArray=JsonArray{vector<string>{token.begin(), token.end()}};
        return jArray.parseArray();
    } else{
        if(token.size()>1){
            std::cout << "Invalid input.\n";
            return false;
        }
        jString=token.front();
    }
    return true;
}

void Json::readJson() {
    if(token.front()=="{"){
        jObject.readObject(1, true);
    } else if(token.front()=="["){
        jArray.readArray(1, true);
    } else{
        std::cout << jString;
    }
    std::cout << std::endl;
}

void Json::showJson() {
    if(token.front()=="{"){
        jObject.showObject();
    } else if(token.front()=="["){
        jArray.showArray();
    } else{
        std::cout << jString << std::endl;
    }
}

JsonObject& Json::object(const string &index) {
    if(token.front()=="{"){
        return jObject.object(index);
    } else if(token.front()=="["){
        return jArray.object(index);
    }
}

JsonArray& Json::array(const string &index) {
    if(token.front()=="{"){
        return jObject.array(index);
    } else if(token.front()=="["){
        return jArray.array(index);
    }
}

void Json::Initial() {
    if(!json.empty()){
        assert(strToToken());
        printToken();
        assert(parseJson());
    }
}

void Json::writeJson() {
    json.clear();
    string temp;
    while(true){
        std::cin>>temp;
        if(std::cin.eof())
            break;
        json+=temp;
    }
    Initial();
}

void Json::clear(){
    json.clear();
    token.clear();
    jString.clear();
    jObject.clear();
    jArray.clear();
}
}   //end namespace MyJson
