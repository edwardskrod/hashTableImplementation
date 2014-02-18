//  Play.cpp
//  Created by Edward J Skrod.
//  Play::searchDescription() was adapted from Ashok Srinivasan's Proj 1
//  solution.

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Play.h"
using namespace std;

// FRIEND FUNCTIONS
ostream& operator<<(ostream& ostrm, const Play& obj) {
    cout << obj.getPlayDescription() << " " << obj.getMin() << " " << obj.getOffenseName()
         << " " << obj.getDefenseName() << " " << obj.getDown() << " " << obj.getYardsToGo()
         << " " << obj.getStartLocation();
    cout << "  " << obj.getRelevance() << "\n";
    
    return ostrm;
}

// Default Constructor
Play::Play()
{ /* :gameID(""), quarter(0), min(0), sec(""), offenseName(""), defenseName(""), down(0), yardsToGo(0), startLocation(0), description(""), offscore(""), defscore(""), season(""), relevance(0.0), relevanceCount(0) */ }

// Constructor that only accepts strings
Play::Play(string gID, string q, string m, string s, string oName, string dName, string dwn, string yTG, string sLoc, string desc, string oScore, string dScore, string sea, int playCounter)
{
    gameID = gID;
    sec = s;
    offscore = oScore;
    defscore = dScore;
    season = sea;
    quarter = atoi(q.c_str());
    min = atoi(m.c_str());
    down = atoi(dwn.c_str());
    yardsToGo = atoi(yTG.c_str());
    startLocation = atoi(sLoc.c_str());
    offenseName = oName;
    defenseName = dName;
    description = desc;
    relevance = 0.0;
    playCount = playCounter;
}

// Constructor
Play::Play(string gID, int q, int m, string sec, string oName, string dName, int dwn, int yTG, int sLoc, string desc, string offscore, string defscore, string season, double rel, string playDesc, int playCounter):gameID(gID), quarter(q), min(m), sec(sec), offenseName(oName), defenseName(dName), down(dwn), yardsToGo(yTG), startLocation(sLoc), description(desc), offscore(offscore), defscore(defscore), season(season), relevance(rel), playDescription(playDesc), playCount(playCounter)
{ /* left intentionally blank */ }

// Copy Constructor
Play::Play(const Play &obj)
{
    gameID = obj.getGameID();
    quarter = obj.getQuarter();
    min = obj.getMin();
    sec = obj.getSec();
    offenseName = obj.getOffenseName();
    defenseName = obj.getDefenseName();
    down = obj.getDown();
    yardsToGo = obj.getYardsToGo();
    startLocation = obj.getStartLocation();
    description = obj.getDescription();
    offscore = obj.getOffscore();
    defscore = obj.getDefscore();
    season = obj.getSeason();
    relevance = obj.getRelevance();
    playDescription = obj.getPlayDescription();
    playCount = obj.getPlayCount();
  
}

void Play::operator=(const Play &obj)
{
    // string gID, int q, int m, string sec, string oName, string dName, int dwn, int yTG, int sLoc, string desc, string offscore, string defscore, string season, double rel, string playDesc
   /*Play * tempObj = new Play(obj.getGameID(), obj.getQuarter(), obj.getMin(), obj.getSec(),
                              obj.getOffenseName(), obj.getDefenseName(),obj.getDown(), obj.getYardsToGo(),
                              obj.getStartLocation(), obj.getDescription(), obj.getOffscore(), obj.getDefscore(),
                              obj.getSeason(), obj.getRelevance(), obj.getPlayDescription(), obj.getPlayCount());*/
    

    this->gameID = obj.getGameID();
    this->min = obj.getMin();
    this->sec = obj.getSec();
    this->offenseName = obj.getOffenseName();
    this->defenseName = obj.getDefenseName();
    this->down = obj.getDown();
    this->yardsToGo = obj.getYardsToGo();
    this->startLocation = obj.getStartLocation();
    this->description = obj.getDescription();
    this->offscore = obj.getOffscore();
    this->defscore = obj.getDefscore();
    this->season = obj.getSeason();
    this->relevance = obj.getRelevance();
    this->playDescription = obj.getPlayDescription();
    this->playCount = obj.getPlayCount();


    
}

bool Play::operator<(const Play &rhs) const
// The OFF field is used to compare plays, using the string class's compare function, with a negative result
// indicating <. (Recall that a comparison is required to insert objects into a BST.) If these fields are
// identical for two records, then the one from the earlier year is considered smaller. If these too are
// identical, then the one occurring earlier in the input file is considered smaller.
{

    // < operator is used to compare root / rhs,  with x (item to be inserted )
    if ( this->getOffenseName() < rhs.getOffenseName() )
        return true;
    
    return false;
}

// Used by BinarySearchTree.cpp to insert plays into the tree
bool Play::operator<=(const Play &rhs) const
// compares x (item to be inserted) with root (rhs)
{
    

    if ( this->getOffenseName() < rhs.getOffenseName() )
        return true;
    
    if ( (this->getOffenseName() == rhs.getOffenseName() ) && (this->getSeason() < rhs.getSeason() ))
        return true;
    
    return false;
    
}

bool Play::operator ==(const Play &rhs) const
{
    /*
     Should always return false because no plays will be equal.
     
    if ( ( this->getDescription() == rhs.getDescription()) && (this->getYardsToGo() == rhs.getYardsToGo() ) )
        return true;
    */
    
    return false;
}


bool Play::operator !=(const Play &rhs) const
{
    /*
    if ( ( this->getDescription() != rhs.getDescription()) || (this->getYardsToGo() != rhs.getYardsToGo() ) )
        return true;
    
    
    return false;
     */
    return true;

}

// Get Functions
string Play::getGameID() const
    { return gameID; }

int Play::getQuarter() const
    { return quarter; }

int Play::getMin() const
    { return min; }

string Play::getSec() const
    { return sec; }

string Play::getOffenseName() const 
    { return offenseName; }

string Play::getDefenseName() const 
    { return defenseName; }

int Play::getDown() const 
    { return down; }

int Play::getYardsToGo() const 
    { return yardsToGo; }

int Play::getStartLocation() const 
    { return startLocation; }

string Play::getDescription() const 
    { return description; }

string Play::getOffscore() const
    { return offscore; }

string Play::getDefscore() const
    { return defscore; }

string Play::getSeason() const
    { return season; }

float Play::getRelevance() const
    { return relevance; }

string Play::getPlayDescription() const
    { return playDescription; }

int Play::getPlayCount() const
{ return playCount; }

// Mutators
void Play::setGameID(const string s)
    { gameID = s; }

void Play::setQuarter(const int i)
    { quarter = i; }

void Play::setMin(const int i)
    { min = i; }

void Play::setSec(const string s)
    { sec = s; }

void Play::setOffenseName(const string s)
    { offenseName = s; }

void Play::setDefenseName(const string s)
    { defenseName = s; }

void Play::setDown(const int i)
    { down = i; }

void Play::setYardsToGo(const int i)
    { yardsToGo = i; }

void Play::setStartLocation(const int i)
    { startLocation = i; }

void Play::setDescription(const string s)
    { description = s; }

void Play::setOffscore(const string s)
    { offscore = s; }

void Play::setDefscore(const string s)
    { defscore = s; }

void Play::setSeason(const string s)
    { season = s; }

void Play::setRelevance (const float r)
    { relevance = r; }

void Play::setPlayDescription(const string s)
    { playDescription = s; }

void Play::setPlayCount(const int pC)
{     playCount = pC;    }


bool Play::isSimilar(string Off, int Down, int Togo, int Ydline) const
{
    if( Off != offenseName || Down != down ) {
        return false;
    }
    if(abs( Togo - yardsToGo ) > 1){
        return false;
    }
    if(fabs( Ydline - startLocation ) <= 0.1 * Ydline ){
        return true;
    }
    else {
        return false;
    }
}

bool Play::searchDescription()
// Adapted from Ashok Srinivasan Proj 1 Solution File
// Function searches for matching words in the Play Description field.
// If found, it set's the playDescription to the Play type and returns true
{

    string desc = getDescription();

    if(desc.find("deep")!=string::npos && desc.find("pass")!=string::npos)
    {
        if(desc.find("right")!=string::npos) {
            this->setPlayDescription(DPR);
            return true;
        }
        if(desc.find("left")!=string::npos) {
            this->setPlayDescription(DPL);
            return true;
        }
        if(desc.find("middle")!=string::npos){
            this->setPlayDescription(DPM);
            return true;
        }
    }
    
    if(desc.find("short")!=string::npos && desc.find("pass")!=string::npos)
    {
        if(desc.find("right")!=string::npos){
            this->setPlayDescription(SPR);
            return true;
        }
        if(desc.find("left")!=string::npos){
            this->setPlayDescription(SPL);
            return true;
        }
        if(desc.find("middle")!=string::npos){
            this->setPlayDescription(SPM);
            return true;
        }
    }
    
    if(desc.find("right")!=string::npos){
        this->setPlayDescription(RTR);
        return true;
    }
    if(desc.find("left")!=string::npos){
        this->setPlayDescription(RTL);
        return true;
    }
    if(desc.find("middle")!=string::npos){
        this->setPlayDescription(RTM);
        return true;
    }
    
    if(desc.find("field")!=string::npos && desc.find("goal")!=string::npos) {
        this->setPlayDescription(FG);
        return true;
    }
    if(desc.find("punts")!=string::npos){
        this->setPlayDescription(PUNT);
        return true;
    }
    
    return false;

}

float Play::calculateRelevance(int Minutes, string Def, int ToGo, int Ydline) const
{
    float relevance = 0.0;
    
    relevance = -(abs( Minutes - min )* 5.0/3.0 + abs( ToGo - yardsToGo )
                  + abs( Ydline - startLocation));
    
    if( Def == defenseName )
        relevance += 100.0;
    
    return relevance;
    
}



bool Play::DeepPassRight()
{
    string desc = getPlayDescription();
    
    if (desc == DPR)
        return true;
    else
        return false;
}

bool Play::DeepPassLeft()
{
    string desc = getPlayDescription();
    
    if (desc == DPL)
        return true;
    else
        return false;
}
bool Play::DeepPassMiddle()
{
    string desc = getPlayDescription();
    
    if (desc == DPM)
        return true;
    else
        return false;
}

bool Play::ShortPassRight()
{
    string desc = getPlayDescription();
    
    if (desc == SPR)
        return true;
    else
        return false;
}
bool Play::ShortPassLeft()
{
    string desc = getPlayDescription();
    
    if (desc == SPL)
        return true;
    else
        return false;
}

bool Play::ShortPassMiddle()
{
    string desc = getPlayDescription();
    
    if (desc == SPM)
        return true;
    else
        return false;
}

bool Play::RunRight()
{
    string desc = getPlayDescription();
    
    if (desc == RTR)
        return true;
    else
        return false;

}

bool Play::RunLeft()
{
    string desc = getPlayDescription();
    
    if (desc == RTL)
        return true;
    else
        return false;
}

bool Play::RunMiddle()
{
    string desc = getPlayDescription();
    
    if (desc == RTM)
        return true;
    else
        return false;
}

bool Play::FieldGoal()
{
    string desc = getPlayDescription();
    
    if (desc == FG)
        return true;
    else
        return false;

}

bool Play::Punts()
{
    string desc = getPlayDescription();
    
    if (desc == PUNT)
        return true;
    else
        return false;
}

bool Play::ClassTest(ostream &os)
{
    bool result = true;
    
       // Play(string gID, string q, string m, string s, string oName, string dName, string dwn, string yTG, string sLoc, string desc, string oScore, string dScore, string sea);
    Play P("20120905_DAL@NYG","1","46","35","NYG","DAL","1","10","53","(1:35) A.Bradshaw left end to 50 for 3 yards (S.Lissemore A.Spencer).","0","0","2012");
    
    os << "  Starting tests of 'Play'\n\n";
    
    
    if(P.getQuarter()==1 && P.getMin()==46 && P.getOffenseName()=="NYG" && P.getDefenseName()=="DAL"
       && P.getDown()==1 && P.getYardsToGo()==10 && P.getStartLocation()==53 && P.getDescription() == "(1:35) A.Bradshaw left end to 50 for 3 yards (S.Lissemore A.Spencer)." ){
        os << "Play stores and retrieves data correctly\n";
    

    }
    else
    {
        os << "ERROR: Play data is not correct. It contains the following, instead of: 1, 46, NYG, DAL, 1, 10, 53, (description), 7, (fullplay)\n";
        cout << P;
        result = false;
    }

    //   calculateRelevance(int Minutes, string Def, int ToGo, int Ydline)
    P.calculateRelevance(46, "DAL", 10, 58);
    if(P.relevance == 95)
        os << "Play computes relevance correctly\n";
    else
    {
        os << "ERROR: Relevance is wrong. It should be 95 instead of " << relevance << endl;
        result = false;
    }
    
    os << endl;
    
    return result;
}

void Play::Print(ostream & os) const
{
    
    if (this != NULL){
    os << getPlayDescription() << " "
        << getMin() << " "
        << getOffenseName() << " "
        << getDefenseName() << " "
        << getDown() << " "
        << getYardsToGo()  << " "
        << getStartLocation()  //<< " "
         //<< getPlayCount()
        << "\n";
    }
}

int Play::Hash( int TableSize ) const
// Hash() performs a simple hash on the
// calling object's Offense name which is in the format
// MIA.    This results in 32 unique hash values.
// Hash() then adds the down to this value.  Downs are 1 - 4


{
    
    string Key = this->getOffenseName();
   int hash = 0;
   
    
    if (Key == "ARI"){
        hash = 0;
    } else if (Key == "ATL"){
        hash = 4;
    } else if (Key == "BAL"){
        hash = 8;
    } else if (Key == "BUF"){
        hash = 16;
    } else if (Key == "CAR"){
        hash = 20;
    } else if (Key == "CHI"){
        hash = 24;
    } else if (Key == "CIN"){
        hash = 28;
    } else if (Key == "CLE"){
        hash = 32;
    } else if (Key == "DAL"){
        hash = 36;
    } else if (Key == "DEN"){
        hash = 40;
    } else if (Key == "DET"){
        hash = 44;
    } else if (Key == "GB"){
        hash = 48;
    } else if (Key == "HOU"){
        hash = 52;
    } else if (Key == "IND"){
        hash = 56;
    } else if ((Key == "JAX") || (Key == "JAC")){
        hash = 60;
    } else if (Key == "KC"){
        hash = 64;
    } else if (Key == "MIA"){
        hash = 68;
    } else if (Key == "MIN"){
        hash = 72;
    } else if (Key == "NE"){
        hash = 76;
    } else if (Key == "NO"){
        hash = 80;
    } else if (Key == "NYG"){
        hash = 84;
    } else if (Key == "NYJ"){
        hash = 88;
    } else if (Key == "OAK"){
        hash = 92;
    } else if (Key == "PHI"){
        hash = 96;
    } else if (Key == "PIT"){
        hash = 100;
    } else if (Key == "SD"){
        hash = 104;
    } else if (Key == "SEA"){
        hash = 108;
    } else if (Key == "SF"){
        hash = 112;
    } else if (Key == "STL"){
        hash = 116;
    } else if (Key == "TB"){
        hash = 120;
    } else if (Key == "TEN"){
        hash = 124;
    } else if (Key == "WAS"){
        hash = 128;
    } else {
        
        cout << "Play.cpp: Hash() Error assigning a hash to a team!\n";
        cout << Key << " does not have a name assocated to a hash num.\n";
    }
    
    hash = hash + this->getDown();

    return hash;
    
    
    /*
     for ( int lcv = 0; lcv != Key.size(); ++lcv){
     
     hash = 37 * hash + (Key[lcv] - 'a' + 1 );
     }
     
     hash = (hash % TableSize) + this->getDown();
     
     // Change the value of hash to be in our hashTable
     // if getDown makes hash too big
     // Need to account for 4 downs
     // wrap it in an if statement so that each hash doesn't have 4 atomics to perform
     if (hash >= TableSize) {
     
     if (hash == (TableSize))                hash = 0;       // getDown() = 1
     else if (hash == (TableSize + 1))       hash = 1;       // getDown() = 2
     else if (hash == (TableSize + 2))       hash = 2;       // getDown() = 3
     else if (hash == (TableSize + 3))       hash = 3;       // getDown() = 4
     
     }
     */
    
}






