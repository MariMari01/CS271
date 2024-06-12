#include "functions.hpp"

//Parses a line, getting rid of spaces and comments indicated through "//"
string parser(string line)
{
    string parsed_line;

    //Remove all spaces from line.
    //Str.erase is needed here to shrink string as it removes spaces.
    line.erase(remove_if(line.begin(), line.end(), isspace),line.end());
    
    //Remove comments from file.
    if (line.find("//") != string::npos)
        parsed_line = line.substr(0, line.find("//"));
    else
        parsed_line = line;
 
    return parsed_line;
}



//Documents the file's symbols and replaces them with their corresponding non symbol value.
map<string,string> symbol_parser(vector<string>lines, map<string,string>symbol_table)
{
    map<string,string>symbols = symbol_table; 

    //First pass
    int lines_excluding_labels = 0;
    for (size_t i = 0; i < lines.size(); i++)
    {
        lines_excluding_labels++;
        if (lines[i][0] == '(')
        {   
            lines_excluding_labels = lines_excluding_labels - 1;
            
            string address = to_string(lines_excluding_labels);
            string address_var = lines[i].substr(1, lines[i].size() - 2);

            symbols.insert({address_var, address});
        }
    }

    int current_register = 16;
    //Second pass
    for (size_t i = 0; i < lines.size(); i++)
    {
        //If we have an A instruction and we have a symbol instead of a number 
        if(lines[i][0] == '@' && !(isdigit(lines[i][1])))
        {
            //Check if we know the value of the value from our symbol table
            string a_inst_symbol = lines[i].substr(1, lines[i].size());

            //If we dont, add it to it.
            if(symbols.find(a_inst_symbol) == symbols.end())
            {
                symbols.insert({a_inst_symbol, to_string(current_register)});
                current_register++;
            }
        }
    }
    return symbols;
}



//Generates the machine code from the parsed input file.
string machine_code_generator(string line, map<string,string>symbols, map<string,string>comp, map<string,string>dest, map<string,string>jump)
{
    string instruction;
    string comp_inst;
    string dest_inst;
    string jump_inst;
    
    string binary_num;

    //A instruction
    if (line[0] == '@')
    {
        string comp_inst = line.substr(1, line.size());
        int num;

        //If Value is a Number
        if (isdigit(comp_inst[0]))
            num = stoi(comp_inst);
        else
        {
            num = stoi(symbols.at(comp_inst));
        }
        binary_num = bitset<15>(num).to_string();

        instruction = '0' + binary_num;
    }
    
    else if (line[0] == '(')
    {
        return "";
    }
    //C instruction 
    else
    {
        instruction = "111";
        auto store = line.find('=');
        auto JMP = line.find(';');
        
        //Destination Instruction and Comp Instruction
        if (store != string::npos)
        {
            comp_inst = comp.at(line.substr(store + 1,line.size()));
            dest_inst = dest.at(line.substr(0,store));
        }
        else
            dest_inst = dest.at("null");
        
        //Jump Instruction and Comp Instrutction
        if (JMP != string::npos)
        {
            comp_inst = comp.at(line.substr(0,JMP));
            jump_inst = jump.at(line.substr(JMP + 1, line.size()));
        }
        else
            jump_inst = jump.at("null");
    
        //Assemble instructions
        instruction = instruction + comp_inst + dest_inst + jump_inst;
    }
    return instruction;
}



//Computation table look up
map<string,string> comp_table()
{
    map<string,string> comp_table;
    //a==0
    comp_table.insert({"0"  ,"0101010"});
    comp_table.insert({"1"  ,"0111111"});
    comp_table.insert({"-1" ,"0111010"});
    comp_table.insert({"D"  ,"0001100"});
    comp_table.insert({"A"  ,"0110000"});
    comp_table.insert({"!D" ,"0001101"});
    comp_table.insert({"!A" ,"0110001"});
    comp_table.insert({"-D" ,"0001111"});
    comp_table.insert({"-A" ,"0110001"});
    comp_table.insert({"D+1","0011111"});
    comp_table.insert({"D-1","0001110"});
    comp_table.insert({"A+1","0110111"});
    comp_table.insert({"A-1","0110010"});
    comp_table.insert({"D+A","0000010"});
    comp_table.insert({"D-A","0010011"});
    comp_table.insert({"A-D","0000111"});
    comp_table.insert({"D&A","0000000"});
    comp_table.insert({"D|A","0010101"});

    //a==1
    comp_table.insert({"M"  ,"1110000"});
    comp_table.insert({"!M" ,"1110001"});
    comp_table.insert({"-M" ,"1110011"});
    comp_table.insert({"M+1","1110111"});
    comp_table.insert({"M-1","1110010"});
    comp_table.insert({"D+M","1000010"});
    comp_table.insert({"D-M","1010011"});
    comp_table.insert({"M-D","1000111"});
    comp_table.insert({"D&M","1000000"});
    comp_table.insert({"D|M","1010101"});

    return comp_table;
}

//Destination table look up 
map<string,string> dest_table()
{
    map<string,string> dest_table;
 
    dest_table.insert({"null","000"});
    dest_table.insert({"M"   ,"001"});
    dest_table.insert({"D"   ,"010"});
    dest_table.insert({"MD"  ,"011"});
    dest_table.insert({"A"   ,"100"});
    dest_table.insert({"AM"  ,"101"});
    dest_table.insert({"AD"  ,"110"});
    dest_table.insert({"AMD" ,"111"});

    return dest_table;
}

//Jump type table look up
map<string,string> jump_table()
{
    map<string,string> jump_table;
 
    jump_table.insert({"null","000"});
    jump_table.insert({"JGT" ,"001"});
    jump_table.insert({"JEQ" ,"010"});
    jump_table.insert({"JGE" ,"011"});
    jump_table.insert({"JLT" ,"100"});
    jump_table.insert({"JNE" ,"101"});
    jump_table.insert({"JLE" ,"110"});
    jump_table.insert({"JMP" ,"111"});

    return jump_table;
}

//Predetermined symbol table
map<string,string>pre_d_symbol_table()
{
    map<string,string>pds_table;

    pds_table.insert({"SP"    ,"0"});
    pds_table.insert({"LCL"   ,"1"});
    pds_table.insert({"ARG"   ,"2"});
    pds_table.insert({"THIS"  ,"3"});
    pds_table.insert({"THAT"  ,"4"});
    pds_table.insert({"R0"    ,"0"});
    pds_table.insert({"R1"    ,"1"});
    pds_table.insert({"R2"    ,"2"});
    pds_table.insert({"R3"    ,"3"});
    pds_table.insert({"R4"    ,"4"});
    pds_table.insert({"R5"    ,"5"});
    pds_table.insert({"R6"    ,"6"});
    pds_table.insert({"R7"    ,"7"});
    pds_table.insert({"R8"    ,"8"});
    pds_table.insert({"R9"    ,"9"});
    pds_table.insert({"R10"   ,"10"});
    pds_table.insert({"R11"   ,"11"});
    pds_table.insert({"R12"   ,"12"});
    pds_table.insert({"R13"   ,"13"});
    pds_table.insert({"R14"   ,"14"});
    pds_table.insert({"R15"   ,"15"});
    pds_table.insert({"SCREEN","16384"});
    pds_table.insert({"KBD"   ,"24576"});

    return pds_table;
}





