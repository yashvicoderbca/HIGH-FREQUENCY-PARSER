/** 
*======================================================================
* HIGH-FREQUENCY DATA PARSER (PROJECT 2 PART 1, PART 2, PART 3, PART 4, PART 5, PART 6, PART 7)
*======================================================================
*FILE: main.cpp
*ROLE: CONTROLLER, MOCK DATASET GENERATION & AUTO DISK SYNC SHUTDOWN 
*TECHNOLOGY: C++, DYNAMIC CONTROL LOOPS, AUTOMATIC PERSISTENCE ROUTINES
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
    out<< "1,amit,45000,IT\n";// ROW 1: VALID
    out<< "2,rahul,INVALIED_SALARY,HR\n";//ROW 2: PART 5 CORRUPT (NON- NUMERIC SALARY)
    out<< "3,priya,55000,FINANCE\n";//ROW 3: VALID
    out<< "4,karan,70000\n";//ROW 4: PART 5 IMCOMPLETE ( MISSING DEPT)
    out<< "5,sneha,80000,MARKETING\n";//ROW 5: VALID
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
    if(!is_pipeline_ready){
        cout<<"[CRITICAL FAILURE]: aborting parsing engine due to pipeline setup failure"<<endl;
        return 0;
    }
    //step 2: parse textual streams into  RAM Structures with exception protection
    parser.parse_and_tokenize("test_data.csv");
    //===================================================================================
    // PART 6 AND PART 7: INTERATIVE DASHBOARD WITH DISK SYNC PERSISTENCE
    //====================================================================================
    int user_choice = 0;
    // event loop: keeps process presistent in ram until explicit exit command
    while(user_choice!=6){
        cout<<"\n=================================================================="<<endl;
        cout<<"          PARSER ENGINE DASHBOARD                                   "<<endl;
        cout<<"\n=================================================================="<<endl;
        cout<<"1. display complete ram matrics"<<endl;
        cout<<"2. serach record by employee ID"<<endl;
        cout<<"3. Analytics: find the highest salary record"<<endl;
        cout<<"4. filter records by department "<<endl;
        cout<<"5. system diagnostic: show parsing metrics"<<endl;
        cout<<"6. Exit application"<<endl;
        cout<<"----------------------------------------------------------------------"<<endl;
        cout<<"enter the choice [1-6]:";
        //safe input guard against invalid character enteries
        if(!(cin>>user_choice)){
            cout<<"\n [INPUT ERROR]: INVALID CHOICE! PLEASE ENTER A VALID NUMBER BETWEEEN 1 TO 6"<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            continue;
        }
        //router processing requested user command via jump table
        switch(user_choice){
            case 1:
            parser.display_database();
            break;

            case 2:{
                int serach_id;
                cout<<" enter employee ID  to serach: ";
                if(cin>> serach_id){
                    parser.search_by_id(serach_id);
                } else{
                    cout<<"[INPUT ERROR]: ID must be an integer value "<<endl;
                    cin.clear();
                    cin.ignore(10000,'\n');
                }
                break;
            }
            case 3:
            parser.find_highest_salary();
            break;

            case 4:{
                string dept_name;
                cout<<"\n enter department Name (eg IT, FINANCE)";
                cin>>dept_name;
                parser.filter_by_department(dept_name);
                break;
            }
              case 5:
              parser.show_system_diagnostics();
              break;

              case 6:
              cout<<"\n shutting down High-Frequency data parser engine . good luck with your project"<<endl;
              break;

              default:
              cout<<"\n [INVALID CHOICE]: OPTION"<<user_choice<< "is not recognized. pick between 1 and 6"<<endl;
              break;
        }
    }
    return 0;
}
