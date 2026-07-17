/** 
*======================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1)
*======================================================================
*FILE: main.cpp
*ROLE: ENTRY POINT, TEST DATA GENERATION AND FLOW CONTROLLER 
*TECHNOLOGY: C++, file output stream, execution trigger
*======================================================================
*/
#include<iostream>
#include<fstream>
#include<string>

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
    // trigger the file loading engine to verify the path before allocation varibles 
    parser.load_file("test_data.csv");
    cout<<endl;
    return 0;
}
