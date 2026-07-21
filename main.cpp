/** 
*======================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1, PART 2, PART 3, PART 4, PART 5)
*======================================================================
*FILE: main.cpp
*ROLE: OPERATIONAL CONTROLLER, MOCK GENERATION AND PIPELINE TRIGGER
*TECHNOLOGY: C++, file output stream, execution trigger
*======================================================================
*/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

// important: connection read.cpp to main.cpp so we can use highfrequencyparser
#include "read.cpp"
using namespace std;
// PART 5 UPDATED: GENERATING dummy CSV with valied, corrupt, and incomplete rows
void create_dummy_csv(){
    ofstream out("test_data.csv");
    out<< "ID, NAME, SALARY, DEPARTMENT\n";
    out<< "1, amit, 45000, IT\n";// ROW 1: VALID
    out<< "2, rahul, INVALIED_SALARY, HR\n";//ROW 2: PART 5 CORRUPT (NON- NUMERIC SALARY)
    out<< "3, priya, 55000, FINANCE\n";//ROW 3: VALID
    out<< "4, karan, 70000\n";//ROW 4: PART 5 IMCOMPLETE ( MISSING DEPT)
    out<< "5, sneha, 80000, MARKETING\n";//ROW 5: VALID
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
        // step 2: parse raw textual streams and map objects into structures
        parser.parse_and_tokenize("test_data.csv");
        // step 3: PART 3 NEW: CALL THE PRINT ENGINE TO PRINT INTERNAL STRUCTURAL STORAGE MEMORY MAPS
        parser.display_database();
        // STEP 4:PART 4 NEW: TRIGGER QUERY AND ANALYTICS ENGINE OPERATIONS
        parser.search_by_id(3);// SEARCH FOR RAHUL (ID 2)
        parser.find_highest_salary(); // FIND WHO GETS HIGHEST PAY
        parser.filter_by_department("MARKETING"); // FILTER EMPLOYEE IN HR
            } else{
        cout<<"[CRITICAL FAILURE]: ABORTING PARSING ENGINE" <<endl;
            }
    cout<<endl;
    return 0;
}
