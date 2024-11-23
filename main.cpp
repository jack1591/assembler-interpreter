#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <string>
#include <cmath>
#include <map>
#include "interpreter.cpp"

using namespace std;
string input_path, bin_path, log_path,range;

int main(int argc, char* argv[]){
    
    input_path = argv[1];
    bin_path = argv[2];
    log_path = argv[3];
    range = argv[4];
    
    l = stoi(range.substr(0,range.find('-')));
    r = stoi(range.substr(range.find('-')+1,range.size()-range.find('-')-1));
    
    cout<<"Path to input file is "<<input_path<<endl;
    cout<<"Path to binary output file is "<<bin_path<<endl;
    cout<<"Path to log file is "<<log_path<<endl;
    cout<<"left is "<<l<<" right is "<<r<<endl;

    read_input(log_path,bin_path,input_path);
    interpreter();
    return 0;
}

//0 = 0000
//218 = 0000000000011011010
//7 = 111

//0000 0101 1011 0000 0000 0001 1100 0000
//0A D0 08 30
//A0 0D 80 03