#include "assembler.cpp"
using namespace std;

map<int,int> memory,registers;
int l,r;

int bin_to_dec(string s){
    int out = 0;
    for (int i=0;i<s.size();i++)
        if (s[i]=='1')
            out+=pow(2,s.size()-i-1);
    return out;
}

int bitreverse(int number,int length){
    bitset<32> bits = number;
    string s = "";
    for (int i=0;i<length;i++)
        s+=to_string(bits[i]);
    //cout<<s<<endl;
    return bin_to_dec(s);
}


void out_result(){
    ofstream fout("result.xml");
    fout << "<result>\n";
    int pred=-1;

    for (auto c:registers){
        if (c.first>=l){
            if (c.first>r)
                break;
            if (pred==-1)
                for (int i = l;i<c.first;i++)
                    fout<<"<register address="<<i<<">"<<-1<<"</register>\n";
            else {                
                for (int i =pred+1;i<min(c.first,r);i++)
                    fout<<"<register address="<<i<<">"<<-1<<"</register>\n";
             }
            
            fout<<"<register address="<<c.first<<">"<<c.second<<"</register>\n";
            
            pred = c.first;
        }
    }
    
    for (int i = max(pred+1,l);i<=r;i++)
            fout<<"<register address="<<i<<">"<<-1<<"</register>\n";

    fout << "<result>\n";
    fout.close();
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
        int command,b,c;
        command = bin_to_dec(string_reverse(bit_str.substr(0,4)));
        switch(command){
            case 0: b = bin_to_dec(string_reverse(bit_str.substr(4,19)));
                    c = bin_to_dec(string_reverse(bit_str.substr(23,3)));
                    registers[c]=b;
                    break;
            case 15: b = bin_to_dec(string_reverse(bit_str.substr(4,3)));
                    c = bin_to_dec(string_reverse(bit_str.substr(7,15)));
                    if (memory[c]==-1)
                        error_detected("memory is empty!\n");
                    registers[b]=memory[c];
                    break;
            case 7: b = bin_to_dec(string_reverse(bit_str.substr(4,15)));
                    c = bin_to_dec(string_reverse(bit_str.substr(19,3)));
                    //cout<<b<<" "<<c<<endl;
                    if (registers[c]==-1)
                        error_detected("register is empty!!\n");
                    memory[b]=registers[c];
                    break;
            case 12: 
                    b = bin_to_dec(string_reverse(bit_str.substr(4,3)));
                    c = bin_to_dec(string_reverse(bit_str.substr(7,3)));
                    //scout<<registers[c]<<" "<<memory[registers[c]]<<endl;
                    if (registers[c]==-1)
                        error_detected("register is empty!\n");
                    else if (memory[registers[c]]==-1)
                        error_detected("memory is empty!\n");
                    else registers[b]=bitreverse(memory[registers[c]],3);
                    break;
            default: 
                    error_detected("The unknown index of command!\n");
                    break; 
        }        
    }
    binFile.close();
    out_result();
}