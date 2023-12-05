//
// Created by Jaibeer Dugal on 05/12/2023.
//

#ifndef ADVENTOFCODE_DAY2_HPP
#define ADVENTOFCODE_DAY2_HPP
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
struct gameSet{
    int red = 0 , green =0 , blue  = 0;
};
struct game{
    int id = 0;
    int sets = 0;
    // each of the balls in the set
    vector<gameSet> gameSets;
};


// Line processing funtion;
// line is ; separated for each set
// we need to accumilate each of the balls
// The Elf would first like to know which games would have been possible
// if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
void processLines(vector<string> lines , vector<game>& games){
    for(string line : lines){
        // line constitution Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
        // get game id only the number
        // the game id can also go into
        game g;
        string gameIdString, restOfLine;
        getline(istringstream(line) , gameIdString , ':');

        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            restOfLine = line.substr(colonPos + 1);
        }

        //eraseing the "Game" from the string
        gameIdString.erase(0,5);
        g.id = stoi(gameIdString);

        istringstream iss(restOfLine);
        string set;
        while(getline(iss , set , ';')){
            istringstream iss2(set);
            string color;
            int red=0,green=0,blue=0;
            while(getline(iss2,color,',')){
                color.erase(0,1);
                int countPos = color.find_first_of(" ");
                string countStr = color.substr(0, countPos);
                countStr.erase(remove_if(countStr.begin(), countStr.end(), [](unsigned char c){ return !isdigit(c); }), countStr.end());
                int count = std::stoi(countStr);
                if(color.find("red") != string::npos){
                    red += count;
                }
                else if(color.find("green") != string::npos){
                    green += count;
                }
                else if(color.find("blue") != string::npos){
                    blue += count;
                }
            }
            g.gameSets.push_back({red,green,blue});
        }
        games.push_back(g);
    }
}

vector<int> PowerSets(vector<game> games){
    //getting the minimum numbers of balls required to play a game ?

    vector<int> result;
    for(auto& g : games)
    {
        int red= INT_MIN, green = INT_MIN  , blue = INT_MIN;
        for (auto &set: g.gameSets)
        {
            if (set.red > red)
            {
                red = set.red;
            }
            if (set.green > green)
            {
                green = set.green;
            }
            if (set.blue > blue)
            {
                blue = set.blue;
            }
        }
        result.push_back((red* green * blue));
    }
    return  result; // return the power set
}

int main(int args , char* argv[])
{
    auto lines = ReadLines("../input2.txt");
    vector<game> games;
    processLines(lines , games);
    int sum =0;
    for(auto& g : games){
        bool valid = true;
        for(auto &set : g.gameSets){
            if(set.red > 12 || set.green > 13 || set.blue > 14){
                valid = false;
                break;
            }
        }
        if(valid){
            sum += g.id;
        }
    }

    cout<< "sum = " << sum << endl;
    sum = 0;
    auto powerSets = PowerSets(games);
    for(auto& p : powerSets){
        sum += p;
        cout<< p << endl;
    }
    cout<< "sum = " << sum << endl;

    std::cout << "Hello World" << std::endl;
    return 0;
}
#endif //ADVENTOFCODE_DAY2_HPP
