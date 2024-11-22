#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <string>
#include <cmath>
using namespace std;
string input_path, output_path, log_path;
string transformate(vector<int> length, int sum, vector<string> arguments){
    string out="";
    string str="";
    string tek;
    for (int i =0;i<3;i++){
        tek = arguments[i];
        bitset<32> x = stoi(tek);
        tek = "";
        for (int j = 0;j<length[i];j++)
            tek+=to_string(x[j]);
        //cout<<tek<<endl;
        str+=tek;
    }
    int sz = str.size();
    for (int i = 0;i<sum-sz;i++)
        str+='0';
    
    for (int i =0;i<4;i++){
        tek="";
        int x = 0;
        for (int j=(i+1)*8-1;j>=i*8+4;j--)
            x+=int(str[j]-'0')*pow(2,j-i*8-4);
        
        if (x<10)    
            out+=to_string(x);
        else out+=char(x-10+'A');
        x=0;
        for (int j=i*8+3;j>=i*8;j--)
            x+=int(str[j]-'0')*pow(2,j-i*8);
        
        if (x<10)
            out+=to_string(x);
        else out+=char(x-10+'A');
        out+=" ";
    }

    return out;
}

string log_in(vector<string> arguments,string out,string command){
    string log = "";
    log += "  <instruction>\n";
    log += "    <mnemonic>"+command+"</mnemonic>\n";
    log += "    <opcode>" +arguments[0]+"</opcode>\n";
    log += "    <operand>"+arguments[1]+"</operand>\n";
    log += "    <result_register>"+arguments[2]+"</result_register>\n";
    log += "    <binary>"+out+"</binary>\n";
    log += "  </instruction>\n";
    return log;
}

void read_input(string path){
    vector<int> length;
    ofstream log(log_path+"log.xml");
    log << "<log>\n";
    
    ifstream fin(path+"input.txt");
    string s = "";
    while (getline(fin,s)){
        s+=' ';
        string command = s.substr(0,s.find(' '));
        
        s = s.substr(s.find(' ')+1,s.size()-s.find(' ')-1);
        vector<string> arguments;
        while (s.size()>0){
            arguments.push_back(s.substr(0,s.find(' ')));
            s = s.substr(s.find(' ')+1,s.size()-s.find(' ')-1);
        }

        if (command=="LOAD_CONST"){
            length.push_back(4);
            length.push_back(19);
            length.push_back(3);
            
        }
        else if (command=="READ_VALUE"){
            length.push_back(4);
            length.push_back(3);
            length.push_back(15);
            
        }
        else if (command=="WRITE_VALUE"){
            length.push_back(4);
            length.push_back(15);
            length.push_back(3);
             
        }
        if (command=="BITREVERSE"){
            length.push_back(4);
            length.push_back(3);
            length.push_back(3);
        }
        
        string out = transformate(length,32,arguments);
        out = log_in(arguments,out,command);
        log<<out;
        length.clear();
    }
    log << "</log>\n";
    fin.close();
    log.close();
}

int main(int argc, char* argv[]){
    
    input_path = argv[1];
    output_path = argv[2];
    log_path = argv[2];
    
    cout<<"Path to input file is "<<input_path<<endl;
    cout<<"Path to output file is "<<output_path<<endl;
    cout<<"Path to log file is "<<log_path<<endl;

    read_input(input_path);
    return 0;
}

//0 = 0000
//218 = 0000000000011011010
//7 = 111

//0000 0101 1011 0000 0000 0001 1100 0000
//0A D0 08 30
//A0 0D 80 03    