
//  Edward J Skrod
//  proj5, COP4530

#include <iostream>
#include <fstream>          // Filestream object
#include "cputime.h"        // For computing the time of functions
#include <unistd.h>         // For cputime
#include <iomanip>          // For output formatting
#include <vector>           // Used to store a temporary list of relevant plays
#include <string>
#include <cstdlib>          // for Exit
#include <sstream>          // To parse the input
#include "List.h"
#include "Play.h"           // lineData class and member functions
#include "HashTable.h"
//#include <unordered_set>
#include <tr1/unordered_set>

using namespace tr1;
using namespace std;

struct PlayHasher
// This struct is used to overload the () operator for the hash function
// used by the unordered_set
{
    unsigned int operator()( const Play &playObj ) const {
       
        unsigned int hash = 0;
    
        //cout << "Calling PlayHasher on: " << playObj << "\n"; // UnHide for testing
        string Key = playObj.getOffenseName() + playObj.getDefenseName();
        //cout << "Key is: " << Key << "\n"; // UnHide for testing
        
        for (unsigned int lcv = 0; lcv != Key.size(); ++lcv){
            hash = 37 * hash + (Key[lcv] - 'a' + 1 );
        }
        
        hash = hash  + playObj.getDown() + playObj.getYardsToGo();
        Key = playObj.getDescription();
        
        // Add the Description here
        for (unsigned int lcv = 0; lcv != Key.size(); ++lcv){
            
            hash += Key[lcv];
        }
        //cout << "Hash is: " << hash << "\n"; // UnHide for testing to see hash value
 
        return hash;
    }
};

// FUNCTIONS
void readData(const string fileName, string &FileContent);
void storeData(const string fn,  unordered_set<Play, PlayHasher> &dataRecord,
               const string &FileContent);
void storeData(const string fn,  HashTable &dataRecord,
               const string &FileContent);
void list(vector<string> &input, unordered_set<Play, PlayHasher> &dataRecord, vector<Play> &tempList);
void list(vector<string> &input, HashTable &dataRecord, vector<Play> &tempList);
void sortByRelevance(vector<Play> &dataRecord);

// GLOBAL CONSTANTS
const string LIST = "list";
const bool TEST = false;

int main(int argc, const char * argv[])
{
    double t1, t2;
    float timeToStore_myhash = 0.0;
    float timeToList_myhash = 0.0;
    float timeToList_myhash_MIN = 1000;  // Give this a large, impossible number to start.
    float timeToList_myhash_MAX = 0.0;
    float timeToList_myhash_TOTAL = 0.0;
    float timeToList_myhash_MEAN = 0.0;
    int listCount = 0;                  // Tracks the number of times that list is called.
    
    
    float timeToStore_myDS = 0.0;
    float timeToList_myDS = 0.0;
    float timeToList_myDS_MIN = 1000;
    float timeToList_myDS_MAX = 0.0;
    float timeToList_myDS_TOTAL = 0.0;
    float timeToList_myDS_MEAN = 0.0;
    

    if (argc < 2) {
        cerr << argv[0] << " Year-List\n";
        exit(1);
    }
  
    string fileName;                    // Stores the filename once parsed
    //fileName = "2002.csv";
    unordered_set<Play, PlayHasher> dataRecord;
    HashTable ht_dataRecord;
    string FileContent;
    
    // Read in the data
   for (int lcv = 1; lcv < argc; lcv++) {   // Set to the 2rd arg
    
   
        // Set the filename
       fileName = argv[lcv];
        
        // Add the relative path and the file extension
       fileName = fileName + ".csv";
        
        // Read data into a temporary file
        readData(fileName, FileContent);
    
       //MYDATASTRUCTURE store Data
       t1 = cputime();
       storeData(fileName, ht_dataRecord, FileContent);
       t2 = cputime();
       timeToStore_myDS += (t2 - t1);

       // MYHASH store Data
       t1 = cputime();
        storeData(fileName, dataRecord, FileContent);
       t2 = cputime();
        timeToStore_myhash += (t2 - t1);
   }
    
    //cout << "myhash size: " << dataRecord.size() << "\n";
    //cout << "mydatarecord size: " << ht_dataRecord.totalNumRecords() << "\n";
    
   
    string tempString;      // Temporary string to save the user's input
    vector <string> input;  // Container to store the user's input
    string subString;
    
    do {
        
        vector<Play> tempList_myhash, tempList_myDS;

        input.clear();      // clear previous iteration (if any)
        
        // Read the input from CIN
        getline(cin, tempString, '\n');
        
        istringstream * issPtr = new istringstream(tempString);
        *issPtr >> subString;
        while (*issPtr) {
            input.push_back(subString);
            *issPtr >> subString;
        }
        delete issPtr;
        
        // Respond to the user's command
        if (input[0] == LIST) {
            
            
            //cout << "Calling list() on myhash: \n";
            // MYHASH list
            t1 = cputime();
            list(input, dataRecord, tempList_myhash);
            t2 = cputime();
            timeToList_myhash = (t2 - t1);
            timeToList_myhash_TOTAL = timeToList_myhash_TOTAL + timeToList_myhash;
            
            //cout << "\nCalling list() on mydatastructure: \n";
            // MYDATASTRUCTURE list
            t1 = cputime();
            list(input, ht_dataRecord, tempList_myDS);
            t2 = cputime();
            timeToList_myDS = (t2 - t1);
            timeToList_myDS_TOTAL = timeToList_myDS_TOTAL + timeToList_myDS;
 
            // Track how many times the list function has been called
            ++listCount;
    
            // Print the plays
            vector<Play>::iterator itr_myhash, itr_myDS;
            int numPlaysToPrint = atoi(input[1].c_str());
            
             itr_myhash = tempList_myhash.begin();
             itr_myDS = tempList_myDS.begin();
             int counter = 0;
             while ((counter < numPlaysToPrint) && (itr_myhash != tempList_myhash.end())){
             
                cout << *itr_myhash;
                cout << *itr_myDS;
                cout << "\n";
             ++itr_myhash;
             ++itr_myDS;
             ++counter;
             
             }
            
       } else if (input[0] == "x") {
            //  exit out of loop
       } else {
            cout << "Invalid command.\n";
        }
        
        // Set minimum, max values for time
        if (timeToList_myhash > timeToList_myhash_MAX)
        { timeToList_myhash_MAX = timeToList_myhash; }
        
        if ((timeToList_myhash < timeToList_myhash_MIN) && timeToList_myhash != 0)
        {  timeToList_myhash_MIN = timeToList_myhash; }
        
        if (timeToList_myDS > timeToList_myDS_MAX)
        { timeToList_myDS_MAX = timeToList_myDS; }
        
        if ((timeToList_myDS < timeToList_myDS_MIN ) && timeToList_myDS != 0)
        { timeToList_myDS_MIN = timeToList_myDS; }
        
       // Clear the temporary lists before the list function is called again
       tempList_myhash.clear();
       tempList_myDS.clear();
     
    } while ((input[0] != "x")); // end while
  
    
    // CALCULATE THE MEAN TIME TO LIST
    if (listCount > 0) {
        
        timeToList_myhash_MEAN = timeToList_myhash_TOTAL / listCount;
        timeToList_myDS_MEAN = timeToList_myDS_TOTAL / listCount;
        
    } else {    // Set timeToList_MIN == 0 if list() is never called

        timeToList_myhash_MIN = 0.0;
        timeToList_myDS_MIN = 0.0;
    }
    
    
    //cout << "Listcount is: " << listCount << "\n";
    cout << fixed << setprecision(5);
    // print statistics on the performance of each data structure
   cout << "myhash: store " << timeToStore_myhash << " s, list: min " << timeToList_myhash_MIN
        << " s, max " << timeToList_myhash_MAX << " s, mean " << timeToList_myhash_MEAN << " s\n";
    
    
    cout << "mydatastructure: store " << timeToStore_myDS << " s, list: min " << timeToList_myDS_MIN
    << " s, max " << timeToList_myDS_MAX << " s, mean " << timeToList_myDS_MEAN << " s\n";
    
    return 0;
}

// ============================ FUNCTIONS ==================================
void readData(const string filename, string &FileContent )
// Opens a file and stores the information into one large string
// Function adapted from Prof. Srinivasan's Proj1 Solution
{
    // Clear file content from previous iteration
    FileContent.clear();
    
    ifstream inFile;
    inFile.open( filename.data(), ios::in|ios::binary|ios::ate);  // Get pointer at end of file
    
    ifstream::pos_type size;
   
    if (!inFile) {
        cout << "Error opening file: " << filename << ". Exiting program.\n" << endl;
        exit(1);
    }
    
    size = inFile.tellg();
    char * buffer = new char[static_cast<int>(size)];
    
    inFile.seekg(0, ios::beg);   // set pointer to beginning of file
    inFile.read(buffer, size);   // read the file contents
    
    FileContent.clear();
    FileContent.append(buffer, buffer + size);  // Read the file contents
    
    delete [] buffer;
    inFile.clear();
    inFile.close();
  
}


void storeData(const string filename, unordered_set<Play, PlayHasher> &dataRecord, const string &FileContent)
// Used by main()

{
    stringstream in(FileContent);
    string temp;
    
    getline(in, temp, (char) 10);             // Read in the first line and discard
    
    // Create temporay variables to store the data from the file.
    string tmpGameID, tmpQuarter, tmpMin, tmpSec, tmpOffenseName,
    tmpDefenseName, tmpDown, tmpYardsToGo, tmpStartLocation,
    tmpDescription, tmpOffscore, tmpDefscore, tmpSeason;
    
    int playCounter = 0;     // This is going to generate a unique number representing
                             // the order in which the plays were stored.
    
    // Read in the variables;  Priming read
    getline(in, tmpGameID, ',');
    
    while (!in.eof()){
        
        getline(in, tmpQuarter, ',');
        getline(in, tmpMin, ',');
        getline(in, tmpSec, ',');
        getline(in, tmpOffenseName, ',');
        getline(in, tmpDefenseName, ',');
        getline(in, tmpDown, ',');
        getline(in, tmpYardsToGo, ',');
        getline(in, tmpStartLocation, ',');
        getline(in, tmpDescription, ',');
        getline(in, tmpOffscore, ',');
        getline(in, tmpDefscore, ',');
        getline(in, tmpSeason);
        
        if ((tmpYardsToGo != "") && (tmpStartLocation != "") && (tmpDown != "") && (tmpOffenseName != ""))
        {
            Play tempPlay(tmpGameID, tmpQuarter, tmpMin, tmpSec,
                          tmpOffenseName, tmpDefenseName, tmpDown, tmpYardsToGo,
                          tmpStartLocation, tmpDescription, tmpOffscore, tmpDefscore,
                          tmpSeason, playCounter);
            //  If tmpDescription contains the necessary words, create a new
            // Play object and add it to dataRecord
            if (tempPlay.searchDescription()) {
              
                ++playCounter;
               dataRecord.insert(tempPlay);

            }
            else {  }
         
          }
        
        // Read in the next Line
        getline(in, tmpGameID, ',');
        
    } // End while(!inFile->eof();
    
 } // storeData()


void storeData(const string filename, HashTable &dataRecord, const string &FileContent)
// Used by main()
{
    stringstream in(FileContent);
    string temp;
    
    getline(in, temp, (char) 10);             // Read in the first line and discard
    

    int playCounter = 0;
    // Create temporay variables to store the data from the file.
    string tmpGameID, tmpQuarter, tmpMin, tmpSec, tmpOffenseName,
    tmpDefenseName, tmpDown, tmpYardsToGo, tmpStartLocation,
    tmpDescription, tmpOffscore, tmpDefscore, tmpSeason;
    
    // Read in the variables;  Priming read
    getline(in, tmpGameID, ',');
    
    while (!in.eof()){
        
        getline(in, tmpQuarter, ',');
        getline(in, tmpMin, ',');
        getline(in, tmpSec, ',');
        getline(in, tmpOffenseName, ',');
        getline(in, tmpDefenseName, ',');
        getline(in, tmpDown, ',');
        getline(in, tmpYardsToGo, ',');
        getline(in, tmpStartLocation, ',');
        getline(in, tmpDescription, ',');
        getline(in, tmpOffscore, ',');
        getline(in, tmpDefscore, ',');
        getline(in, tmpSeason);
        
        if ((tmpYardsToGo != "") && (tmpStartLocation != "") && (tmpDown != "") && (tmpOffenseName != ""))
        {
            Play tempPlay(tmpGameID, tmpQuarter, tmpMin, tmpSec,
                          tmpOffenseName, tmpDefenseName, tmpDown, tmpYardsToGo,
                          tmpStartLocation, tmpDescription, tmpOffscore, tmpDefscore,
                          tmpSeason, playCounter);
            
            //  If tmpDescription contains the necessary words, create a new
            // Play object and add it to dataRecord
            if (tempPlay.searchDescription()) {
                
                ++playCounter;
                dataRecord.insert(tempPlay);
                
            }
            else {  }
            
        }
        
        // Read in the next Line
        getline(in, tmpGameID, ',');
        
    } // End while(!inFile->eof();
    
} // storeData()

void list(vector<string> &input, unordered_set<Play, PlayHasher> &dataRecord, vector<Play> &tempList)
// Used by main()
{
    
    if (input.size() == 8) {
        
        // Convert to integers where necessary and store the input in variables
        int minRemaining = atoi(input[2].c_str());
        string offense = input[3];              // Stores the Offense Team Code
        string defense = input[4];
        int down = atoi(input[5].c_str());      // Down
        int togo = atoi(input[6].c_str());      // Yards to Go for a First Down
        int ydline = atoi(input[7].c_str());    //  Stores the starting yardline
        
        
        unordered_set<Play, PlayHasher>::iterator itr;
        float relevance = 0.0;
        
        for (itr = dataRecord.begin(); itr != dataRecord.end(); ++itr){
            
             if (itr->isSimilar(offense, down, togo, ydline)){
                
                relevance = itr->calculateRelevance(minRemaining, defense, togo, ydline);
                
                Play tempSimilarData(itr->getGameID(),
                                     itr->getQuarter(),
                                     itr->getMin(),
                                     itr->getSec(),
                                     itr->getOffenseName(),
                                     itr->getDefenseName(),
                                     itr->getDown(),
                                     itr->getYardsToGo(),
                                     itr->getStartLocation(),
                                     itr->getDescription(),
                                     itr->getOffscore(),
                                     itr->getDefscore(),
                                     itr->getSeason(),
                                     relevance,
                                     itr->getPlayDescription(),
                                     itr->getPlayCount()
                                     );
                
                tempList.push_back(tempSimilarData);
            }
       }
        
       if (tempList.size() > 1){   // No need to sort if size() is <= 1
            
            //cout << "Sorting...." << endl;
            sortByRelevance ( tempList );
            
        } else if (tempList.size() == 0) {
            cout << "No similar play\n";
        } else {  }
    } else {
        cout << "No similar play\n";
    }
} // End list()

void list(vector<string> &input, HashTable &dataRecord, vector<Play> &tempList)
// Used by main()
{
    
    if (input.size() == 8) {
        
        // Convert to integers where necessary and store the input in variables
        int minRemaining = atoi(input[2].c_str());
        string offense = input[3];              // Stores the Offense Team Code
        string defense = input[4];
        int down = atoi(input[5].c_str());      // Down
        int togo = atoi(input[6].c_str());      // Yards to Go for a First Down
        int ydline = atoi(input[7].c_str());    //  Stores the starting yardline
        
        // Calculate the bucket number
        int Key = dataRecord.myhash( offense, down );
        

        // Generate the List of Plays
        dataRecord.handleList(tempList, Key, minRemaining, offense, defense, down, togo, ydline);
        
        if (tempList.size() > 1){   // No need to sort if size() is <= 1
            
            //dataRecord.mergeSort(tempList);
            //cout << "Sorting...." << endl;
            sortByRelevance ( tempList );
            
        } else if (tempList.size() == 0) {
            cout << "No similar play\n";
        } else {  }
        
    } else {
        cout << "No similar play\n";
    }
} // End list()


void sortByRelevance(vector<Play> &dR)
// Used by list()
// Sorts the vector by relevance in decending order from largest to smallest
{
    vector<Play>::iterator start;
    vector<Play>::iterator largest;
    vector<Play>::iterator current;
    
    Play temp;	            // Temp type is basetype of array
                            // Temporary storage during swap
    
    // Perform (numVectorElements - 1)  iterations
    for (start = dR.begin(); start < (dR.end() - 1); start++) {
        
        largest = start;
        
        // Scan the unsorted part of the array to find the smallest title
        for (current = (start + 1); current < dR.end(); current++)
        {
            if ((current->getRelevance() >= largest->getRelevance())) {
                
                if (current->getRelevance() > largest->getRelevance()){
                    largest = current;
                    
                } else if ((current->getRelevance() == largest->getRelevance()) && (current->getSeason() >= largest->getSeason())) {
                    
                    if (current->getSeason() > largest->getSeason()) {

                        largest = current;
                        
                    } else if (current->getSeason() == largest->getSeason()){
                    
                        if (current->getPlayCount() > largest->getPlayCount()) {
                            
                            largest = current;
                        } else { /* do nothing */ }
                        
                    } else { /* do nothing */ }
                    
                }
                else {}
                
            } // end if ((current->getRelevance() >= largest->getRelevance()))
            
        } // end for loop
        
        // Perform Exchage of array elements if necessary
        if (largest != start) {
            
            
            temp = *start;
            *start = *largest;
            *largest = temp;
            
            
            
         /*
            //  Temp = start
            temp.setGameID(start->getGameID());
            temp.setQuarter(start->getQuarter());
            temp.setMin(start->getMin());
            temp.setSec(start->getSec());
            temp.setOffenseName(start->getOffenseName());
            temp.setDefenseName(start->getDefenseName());
            temp.setDown(start->getDown());
            temp.setYardsToGo(start->getYardsToGo());
            temp.setStartLocation(start->getStartLocation());
            temp.setDescription(start->getDescription());
            temp.setRelevance(start->getRelevance());
            temp.setPlayDescription(start->getPlayDescription());
            temp.setPlayCount(start->getPlayCount());
            
            /// Start = Largest
            start->setGameID(largest->getGameID());
            start->setQuarter(largest->getQuarter());
            start->setMin(largest->getMin());
            start->setSec(largest->getSec());
            start->setOffenseName(largest->getOffenseName());
            start->setDefenseName(largest->getDefenseName());
            start->setDown(largest->getDown());
            start->setYardsToGo(largest->getYardsToGo());
            start->setStartLocation(largest->getStartLocation());
            start->setDescription(largest->getDescription());
            start->setRelevance(largest->getRelevance());
            start->setPlayDescription(largest->getPlayDescription());
            start->setPlayCount(largest->getPlayCount());

            
            // Largest = temp
            largest->setGameID(temp.getGameID());
            largest->setQuarter(temp.getQuarter());
            largest->setMin(temp.getMin());
            largest->setSec(temp.getSec());
            largest->setOffenseName(temp.getOffenseName());
            largest->setDefenseName(temp.getDefenseName());
            largest->setDown(temp.getDown());
            largest->setYardsToGo(temp.getYardsToGo());
            largest->setStartLocation(temp.getStartLocation());
            largest->setDescription(temp.getDescription());
            largest->setRelevance(temp.getRelevance());
            largest->setPlayDescription(temp.getPlayDescription());
            largest->setPlayCount(temp.getPlayCount());
*/
            
        }
    }  // end for loop
}

