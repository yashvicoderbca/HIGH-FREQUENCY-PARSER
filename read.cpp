/** 
*=======================================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1)
*=======================================================================================
*FILE: read.cpp
*ROLE: CORE PARSING LOGIC AND VALIDATION ENGINE
*TECHNOLOGY: C++,FILE I/O, RESOURSE ALLOCATION, GUARD CLAUSE LOGIC
*======================================================================================
*/
#include <iostream>//required for standard input/output stream operations(eg cout,end)
#include<fstream> //required for handling file input/output stream pipelines (eg, ifstream, ofstream)
#include<string>// required for utilization the core c++ string data types and manipulation mechanics
#include<sstream>//required for stringstream processing to enable advanced row-splitting and tokenization
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
    /** 
    * @brief PART 2 NEW: reads the file line by line and tokenizes each row using commas.
    * @param filename path of the target CSV file
    */
    void parse_and_tokenize(const string& filename){
        // step 1: open stream in read mode to parse data rows
        ifstream file(filename);
        if(!file.is_open()){
            cout<<"[ERROR][PART 2]: FAILED TO OPEN THE FILE FOR TOKENIZATION ENGINE!"<<endl;
            return;
        }
        cout<<"\n[ STARTING PART 2: ROW EXTRACTION AND TOKENIZATION PIPELINE]"<<endl;
        cout<<"====================================================================";
        string current_row;
        int row_counter = 0;
        //step 2: continuous execution loop to extract rows sequuentially till EOF(END OF FILE)
        while(getline(file,current_row)){
            row_counter++;
            cout<<"\n[ROW #]"<<row_counter<<"RAW TEXT]:"<<current_row<<endl;
            //step 3: wrap the raw string inside a stream object to slice segments logically
            stringstream data_stream(current_row);
            string individual_token;
            cout<<"-> tokens extracted:";
            //step 4: internal splitting loop parsing individual data element separated by comma
            while(getline(data_stream,individual_token,',')){
                cout<<"["<<individual_token<<"]";
            }
            cout<<endl;
        }
       cout<<"-------------------------------------------------------------------"<<endl;
       cout<<"[SUCCESS][PART 2]:total"<<row_counter<<"rows processed and parsed securely.\n"<<endl;
       // step 5: safely release system hardware descriptors
       file.close();
    }
};
