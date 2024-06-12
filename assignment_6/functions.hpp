#pragma once
#include <string>
#include <algorithm>
#include <map>
#include <bitset>
#include <vector>

using std::stoi;
using std::string;
using std::remove;
using std::to_string;

using std::map;
using std::bitset;
using std::vector;

//Parses string to get rid of white spaces and comments
string parser(string line);
//Detects symbols and places them and their address into the symbol table
map<string,string> symbol_parser(vector<string>lines, map<string,string>symbol_table);
//Generates the binary machine code
string machine_code_generator(string line,map<string,string>symbols, map<string,string>comp, map<string,string>dest, map<string,string>jump);

//Predetermined symbol table
map<string,string> pre_d_symbol_table();
//Computation table definition
map<string,string> comp_table();
//Destination table definition
map<string,string> dest_table();
//Jump type table definition
map<string,string> jump_table();
