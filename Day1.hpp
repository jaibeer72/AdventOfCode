//
// Created by Jaibeer Dugal on 04/12/2023.
//

#ifndef ADVENTOFCODE_DAY1_HPP
#define ADVENTOFCODE_DAY1_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> ReadLines(const char* filename){
    vector<string> lines;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    unordered_map<string , int> map = {
            {"one",1},
            {"two",2},
            {"three",3},
            {"four",4},
            {"five",5},
            {"six",6},
            {"seven",7},
            {"eight",8},
            {"nine",9},
    };

    vector<string> lines = ReadLines("../input.txt");
    int n = lines.size();
    vector<int> nums;
    int iNum1,iNum2 = -1;
    for(int i = 0; i < n ; i++)
    {
        int lineLen = lines[i].length();
        int num1 = 0;
        for(int j =0; j < lineLen;j++){
            if(isdigit(lines[i][j])){
                num1 = lines[i][j] - '0';
                iNum1 = j;
                break;
            }
        }
        int num2 = 0;
        for(int j = lineLen-1 ; j >= 0 ; j--){
            if(isdigit(lines[i][j])){
                num2 = lines[i][j] - '0';
                iNum2 = j;
                break;
            }
        }
        for(auto& word : map){
            size_t firstPos = lines[i].find(word.first);
            size_t lastPos = lines[i].rfind(word.first);
            if(firstPos != string::npos && firstPos < iNum1){
                num1 = word.second;
                iNum1 = firstPos;
            }
            if(lastPos != string::npos && lastPos > iNum2){
                num2 = word.second;
                iNum2 = lastPos;
            }
        }
        nums.push_back((num1* 10 )+num2);
    }

// sum of all the numbers
    int sum = 0;
    for(int i = 0; i < nums.size(); i++){
        sum += nums[i];
    }
    std::cout<< "sum = " << sum << std::endl;
    return 0;
}
#endif //ADVENTOFCODE_DAY1_HPP
