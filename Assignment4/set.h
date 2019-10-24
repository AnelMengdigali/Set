
#ifndef SET_INCLUDED
#define SET_INCLUDED    1 

#include <iostream>
#include <string>
#include <vector>

class set
{
   std::vector< std::string > data;
     
public: 
   //Written constructor that operates on its own:

   set( ) = default;   
   set( const set& s ) = default;
   set& operator = ( const set& s ) = default; 
   ~set( ) = default;

   set( std::initializer_list< std::string > init ) 
   {  //Other constructor that does initialization of form s = { "123" }     considering a repeatition
      for (std::string s: init)
      {
         insert(s);
      } 
   }

   //Function prototypes:

   bool contains( const std::string& s ) const; 
      //Returns true if s is already on the set
   
   bool insert( const std::string& s );  
      //Returns true if the insertion took place

   size_t insert( const set& s ); 
      //Returns the number of inserted elements

   bool remove( const std::string& s );
      //Returns true if the set has s 

   size_t remove( const set& s );
      //Returns number of removed elements
 
   size_t size( ) const 
   {  //Returns current size of the set ( method of the vector )
      return data.size();
   }

   void clear( ) 
   {  //Removes all elements from the set ( method of the vector )
      data.clear();
   }

      //Bodies of methods for the use of iterators
   using const_iterator = std::vector< std::string > :: const_iterator;
   const_iterator begin( ) const { return data. begin( ); }
   const_iterator end( ) const { return data. end( ); }

   static bool equal( const std::string& s1, const std::string& s2 );
      //Returns true if two strings ( s1 and s2 ) are equal
 
};

   //Additional method that does printing
std::ostream& operator << ( std::ostream& out, const set& s ); 

   //Returns true if s1 is a subset of s2 
bool subset( const set& s1, const set& s2 );

   //Returns true if s1 and s2 are subsets of each other
inline bool equal( const set& s1, const set& s2 )
{
   return subset( s1, s2 ) && subset( s2, s1 );
}

#endif


