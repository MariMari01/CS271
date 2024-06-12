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






//Generates the machine code from the parsed input file.
string machine_code_generator(string line, map<string,string>comp, map<string,string>dest, map<string,string>jump)
{
    string instruction;
    string comp_inst;
    string dest_inst;
    string jump_inst;
    
    //A instruction
    if (line[0] == '@')
    {
        string comp_inst = line.substr(1, line.size());
        string binary_num;

        //If Value is a Number
        int num = stoi(comp_inst);

        binary_num = bitset<15>(num).to_string();

        binary_num = '0' + binary_num;

        instruction = binary_num;
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