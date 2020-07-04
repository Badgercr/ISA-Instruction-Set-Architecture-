///Simulator_Turles.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string.h>
#include <map>
#include <vector>

using namespace std;

int bin_to_dec(string bin);

int main()
{
    ifstream fin("programc.o.txt");              /// the file with binary code (0s and 1s)
    ifstream fin2("programc.o.txt");              /// the file with binary code (0s and 1s)

    if(fin.fail())                          /// make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }

    string instructions;                     /// hold the entire binary instruction
    string opcode;                          /// hold the binary opcode (4 bits)
    vector <string>code;
    int ip = -1;
    map<string, vector<int>> reg_map;               /// a map from strings to keys to rep registers
    reg_map["00"];                 ///r1
    reg_map["01"];                  ///r2
    reg_map["10"];                ///r3
    reg_map["11"];                    ///r4



    while(fin>>instructions)
    {
           // fin >> instructions;
            code.push_back(instructions);
    }
    fin.clear();
    int code_s = 100;



    while(--code_s >=0)
    {

        ip++;
     //  cout << ip << "ip" <<endl;
//        cout << code_s << "code" << endl;

        if(code[ip].substr(0,4) == "0000") ///MOVE                  //// if the first 4 bits are PUT
        {
            string n = code[ip].substr(4,6);     /// read the 6 bits related to numerical value
            int val = bin_to_dec(n);                /// convert binary to decimal

            string regis = code[ip].substr(10,2);    /// find the 2 bits related to the register
            reg_map[regis].resize(1);
            reg_map[regis][0] = val;
        }
        else if(code[ip].substr(0,4) == "0001") ///ADD               /// SUM instruction is followed by three registers
        {
            string regisA = code[ip].substr(4,2);    /// bits 5-6 are the first register
            string regisB = code[ip].substr(6,2);    /// bits 7-8 are the second register
            string regisC = code[ip].substr(8,2);   /// bits 9-10 are the last register

            int sum_result = reg_map[regisA][0] + reg_map[regisB][0]; /// add the first two registers
            reg_map[regisC][0]=sum_result;                       /// place the result in the third register
        }
        else if(code[ip].substr(0,4) == "0010") ///SUBTRACT               /// SUM instruction is followed by three registers
        {
            string regisA = code[ip].substr(4,2);    /// bits 5-6 are the first register
            string regisB = code[ip].substr(6,2);    /// bits 7-8 are the second register
            string regisC = code[ip].substr(8,2);   /// bits 9-10 are the last register

            int subt_result = reg_map[regisA][0] - reg_map[regisB][0]; /// add the first two registers
            reg_map[regisC].push_back(subt_result);                       /// place the result in the third register
        }
        else if(code[ip].substr(0,4) == "0100") ///MULTIPLY              /// SUM instruction is followed by three registers
        {
            string regisA = code[ip].substr(4,2);    /// bits 5-6 are the first register
            string regisB = code[ip].substr(6,2);    /// bits 7-8 are the second register
            string regisC = code[ip].substr(8,2);   /// bits 9-10 are the last register

            int mult_result = reg_map[regisA][0] * reg_map[regisB][0]; /// add the first two registers
            reg_map[regisC].push_back(mult_result);                       /// place the result in the third register
        }
        else if(code[ip].substr(0,4) == "1000") ///DIVIDE                /// SUM instruction is followed by three registers
        {
            string regisA = code[ip].substr(4,2);    /// bits 5-6 are the first register
            string regisB = code[ip].substr(6,2);    /// bits 7-8 are the second register
            string regisC = code[ip].substr(8,2);   /// bits 9-10 are the last register

            int div_result = reg_map[regisA][0] / reg_map[regisB][0]; /// add the first two registers
            reg_map[regisC].push_back(div_result);                       /// place the result in the third register
        }
        else if(code[ip].substr(0,4) == "1100") ///SCREEN == OUTPUT                /// print to screen
        {
            string regis = code[ip].substr(4,2);     /// find which register to print
            cout << "Output: " << endl;
            for(int i=0;i<reg_map[regis].size();i++)
            {
                cout << reg_map[regis][i];
            }
        }
        else if(code[ip].substr(0,4) == "0011") ///STOP
        {
            EXIT_SUCCESS;
        }
        else if(code[ip].substr(0,4) == "0110") ///GOTO == JUMP
        {
            string num = code[ip].substr(4,6);
            int line = bin_to_dec(num);
            ip = line;
            ip-=2;

        }
        else if(code[ip].substr(0,4) == "0111") ///makeARRAY
        {
           string num = code[ip].substr(4,6);
            int num2 = bin_to_dec(num);
            string regis = code[ip].substr(10,2);   /// find the 2 bits related to the register
            reg_map[regis].resize(num2);
        }
        else if(code[ip].substr(0,4) == "1010") ///FIND
        {
            string regis = code[ip].substr(10,2);
            string bin = code[ip].substr(4,6);
            int num = bin_to_dec(bin);
            for(int i=0;i<reg_map[regis].size();i++)
            {
                if(reg_map[regis][i]==num)
                {
                    cout << "Value "<< reg_map[regis][i] << " exist at index " << i<<endl;
                    break;
                }

            }
        }
        else if(code[ip].substr(0,4) == "1111") ///IN
        {
            string regis = code[ip].substr(4,2);
            for(int i=0;i<reg_map[regis].size();i++)
            {
                cout << "Input: ";
                cin >> reg_map[regis][i];
            }
        }
        else if(code[ip].substr(0,4) == "1110") ///INCREMENT
        {
            string regis = code[ip].substr(4,2);
            reg_map[regis][0]++;
        }
        else if(code[ip].substr(0,4) == "1011") ///Decrement
        {
            string regis = code[ip].substr(4,2);
            reg_map[regis][0]--;
        }
        else if(code[ip].substr(0,4) == "1001") ///ERASE
        {
            reg_map["00"].clear();
            reg_map["01"].clear();
            reg_map["10"].clear();
            reg_map["11"].clear();

        }
        else if(code[ip].substr(0,4)=="0101") ///skip
        {
            string regis1 = code[ip].substr(4,2);
            string regis2 = code[ip].substr(10,2);
            string cond = code[ip].substr(6,4);

            if(cond=="1111")
            {
                if(reg_map[regis1]>reg_map[regis2])
                {
                    ip++;
                }
            }
            if(cond=="0000")
            {
                if(reg_map[regis1]<reg_map[regis2])
                {
                    ip++;
                }
            }
            if(cond=="1010")
            {
                if(reg_map[regis1]==reg_map[regis2])
                {
                    ip++;
                }
            }



        }
    }

    fin.close();

    return 0;
}

int bin_to_dec(string bin)
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++)
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);

    return num;
}


