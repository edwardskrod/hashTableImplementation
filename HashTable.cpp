//
//  HashTable.cpp
//  proj5
//
//  Created by Edward J Skrod on 11/13/13.
//  Copyright (c) 2013 Edward J Skrod. All rights reserved.
//

#include "HashTable.h"

HashTable::HashTable( int currentTableSize ):currentSize(currentTableSize)
{
    List * myList;
    
    for (int lcv = 0; lcv < currentSize; ++lcv){
        
        myList = new List;
        
        theLists.push_back(myList);
    }
   
}
HashTable::~HashTable()
{   makeEmpty();    }

void HashTable::makeEmpty(  )
{
     for (int lcv = 0; lcv < currentSize; ++lcv){
        theLists[lcv]->clear( );
    }
}

void HashTable::insert( const Play &playObj )
{
    
    int Key = 0;
    
    // Hash the current play
    Key = playObj.Hash(this->currentSize);
    
    //cout << "Key: " << Key << " " << "Play: ";
    //playObj.Print(cout);
    
    theLists[Key]->push_back(playObj);
   
    
}
void HashTable::print( )

{
    List::iterator itr;
    
    for (int lcv = 0; lcv < currentSize; ++lcv){
        
        
        for (itr = theLists[lcv]->begin(); itr != theLists[lcv]->end(); ++itr){
        
            cout << *itr;
        }
     }
 }

int HashTable::myhash(string Off, int Down) const
// myhash is used by HashTable to create a unique
// bucket number for Plays based upon the Offense
// Team Name and the Down.   I assign a unique hash value
// to each team that is a factor of 4.  This allows each team
// to use 4 unique buckets.
{
    
    string Key = Off;
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
        }  else if ((Key == "JAX") || (Key == "JAC")){
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
    
   
        
        
        
    hash = hash + Down;
    
    return hash;
    
}

void HashTable::handleList(vector<Play> &relevantDataRecord,  int Key, int minRemaining, string Off, string Def, int Down, int Togo, int Ydline)
// Calculates the relevance of similar plays and pushes them onto a vector for sorting
{
    List::iterator itr;
    float relevance = 0.0;
    
    for (itr = theLists[Key]->begin(); itr != theLists[Key]->end(); ++itr){
        
        if (itr.getCurrent()->playObj.isSimilar(Off, Down, Togo, Ydline)){
            
            relevance = itr.getCurrent()->playObj.calculateRelevance(minRemaining, Def, Togo, Ydline);
            
            Play tempSimilarData(itr.getCurrent()->playObj.getGameID(),
                                 itr.getCurrent()->playObj.getQuarter(),
                                 itr.getCurrent()->playObj.getMin(),
                                 itr.getCurrent()->playObj.getSec(),
                                 itr.getCurrent()->playObj.getOffenseName(),
                                 itr.getCurrent()->playObj.getDefenseName(),
                                 itr.getCurrent()->playObj.getDown(),
                                 itr.getCurrent()->playObj.getYardsToGo(),
                                 itr.getCurrent()->playObj.getStartLocation(),
                                 itr.getCurrent()->playObj.getDescription(),
                                 itr.getCurrent()->playObj.getOffscore(),
                                 itr.getCurrent()->playObj.getDefscore(),
                                 itr.getCurrent()->playObj.getSeason(),
                                 relevance,
                                 itr.getCurrent()->playObj.getPlayDescription(),
                                 itr.getCurrent()->playObj.getPlayCount()
                                 );
            
            relevantDataRecord.push_back(tempSimilarData);
        }
    }
}

/*
 Adapted from
 http://simplestcodings.blogspot.com/2010/08/merge-sort-implementation-in-c.html
*/
void HashTable::mergeSort(vector<Play> &list1)
// Public member function to abstract the second list away from the
// user of the class
// Calculates the size of the list
{
    
   int num = static_cast<int>(list1.size());  // Returns the number of elements in the array
    vector<Play> list2(num);    // Creates a vector of Plays of size num
    // Call the private member function
    this->mergeSort(list1, list2, 0, (num -1));
}

void HashTable::mergeSort(vector<Play> &list1, vector<Play> &list2, int begin, int end )
{
    
    int pivot;
    
    if (begin < end)
    {
       pivot = ( begin + end ) / 2;
        
        // Recursivley (and conceptually) divide the list into smaller
        // and smaller units
        mergeSort(list1, list2, begin, pivot);
        mergeSort(list1, list2, (pivot + 1), end);
        merge(list1, list2, begin, pivot, end);
    }
}

void HashTable::merge(vector<Play> &list1, vector<Play> &list2, int begin, int pivot, int end)

{
    int h, i, j, k;
    h = begin;
    i = begin;
    j = pivot + 1;
    
    while ((h <= pivot) && (j <= end)) {
        
        if (list1[h].getRelevance() >= list1[j].getRelevance())  {
            list2[i] = list1[h];
            ++h;
        }
        
        else {
            list2[i] = list1[j];
            ++j;
        }
        
        ++i;
    }
    
    
    if (h > pivot) {
        
        for (k = j; k <= end; ++k)
        {
            
            list2[i] = list1[k];
            ++i;
        }
        
     }
    else {
        for (k = h; k <= pivot; ++k){
            list2[i] = list1[k];
            ++i;
        }
    }
    
    // copy list2 into list1 from begining to end
    for (k = begin; k <= end; ++k) {
        list1[k] = list2[k];
    }
}

int HashTable::totalNumRecords()
// This function returns the total number of Plays that are stored in the Hash Table
// Used for testing
{
    
    int numRecords = 0;
    
    for (int lcv = 0; lcv < currentSize; ++lcv) {
    
        numRecords += theLists[lcv]->size();
        
    }
    
     
    return numRecords;
}


