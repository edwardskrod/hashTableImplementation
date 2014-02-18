//
//  HashTable.h
//  proj5
//
//  Created by Edward J Skrod on 11/13/13.
//  Copyright (c) 2013 Edward J Skrod. All rights reserved.
//

#ifndef __proj5__HashTable__
#define __proj5__HashTable__

#include <iostream>
#include <vector>
#include "List.h"
#include "Play.h"

class HashTable
{
public:
    explicit HashTable( int currentTableSize = 133 );
    ~HashTable( );

    void makeEmpty( );
    
    void insert( const Play &x );
    void print( );
    int getCurrentSize()
    { return currentSize; }
    
    int myhash( string Off, int Down ) const;
  
    void handleList(vector<Play> &relevantDataRecord,  int Key, int minRemaining, string Off, string Def, int Down, int Togo, int Ydline);
    
    // Public member function takes the temporary list as a parameter
    void mergeSort(vector<Play> &list1);
    
    int totalNumRecords();
    
private:
    
    // Private member functions for merge Sort
    void mergeSort( vector<Play> &list1, vector<Play> &list2, int begin, int end );
    void merge(vector<Play> &list1, vector<Play> &list2, int begin, int pivot, int end);
    
     vector<List*> theLists;
     int currentSize;
};
#endif /* defined(__proj5__HashTable__) */

