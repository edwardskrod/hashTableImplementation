//  List.h
//  Created by Edward J Skrod on 10/9/13.  Adapted from Weiss, "Data Structurs
// And Algorithm Analysis in C++", 3rd edition, Section 3.5 "Implementation of a list."
#ifndef __proj3__List__
#define __proj3__List__

#include <iostream>
#include <cmath>
#include "Play.h"

using namespace std;

class List
{
private:
    
    class Node
    {
    public:
        
        Play playObj;
        Node *prev;       // Pointer to previous node
        Node *next;       // Pointer to next node
        
        Node(const Play & obj = Play( ), Node *p = NULL, Node *n = NULL)
        : playObj(obj), prev(p), next(n) { }
    };
public:
    class const_iterator
    {
        
    public:
        const_iterator( ) : current( NULL )
        {  /* left intentionally blank */    }
        
        const Play & operator* ( ) const
        { return retrieve ( ); }
        
        const_iterator & operator++ ( )
        {
        
          current = current->next;
          return *this;
        }
        
        const_iterator operator++ ( int )
        {
            const_iterator old = *this;
            ++ ( *this ) ;
            return old;
        }
        
        const_iterator & operator-- ( )
        {
            
            current = current->prev;
            
            return *this;
        }
        
        const_iterator operator-- ( int )
        {
            const_iterator old = *this;
            -- ( *this ) ;
            return old;
        }
        
        const_iterator operator+( int x ){
            
            const_iterator temp = *this;
            
            ++( temp );
            
            return temp;
        }
        
        
        bool operator== (const const_iterator & rhs ) const
        { return current == rhs.current; }
        
        bool operator != ( const const_iterator & rhs ) const
        { return !(*this == rhs ); }
        
        Node *getCurrent ( )
        { return current; }
        
        
    protected:
        Node *current;
        
        Play &retrieve( ) const
        { return current->playObj; }
        
        const_iterator( Node *p ) : current( p )
        { /* intentionally left blank */ }
        
        friend class List;
 
    };

    class iterator : public const_iterator
    {
       
    public:
        iterator ( )
        { }
        
        Play & operator* ( )
        { return retrieve( ) ; }
        
        const Play & operator* ( ) const
        { return const_iterator::operator* ( ); }
        
        iterator & operator++ ( )
        {
            current = current->next;
            return *this;
        }
        
        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }
        iterator & operator-- ( )
        {
            current = current->prev;
            return *this;
        }
        
        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }
        iterator operator+( int x ){
            
          iterator temp = *this;
            
          ++( temp );
            
          return temp;
        }
        
        
    protected:
        iterator( Node *p ) : const_iterator( p )
        { }
        friend class List;
    };
  
   // CONST REVERSE ITERATOR
    class const_reverse_iterator
    {
        
    public:
        const_reverse_iterator( ) : current( NULL )
        {  /* left intentionally blank */    }
        
        const Play & operator* ( ) const
        { return retrieve ( ); }
        
        const_reverse_iterator & operator++ ( )  // Behaves like const_iterator operator--
        {
            current = current->prev;
            return *this;
        }
        
        const_reverse_iterator operator++ ( int ) // Behaves like const_iterator operator--
        {
            const_reverse_iterator old = *this;
            ++ ( *this ) ;
            return old;
        }
        
        const_reverse_iterator & operator-- ( ) // Behaves like const_iterator operator++
        {
            current = current->next;
            return *this;
        }
        
        const_reverse_iterator operator-- ( int ) // Behaves like const_iterator operator++
        {
            const_reverse_iterator old = *this;
            -- ( *this ) ;
            return old;
        }
        
       
        bool operator== (const const_reverse_iterator & rhs ) const
        { return current == rhs.current; }
        
        bool operator != ( const const_reverse_iterator & rhs ) const
        { return !(*this == rhs ); }
        
        Node *getCurrent ( )
        { return current; }
        
        
    protected:
        Node *current;
        
        Play &retrieve( ) const
        { return current->playObj; }
        
        const_reverse_iterator( Node *p ) : current( p )
        { /* intentionally left blank */ }
        
        friend class List;
        
    };
    // END CONST REVERSE ITERATOR

    class reverse_iterator : public const_reverse_iterator
    {
        
    public:
        reverse_iterator ( )
        { }
        
        Play & operator* ( )
        { return retrieve( ) ; }
        
        
        reverse_iterator & operator++ ( )
        {
            current = current->prev;
            return *this;
        }
        
        reverse_iterator operator++ ( int )
        {
            reverse_iterator old = *this;
            ++( *this );
            return old;
        }
        reverse_iterator & operator-- ( )
        {
            current = current->next;
            return *this;
        }
        
        reverse_iterator operator-- ( int )
        {
            reverse_iterator old = *this;
            --( *this );
            return old;
        }
        reverse_iterator operator+( int x ){
            
            reverse_iterator temp = *this;
            
            ++( temp );
            
            return temp;
        }
        
        
    protected:
        reverse_iterator( Node *p ) : const_reverse_iterator( p )
        { }
        friend class List;
    };

public:
    List();
    List(const List &rhs);
    ~List();
    void init( );
    
    const List& operator= ( const List & rhs);
    
    iterator begin( )
    { return iterator(head->next); }
    
    const_iterator begin( ) const
    { return const_iterator(head->next); }
   
    reverse_iterator rbegin( )
    { return reverse_iterator(tail->prev);  }
    
    const_reverse_iterator rbegin( ) const
    {  return const_reverse_iterator(tail->prev); }
    
    iterator end( )
    { return iterator( tail ); }
    
    const_iterator end( ) const
    { return const_iterator( tail ); }
    
    reverse_iterator rend()
    {  return reverse_iterator( head ); }
    
    const_reverse_iterator rend() const
    {  return const_reverse_iterator( head );  }
    
    
    int size( ) const
    { return theSize; }
    
    bool empty( ) const
    { return size ( ) == 0; }
    
    void clear( );
    
    Play &front( )
    { return *begin( ); }
    
    const Play & front ( ) const
    { return *begin( ); }
    
    Play & back ( )
    { return *(--end( ));  }
    
    const Play & back( ) const
    { return *(--end( )); }
    
    void push_front( const Play &x )
    { insert ( begin( ), x ); }
    
    void push_back( const Play &x )
    {  insert( end( ), x ); }
    
    void pop_front( )
    { erase(begin( ) ); }
     
     void pop_back( )
    { erase( --end( )); }
    
    
    iterator insert( iterator itr, const Play &x );
    iterator erase ( iterator itr );
    iterator erase ( iterator start, iterator end );
    iterator search(string desc, float rel);
    
    void move_to_front( iterator itr );
    void print(int n);
  
private:
    Node *head;
    Node *tail;
    
    int theSize;             // The size of the list (how many nodes)
};


#endif /* defined(__proj3__List__) */
