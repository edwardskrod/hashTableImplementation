//  List.cpp
//  Created by Edward J Skrod on 10/9/13.  Adapted from Weiss, "Data Structurs
//  And Algorithm Analysis in C++", 3rd edition, Section 3.5 "Implementation of a list."
#include <iostream>
#include "List.h"
using namespace std;

List::List()
// Default constructor creates an empty list.
// head and tail are initialized to NULL, size set to 0.
{  init( ); }

List::List(const List & rhs)
{
    // Initialize the list
    init();
 
    // Copy all of rhs to lhs
    for (const_iterator itr = rhs.begin( ); itr != rhs.end( ); ++itr){
        this->push_back( *itr );
    }
}

List::~List()
// Destructor deletes all items in the list.
{
    clear( );
    delete head;
    delete tail;
} // ~List

void List::init()
// Initializes List to size=0, with head and tail empty
// nodes, pointing to each other
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

const List& List::operator= ( const List & rhs)
{
    if (this == &rhs)
        return *this;
    clear( );
    for (const_iterator itr = rhs.begin( ); itr != rhs.end( ); ++itr){
        push_back( *itr );
    }
    return *this;
}


List::iterator List::insert( iterator itr, const Play &x )
{
    Node *p = itr.current;
    theSize++;
    
    return iterator( p->prev = p->prev->next = new Node( x, p->prev, p) );
    
}

List::iterator List::erase ( iterator itr )
{
    
    if (head != tail->prev){
        
        Node *p = itr.current;
        iterator retVal( p -> next );
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        
        theSize--;
        return retVal;
    }
    
    else {  // List is Empty
        cout << "Cannot erase from an empty list.\n";
       return itr;
    }
}

List::iterator List::erase ( iterator start, iterator end )
// Deletes all nodes from start to end - 1, position.
// Returns end
{
    for (iterator itr = start; itr != end;)
    {
        itr = erase( itr );
    }
    return end;
}

void List::clear( )
{
   while ( !empty( ) )
      pop_front( );
}


List::iterator List::search(string desc, float rel)
// Uses <cmath>
// search for Node containing desc == description and rel = relevance
// if yes, return the pointer to the listnode in the list
// if not, return NULL
{
    // search for matching description and relevance
    iterator iter = this->begin();    // nodePtr traverses the list
    
    bool found = false;
    //iter.getCurrent()->playObj.getQuarter(),
    while (iter != this->end() && (!found)) {
           
           if ((iter.getCurrent()->playObj.getDescription() == desc) &&
               (abs((rel - iter.getCurrent()->playObj.getRelevance())) <= .001))
           {
            found = true;
          }
          else {
               ++iter;
           }
        
    }
    return iter;
}

void List::move_to_front( iterator itr )
{
    if (itr == head->next){
        // Node is already the first node in the list.  No need to move to the front.
    } else {
    // Remove node from list.  Connect Node->prev and Node->next
    itr.getCurrent()->prev->next = itr.getCurrent()->next;
    itr.getCurrent()->next->prev = itr.getCurrent()->prev;
    
    // Insert Node at head->next
    // Connect head->next to itr
    head->next->prev = itr.getCurrent();
    itr.getCurrent()->next = head->next;
    
    // Connect head to itr
    itr.getCurrent()->prev = head;
    head->next = itr.getCurrent();
        
    }
}

void List::print( int n )
// printing the content and the list
{
    
    if (n <= 0) {
        return;
    }
    
    int count = 0;
    
    if (head == tail->prev) {
        cout << "list has no item.\n";
        return;
    }
    
    iterator itr = this->begin();
    
    while (itr != this->end() && (count < n)){
        cout << itr.getCurrent()->playObj.getPlayDescription() << " "
        << itr.getCurrent()->playObj.getMin() << " "
        << itr.getCurrent()->playObj.getOffenseName() << " "
        << itr.getCurrent()->playObj.getDefenseName() << " "
        << itr.getCurrent()->playObj.getDown() << " "
        << itr.getCurrent()->playObj.getYardsToGo()  << " "
        << itr.getCurrent()->playObj.getStartLocation() << "\n";
        
        ++itr;
        ++count;
    }
}  // print()
