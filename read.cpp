/** 
*=======================================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1, PART 2, PART 3, PART 4)
*=======================================================================================
*FILE: read.cpp
*ROLE: CORE PARSING LOGIC AND VALIDATION ENGINE
*TECHNOLOGY: C++,FILE I/O, RESOURSE ALLOCATION, GUARD CLAUSE LOGIC
*======================================================================================
*/
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

//=========================================================================================
//PART 3 NEW: CUSTOM DATA STRUCTURE FOR OBJECT MAPPING 
//=========================================================================================
struct Employee{
    int id;
    string name;
    int salary;
    string department;
};
class highfrequencyparser {
    public:
    // PART 3 NEW: FIXED CAPACITY ARRAY DATABASE BUFFER TO STORE MAPPED DATA ROWS
    Employee parsed_database[100];
    int active_record_count = 0; // tracks the number of loaded objects in ram
    //========================================================================================
//PART 1: HIGH-PERFORMANCE FILE LOADING ENGINE
//========================================================================================
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
    * @brief PART 2 AND 3: EXTRACTS ROWS, TOKENIZES STRINGS, AND MAPS INTO THE RAM DATABASE.
    */
    void parse_and_tokenize(const string& filename){
        // step 1: open stream in read mode to parse data rows
        ifstream file(filename);
        if(!file.is_open()){
            cout<<"[ERROR][PART 2]: FAILED TO OPEN THE FILE FOR PARSING!"<<endl;
            return;
        }
        cout<<"\n[STARTING PROCESSING LIFECYCLE: DATA PIPELINE LOGS]"<<endl;
        cout<<"====================================================================";
        string current_row;
        int row_counter = 0;
        //SKIP THE HEADER ROW (ID,NAME,SALARY,DEPARTMENT)TO AVOID PARSING HEADERS INTO INT VARIABLES
         if(getline(file,current_row)){
            cout<<"[HEADER DETECTED AND SKIPPED]:"<<current_row<<endl;
         }
         //sequential row extraction loop
         while(getline(file,current_row)){
            row_counter++;
            stringstream data_stream(current_row);
            string raw_id,raw_name,raw_salary,raw_dept;
            //PART 3 NEW:POSITIONAL DATA EXTRACTION FROM THE STREAM USING COMMA SEPERATION
            if(getline(data_stream,raw_id,',')&& getline(data_stream,raw_name,',')&& getline(data_stream,raw_salary,',')&&getline(data_stream,raw_dept,',')){
                //PART 3 NEW: OBJECT INSTANTIATION AND STRING TO INTEGER DATA CASTING (stio)
                Employee temp_emp;
                temp_emp.id = stoi(raw_id); // coverting string id to integer
                temp_emp.name = raw_name;
                temp_emp.salary = stoi(raw_salary); //coverting string salary to integer
                temp_emp.department = raw_dept;
                // PART 3 NEW: PUCH THE CONSTRUCTED OBJECT DIRECTLY INTO RAM DATABASE ARRAY
                parsed_database[active_record_count] = temp_emp;
                active_record_count++;
                //logging current state telemetry
                cout<<"[PARSED ROW #" <<row_counter<<"]: mapped"<<temp_emp.name<<"securely into ram memory matrix location index["<<active_record_count-1<<"]"<<endl;
            }
         }
         cout<<"==========================================================================="<<endl;
         cout<<"[SUCCESS]: parasing complete. total"<<active_record_count<<"objects generated in ram.\n"<<endl;
         file.close();
    }
        /**
        * @brief PART 3 NEW: DISPLAY THE INTERNAL STRUCTURE RAM MEMORY DATABASE TO VERIFY STORAGE INTEGRITY.
        */
        void display_database(){
            cout<<"[PRINTING RAM DATABASE METRICS- VERIFYING STORAGE STRUCTURES]"<<endl;
            cout<<"=============================================================="<<endl;
            cout<<"INDEX\tID\tNAME\t\tSALARY\t\tDEPARTMENT"<<endl;
            cout<<"============================================================"<<endl;
            for(int i=0;i<active_record_count;i++){
                cout<<i<<"\t"
                    <<parsed_database[i].id<<"\t"
                    <<parsed_database[i].name<<"\t\t"
                    <<parsed_database[i].salary<<"\t\t"
                    <<parsed_database[i].department<<endl;
            }
            cout<<"====================================================="<<endl;
        }
        //===========================================================================
        // PART 4 NEW: QUERY AND ANALYTICS ENGINE
        //============================================================================
        /**
        * @brief part 4 new:searches for the employee record using their unique id.
        * @param target_id ID to search for in RAM database
        */
        void search_by_id(int target_id) {
            cout<<"\n[QUERY ENGINE:SEARCH BY ID ="<<target_id<<"]"<<endl;
            // flag to track wherther the target  ID was found during iteration
            bool found= false;
            // iteration through all active records in the database
            for( int i= 0; i<active_record_count; i++){
                //  check if the current record's id matches the target 
                if( parsed_database[i].id==target_id){
                    cout<<"[MATCH FOUND]: ID:"<<parsed_database[i].id
                        <<"|NAME: "<<parsed_database[i].name
                         <<"|SALARY: "<<parsed_database[i].salary
                         <<"|DEPT: "<<parsed_database[i].department<<endl;
                       found=true;
                        break;//stop the loop execution immediately once a match is confirmed
                }
            }
            if(!found) {
                cout<<"[NO MATCH]: RECORD WITH ID"<<target_id<<"was not found"<<endl;
            }
        }
          /** 
          * @brief PART 4 NEW: FINDS AND DISPLAY THE EMPLOYEE WITH HIGHEST SALARY.
          */
          void find_highest_salary(){
              cout<<"\n [ANALYTICS ENGINE: FIND HIGHEST SALARY]"<<endl;
              // guard clause: enshure the database is not empty to prevent errors
              if( active_record_count==0){
                  cout<<"[ERROR]: DATABASE IS EMPTY"<<endl; 
                  return;
              }
              // initialize the first record as a baseline maximum
              int max_index=0;
              // iterate starting from second record (index 1) to compare salaries
              for( int i= 1; i<active_record_count; i++){
                  //otherwise max_index if the larger salary value is encountered
                  if(parsed_database[i].salary> parased_database[max_index].salary){
                      max_index = i;
                  }
              }
                  // print the highest salary record details mapped to the maximum index
                  cout<<"HIGHEST SALARY RECORD:"<<parsed_database[max_index].name
                   cout<<"WITH:"<< parsed_database[max_index].salary
                   cout<<"DEPT:"<< parsed_database[max_index].department<<")"<<endl;
              }
           /**
           *  @brief PART 4 NEW: filters and lists all the employee belonging to a specific department 
           * @param target_dept the exact department string name to filter the database by.
           */
            void filter_by_department(const string& target_dept){
                cout<<"\n [FILTER ENGINE: EMPLOYEES IN DEPARTMENT='"<<target_dept<<"']"<<endl;
                // counter variable to tally the number of matching records found 
                int match_count = 0;
                // iterate through the entire dataset to find the all the string matches
                for( int i=0; i<active_record_count; i++){
                    // checks the current record's department alligns with the target query
                    if( parsed_database[i].departemnt == target_dept){
                        match_count++;
                        // display the specific details of the matched record
                        cout<<"["<<match_count<<"] ID:"<<parsed_database[i].id
                              <<"| NAME:"<< parsed_database[i].name
                             <<"| SALARY: << parsed_database[i].salary<<endl;
                    }
                }
                // output final evalution logic based on the match counter state 
                if(match_count==0){
                    cout<<"[NO MATCH]: NO EMPLOYEES FOUND IN "<<target_dept<<"'department"<<endl;
                } else{
                    cout<<"-> total" <<match_count<<"employee(s) found in"<<target_dept<<"."<<endl;
                }
                    
            }
    };
        
