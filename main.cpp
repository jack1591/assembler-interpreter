#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <string>
#include <cmath>
#include <map>
using namespace std;
string input_path, bin_path, log_path;
map<int,int> memory,registers;

int bin_to_dec(string s){
    int out = 0;
    for (int i=0;i<s.size();i++)
        if (s[i]=='1')
            out+=pow(2,s.size()-i-1);
    return out;
}

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
            out+="0x"+to_string(x);
        else {
            out+="0x";
            out+=char(x-10+'A');
        }
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

int bitreverse(int number,int length){
    bitset<32> bits = number;
    string s = "";
    for (int i=0;i<length;i++)
        s+=to_string(bits[i]);
    return bin_to_dec(s);
}

void read_input(string path){
    vector<int> length;
    ofstream log(log_path+"log.xml");
    ofstream binFile(bin_path+"output.bin");
    
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
        binFile<<out+"\n";
        out = log_in(arguments,out,command);
        log<<out;
        
        length.clear();
    }
    log << "</log>\n";
    fin.close();
    log.close();
    binFile.close();
}

string string_reverse(string s){
    int size = s.size();
    string out = "";
    for (int i = s.size()-1;i>=0;i--)
        out+=s[i];
    return out;
}

void interpreter(){
    fstream binFile("output.bin");
    string s;
    while (getline(binFile,s)){
        s+=" ";
        vector<string> parts;
        
        while (s.size()>1){
            parts.push_back(s.substr(2,s.find(' ')-2));
            s = s.substr(s.find(' ')+1,s.size()-s.find(' ')-1);
        }
        
        for (int i=0;i<4;i++)
            swap(parts[i][0],parts[i][1]);
        
        string bit_str="";
        for (auto c:parts){
            for (int i =0;i<2;i++){
                int x;
                if (c[i]>='A' && c[i]<='F')
                    x=10+c[i]-'A';
                else x = c[i]-'0';
                bitset<4> bits = x;
                for (int j = 0;j<4;j++)
                    bit_str+=to_string(bits[j]);
            }
        }
        cout<<bit_str<<endl;
        int command,b,c;
        command = bin_to_dec(string_reverse(bit_str.substr(0,4)));
        switch(command){
            case 0: b = bin_to_dec(string_reverse(bit_str.substr(4,19)));
                    c = bin_to_dec(string_reverse(bit_str.substr(23,3)));
                    registers[c]=b;
                    break;
            case 15: b = bin_to_dec(string_reverse(bit_str.substr(4,3)));
                    c = bin_to_dec(string_reverse(bit_str.substr(7,15)));
                    registers[b]=memory[c];
                    break;
            case 7: b = bin_to_dec(string_reverse(bit_str.substr(4,15)));
                    c = bin_to_dec(string_reverse(bit_str.substr(19,3)));
                    memory[b]=registers[c];
                    break;
            case 12: 
                    b = bin_to_dec(string_reverse(bit_str.substr(4,3)));
                    c = bin_to_dec(string_reverse(bit_str.substr(7,3)));
                    if (registers[c]==0)
                        cout<<"register is empty!\n";
                    else if (memory[registers[c]]==0)
                        cout<<"memory is empty!\n";
                    else {
                        registers[b]=bitreverse(memory[registers[c]],3);
                        cout<<registers[b]<<endl;
                    }
                    break;
            default: cout<<"Error!";
                     break; 
        }        
        cout<<command<<" "<<b<<" "<<c<<endl;
    }
    binFile.close();
}

int main(int argc, char* argv[]){
    
    input_path = argv[1];
    bin_path = argv[2];
    log_path = argv[2];
    
    cout<<"Path to input file is "<<input_path<<endl;
    cout<<"Path to binary output file is "<<bin_path<<endl;
    cout<<"Path to log file is "<<log_path<<endl;

    read_input(input_path);
    interpreter();
    return 0;
}

//0 = 0000
//218 = 0000000000011011010
//7 = 111

//0000 0101 1011 0000 0000 0001 1100 0000
//0A D0 08 30
//A0 0D 80 03