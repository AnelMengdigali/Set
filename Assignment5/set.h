
#ifndef SET_INCLUDED
#define SET_INCLUDED    1 

#include <iostream>
#include <string>
#include <vector>

bool equal( const std::string& s1, const std::string& s2 );
   //Returns true if s1 and s2 are equal

bool before( const std::string& s1, const std::string& s2 );
   //Returns true if s1 comes before s2 in lexicographic order

//Implementation of the BST: 
struct treenode
{
   std::string val;
   treenode* left;
   treenode* right;

   treenode( const std::string& val )
      : val{ val },
        left{ nullptr },
        right{ nullptr }  
   { }

   treenode( std::string&& val )
      : val{ std::move(val) },
        left{ nullptr },
        right{ nullptr } 
   { }
};

void deallocate( treenode* n ); 
   //Deallocate complete tree n (used by destructor)

void writecopy( treenode** to, treenode* from );
   //Used by copy constructor and assignment operator

const treenode* find( const treenode* n, const std::string& el );
   //Function that is needed for lookup 

treenode** find( treenode** n, const std::string& el );
   //Function that is needed for insertion and removal

void rightinsert( treenode** into, treenode* n );
   //Insert n at the right most position in into

void print( std::ostream& out, const treenode* n, size_t indent );
   //Print the BST as it is

size_t size( const treenode* n );
   //Returns the total size of tree

size_t height( const treenode* n );
   //Returns the height of the tree starting at n

size_t log_base2( size_t s ); 
   //Returns logarithmic with base 2 value of the s

class set
{
   treenode* tr;

public:
   //Default constructor:
   set( ) 
      : tr{ nullptr } 
   { } 

   //Copy constructor:
   set( const set& s ) 
      : tr{ nullptr }
   {
      writecopy( &tr, s. tr );
   }

   //Assignment operator
   set& operator = ( const set& s ) 
   {
      if( tr != s. tr )
      {
         deallocate( tr );
         writecopy( &tr, s. tr );
      }
      return *this;
   }

   //Destructor:
   ~set( ) { deallocate( tr ); }

   //Other constructor:
   set( std::initializer_list< std::string > init )
      : tr{ nullptr }
   {
      for( const auto& s : init ) 
         insert( s );
   } 
  
   const std::string& top( ) const { return tr -> val; }
      // Return element on top. The tree must be non empty.
 
   bool contains( const std::string& s ) const;
      //Returns true if the set have el

   bool insert( const std::string& s );
      // Returns true if the insertion took place.

   bool remove( const std::string& s );
      // Returns true if s was successfully removed
 
   size_t size( ) const { return ::size( tr ); }
      //Returns the total size of tree

   size_t height( ) const { return ::height( tr ); }
      //Returns the height of the tree

   bool isempty( ) const { return ! tr; }
      //Returns true if the BST is empty 

   void clear( ) { deallocate( tr ); tr = nullptr; }
      //Remove all elements from the BST
  
   void checksorted( ) const;
      //For self-checking: 

   std::ostream& print( size_t indent, std::ostream& out ) const;
};

//Does printing:
inline std::ostream& operator << ( std::ostream& out, const set& s )
{   
   return s. print( 0, out );
}


#endif

