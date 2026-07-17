/** 
*=======================================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1)
*=======================================================================================
*FILE: read.cpp
*ROLE: CORE PARSING LOGIC AND VALIDATION ENGINE
*TECHNOLOGY: C++,FILE I/O, RESOURSE ALLOCATION, GUARD CLAUSE LOGIC
*======================================================================================
*/
#include <iostream>
#include<fstream>
#include<string>

using namespace std;
//========================================================================================
//PART 1: HIGH-PERFORMANCE FILE LOADING ENGINE
//========================================================================================
class highfrequencyparser{
    public:
    /** 
    *@brief verifies if the target file exists and establishes a secure stream connection.
    *@param filename path of the target CSV file.
    @return true if the pipeline is successfully established false otherwise.
    */
    bool load_file(const string& filename){
        //step 1: open an input file stream (ifstream) in readmode
        ifstream file(filename);
        //step 2: Guard clause check - verify if the hardware file descriptor opened successfully 
        if(!file.is_open()){
            cout<<"[ERROR][PART1]: OOPS! file"<<filename
            <<"was not found or corrupt!"<<endl;
            return false;//safely exist early to prevent program crash
        }
        //step 3: telemetry log on successful connection
        cout<<"[SUCCESS][PART 1]:pipeline prefectly connected"<<filename<<"successfully loaded"<<endl;
        // step 4:safely close the pipeline connection to prevent memory leaks
        file.close();
        return true;
    }
};
