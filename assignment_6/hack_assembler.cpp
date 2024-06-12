/*
File: hack_assembler.cpp
Author: Samuel Garcia Lopez

Description:
This file assembles Hack assembly code into binary instructions
for the computer. 
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include "functions.hpp"


using std::cout;
using std::endl;

using std::ifstream;
using std::ofstream;

using std::vector;

using std::bitset;

int main(int argc, char* argv[])
{

    map<string,string> dest = dest_table();
    map<string,string> jump = jump_table();
    map<string,string> comp = comp_table();
    map<string,string> symb = pre_d_symbol_table();
    map<string,string> updated_symb;

    vector<string> file_lines;

    //File to be read and translated into binary instructions.
    char* input_filename = argv[1];
    ifstream input_file;
    input_file.open(input_filename);
    
    //File to write binary instructions to.
    ofstream output_file;
    output_file.open("output.hack");
    string file_line;

    if (input_file.is_open())
    {
        while(getline(input_file,file_line))
        {
            string parsed_line = parser(file_line);
            //Ensure the parsed line is not empty.
            if (parsed_line != "")
            {
                file_lines.push_back(parsed_line);                
            }
        }
    }
    else
    {
        cout << "file does not exist!";
        return 0;
    }

    updated_symb = symbol_parser(file_lines, symb);

    for (size_t i = 0; i < file_lines.size(); i++)
    {
        string binary_code = machine_code_generator(file_lines[i], updated_symb, comp, dest, jump);

        if (binary_code != "")
            output_file << binary_code << endl;
    }
    input_file.close();
    output_file.close();
    return 0;
}
