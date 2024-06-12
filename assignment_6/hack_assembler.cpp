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

    map<string,string>dest = dest_table();
    map<string,string>jump = jump_table();
    map<string,string>comp = comp_table();

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
        int line = 0;

        while(getline(input_file,file_line))
        {
            string parsed_line = parser(file_line);
            //Ensure the parsed line is not empty.
            if (parsed_line != "")
            {
                file_lines.push_back(parsed_line);                
                //cout << endl << file_lines[line];
                line += 1;
            }
        }
    }
    else
    {
        cout << "file does not exist!";
        return 0;
    }

    for (size_t i = 0; i < file_lines.size(); i++)
    {
        string binary_code = machine_code_generator(file_lines[i], comp, dest, jump);

        output_file << binary_code << endl;
    }
    return 0;
}
