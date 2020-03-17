#include "JsonArray.h"
#include "JsonObject.h"
#include "JsonFunction.h"

namespace MyJson{

JsonArray & JsonArray::operator=(const JsonArray &rhs) {
    if(this != &rhs){
        token=rhs.token;
    }
    return *this;
}

bool JsonArray::parseArray() {
    int nObject=0, nArray=0;    //用于标记第n个对象或数组
    for(auto p=token.cbegin()+1; p<token.cend()-1;){
        if((*p != "{") and (*p != "[")){
            if(*p == ","){  //避免空输入，，
                std::cout << "Empty input of array before " << *p << ".\n";
                return false;
            }
            value.push_back(*p);
            if((p+1 < token.cend()-1) and (*(p+1) != ",")){ //避免没有，分割的情况
                std::cout << "Missing \",\" between " << *p << " and " << *(p+1) << ".\n";
                return false;
            }
            p+=2;
        } else if(*p == "{"){
            ++nObject;
            value.push_back((string{"object"}+to_string(nObject)));
            vector<string> temp{};
            int nBrace=1;
            auto p2=p;
            while(nBrace>0){
                temp.push_back(*p2++);
                if(*p2=="{")
                    ++nBrace;
                if(*p2=="}")
                    --nBrace;
            }
            temp.push_back(*p2);
            valueJObject[value.back()]=JsonObject{temp};
            if(!valueJObject[value.back()].parseObject())
                return false;
            if((p2+1 < token.cend()-1) and (*(p2+1) != ",")){
                std::cout << "Missing \",\" between " << *p2 << " and " << *(p2+1) << ".\n";
                return false;
            }
            p=p2+2;
        } else if(*p == "["){
            ++nArray;
            value.push_back((string{"array"}+to_string(nArray)));
            vector<string> temp{};
            int nBracket=1;
            auto p3=p;
            while(nBracket>0){
                temp.push_back(*p3++);
                if(*p3=="[")
                    ++nBracket;
                if(*p3=="]")
                    --nBracket;
            }
            temp.push_back(*p3);
            if((p3+1 < token.cend()-1) and (*(p3+1) != ",")){
                std::cout << "Missing \",\" between " << *p3 << " and " << *(p3+1) << ".\n";
                return false;
            }
            valueJArray[value.back()]=JsonArray{temp};
            if(!valueJArray[value.back()].parseArray())
                return false;
            p=p3+2;
        }
    }
    return true;
}

void JsonArray::readArray(int n, bool isEnter) {
    if(isEnter){
        //std::cout << std::endl;
        printSpace(n-1);
    }
    std::cout << "[\n";
    for(const auto &i: value){
        if(i.front() == 'a'){
            valueJArray[i].readArray(n+1, true);
        } else if(i.front() == 'o'){
            valueJObject[i].readObject(n+1, true);
        } else{
            printSpace(n);
            std::cout << i;
        }
        if(i!=value.back())
            std::cout << ",\n";
        else
            std::cout << "\n";
    }
    printSpace(n-1);
    std::cout << "]";
}

void JsonArray::showArray() {
    std::cout << "[ ";
    for(const auto &i: value)
        std::cout << i << ", ";
    std::cout << "\b\b ]\n";
}

JsonArray & JsonArray::array(const string &index) {
    valueJArray[index].showArray();
    return valueJArray[index];
}

JsonObject & JsonArray::object(const string &index) {
    valueJObject[index].showObject();
    return valueJObject[index];
}

void JsonArray::clear() {
    token.clear();
    value.clear();
    valueJObject.clear();
    valueJArray.clear();
}
}   //end namespace MyJson