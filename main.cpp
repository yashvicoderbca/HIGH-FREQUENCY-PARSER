/** 
*======================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1)
*======================================================================
*FILE: main.cpp
*ROLE: ENTRY POINT, TEST DATA GENERATION AND FLOW CONTROLLER 
*TECHNOLOGY: C++, file output stream, execution trigger
*======================================================================
*/
#include<iostream>// required for standard input/output stream operations (eg,cout,end)
#include<fstream>// required for helding file input/output stream pipelines(eg, ifstream, ofstream)
#include<string>//required for utilizing the core c++ string data types and manipulation mechanics
#include<sstream>//required for stringstream processing to enable advanced row-splitting and tokenization

// important: connection read.cpp to main.cpp so we can use highfrequencyparser
#include "read.cpp"
using namespace std;

//========================================================================
// HELP LOGIC: DYNAMIC TEST DATA GENERATOR
//========================================================================
void create_dummy_csv(){
    //open an output file stream (ofstream) to create the file on the hard disk
    ofstream out("test_data.csv");
    // writing sample rows into the csv file 
    out<<"ID,NAME,SALERY,DEPARTMENT\n";
    out<<"1,AMIT,45000,IT\n";
    out<<"2,RAHUL,60000,HR\n";
    out<<"3,PRIYA,55000,FINANCE\n";
    // SAFELY CLOSE THE OUTPUT CONNECTION TO RELEASE SYSTEM RESOURCES
    out.close();
}
//=====================================================================
//MAIN FUNCTION 
//=====================================================================
int main(){
    cout<<"PROJECT 2:HIGH-FREQUENCY DATA PARSER START\n"<<endl;
    //firstly ,dynamically generate the test data file on the storage drive
    create_dummy_csv();
    //instantiate the custom parser object in raw (defined in read.cpp)
    highfrequencyparser parser;
    // execute part 1 pipeline to check file path and connecting layouts
    bool is_pipeline_ready = parser.load_file("test_data.csv");
    // conditional routing execution path - trigger part 2 only if connection passes
    if(is_pipeline_ready){
        parser.parse_and_tokenize("test_data.csv");
    } else{
        cout<<"[CRITICAL FAILURE]: Aborting parasing engine due to pipeline setup failure"<<endl;
    }
    cout<<endl;
    return 0;
}
