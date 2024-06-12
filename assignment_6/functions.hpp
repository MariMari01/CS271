#pragma once
#include <string>
#include <algorithm>
#include <map>
#include <bitset>

using std::stoi;
using std::string;
using std::remove;
using std::map;
using std::bitset;

string parser(string line);
string machine_code_generator(string line, map<string,string>comp, map<string,string>dest, map<string,string>jump);

map<string,string> comp_table();
map<string,string> dest_table();
map<string,string> jump_table();