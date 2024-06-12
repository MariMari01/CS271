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

string parser(string line);
map<string,string> symbol_parser(vector<string>lines, map<string,string>symbol_table);
string machine_code_generator(string line,map<string,string>symbols, map<string,string>comp, map<string,string>dest, map<string,string>jump);

map<string,string> pre_d_symbol_table();
map<string,string> comp_table();
map<string,string> dest_table();
map<string,string> jump_table();