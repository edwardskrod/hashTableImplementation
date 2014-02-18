//  Created by Edward J Skrod.
//  proj5, COP4530
//  Example input:
//  gameid, qtr, min, sec, off, def, down, togo, ydline, description, offscore, defscore, season
//  20070906_NO@IND, 1, 59, 49, IND, NO, 2, 10, 68, K.Keith left end pushed ob at IND 39 for 7 yards, 0, 0, 2007

#ifndef __proj1__lineData__
#define __proj1__lineData__

#include <iostream>
#include <string>
using namespace std;


const string DPR = "Deep pass right", DPL = "Deep pass left", DPM = "Deep pass middle",
SPR = "Short pass right", SPL = "Short pass left", SPM = "Short pass middle",
RTR = "Run to the right", RTL = "Run to the left", RTM = "Run to the middle",
FG = "Field goal attempt", PUNT = "Punt";

class Play
{

    friend ostream &operator<<(ostream& ostrm, const Play& obj);
    
private:
    string gameID;
    int quarter;            // The quarter.  1 - 4
    int min;                // minutes remaining in the game
    string sec;
    string offenseName;     // Offensive team name
    string defenseName;     // Defensive team name
    int down;               // the Down.  1 - 4
    int yardsToGo;          // The number of yards to go to get a first down
    int startLocation;      // Starting location for the down; 1 - 99
    string description;     // A description of the play
    string offscore;
    string defscore;
    string season;
    float relevance;       // Relevance of play
    string playDescription;
    int playCount;          // tracks the read position.  If playCount1 < playCount2,
                            //playCount1 was read before playCount2.
    
    
public:
    Play();
    // Constructor
    Play(string gID, string q, string m, string s, string oName, string dName, string dwn, string yTG, string sLoc, string desc, string oScore, string dScore, string sea, int playCounter = 0);
    
    // Constructor with relevance passed in;  data has already been formatted as int, double, etc.
    Play(string gID, int q, int m, string sec, string oName, string dName, int dwn, int yTG, int sLoc, string desc, string offscore, string defscore, string season, double rel, string playDesc, int playCounter);
    
    Play(const Play &obj);
    void operator=(const Play &obj);
    bool operator ==(const Play &obj) const;
    bool operator !=(const Play &obj) const;
    
    bool operator<(const Play &rhs) const;
    bool operator<=(const Play &rhs) const;
   
     
    // Accessors
    string getGameID() const;
    int getQuarter() const;
    int getMin() const;
    string getSec() const;
    string getOffenseName() const;
    string getDefenseName()const;
    int getDown() const;
    int getYardsToGo() const;
    int getStartLocation() const;
    string getDescription() const;
    string getOffscore() const;
    string getDefscore() const;
    string getSeason() const;
    float getRelevance() const;
    string getPlayDescription() const;
    int getPlayCount() const;
    
    // Mutators
    void setGameID(const string s);
    void setQuarter(const int i);
    void setMin(const int i);
    void setSec(const string s);
    void setOffenseName(const string s);
    void setDefenseName(const string s);
    void setDown(const int i);
    void setYardsToGo(const int i);
    void setStartLocation(const int i);
    void setDescription(const string s);
    void setOffscore(const string s);
    void setDefscore(const string s);
    void setSeason(const string s);
    void setRelevance(const float r);
    void setPlayDescription(const string s);
    void setPlayCount(const int pC);
    
    // Member Functions
    bool searchDescription();
    bool isSimilar(string Off, int Down, int Togo, int Ydline) const;
    float calculateRelevance(int Minutes, string Def, int ToGo, int Ydline) const;
    int Hash( int TableSize ) const;

    
    bool DeepPassRight();
    bool DeepPassLeft();
    bool DeepPassMiddle();
    bool ShortPassRight();
    bool ShortPassLeft();
    bool ShortPassMiddle();
    bool RunRight();
    bool RunLeft();
    bool RunMiddle();
    bool FieldGoal();
    bool Punts();
    
    bool ClassTest(ostream &os);
    void Print(ostream & os) const;
    
    
};
#endif /* defined(__proj1__lineData__) */
