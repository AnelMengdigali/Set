
#ifndef SET_INCLUDED
#define SET_INCLUDED    1

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>

//Implementation of set using hash table:

class set 
{  //Fields of the class:
   size_t set_size;
   double max_load_factor;
   std::vector< std::list< std::string >> buckets;

public:
//Methods of the class:

   //Default constructor:
   set( size_t num_buckets = 4, double max_load_factor = 3.0 ) 
      : set_size{ 0 },
        max_load_factor{ max_load_factor },
        buckets{ std::vector< std::list< std::string >> ( num_buckets ) }
   {
      if( num_buckets == 0 )
         throw std::runtime_error( "number of buckets cannot be zero" ); 
   }

   set( const set& s ) = default; 
      //Copy constructor

   set& operator = ( const set& s ) = default;
      //Assignment operator

   ~set() = default;
      //Destructor

   //Other constructor (from initializer list):
   set(std::initializer_list<std::string > init )
      :set( ) 
   {
      for( const auto& s : init )
         insert(s);
   }

   bool contains( const std::string& s ) const;
      //Returns true if the hash table has s

   bool simp_insert( const std::string& s ); 
      //Does an insertion only; returns true if the insertion took place

   bool insert( const std::string& s );
      //Call for the rehashing; returns true if the insertion took place.

   bool remove( const std::string& s );
      //Returns true if s was removed

   //Returns a number of strings in the hash table:
   size_t size() const
   { 
      return set_size;
   }

   //Returns true if the hash table empty:
   bool isempty() const
   {
      return set_size == 0;
   }

   //Computes a value of the load factor:
   double loadfactor() const 
   {
      return static_cast<double> ( set_size ) / buckets. size( );  
   }

   //Computes the stdev value:
   double standarddev() const 
   {
      double sum = 0.0;
      double lf = loadfactor();

      for ( const auto& l : buckets ) 
      {
	  double dif = l.size() - lf;
          sum += dif*dif;
      }

      return sqrt( sum / buckets. size() );
   }

   void clear();
      //Removes all the elements from the hash table
     
   void rehash( size_t newbucketsize );
      //Rehashes when load factor becomes bigger than max_load_factor
 
   std::ostream& print( std::ostream& out ) const; 
      //Does a printing

   std::ostream& printstatistics( std::ostream& out ) const;
      //Prints the fileds 

   //For debugging:
 
   size_t getnrbuckets( ) const  
   {
      return buckets. size( ); 
   }

   const std::list< std::string > & getbucket( size_t i ) 
   {
      return buckets[i];
   }
};

//Provides a nice printing:
inline std::ostream& operator << ( std::ostream& out, const set& s ) 
{
   return s.print( out );
}

bool equal( const std::string& s1, const std::string& s2 );
   //Returns true if s1 and s2 are equal

size_t hash( const std::string& s );
   //Returns computed hash value of s

#endif


