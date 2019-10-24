
#include "set.h"

void print( std::ostream& out, const treenode* n, size_t indent )
{
   for( size_t i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}

void checksorted( 
          treenode* n, 
          const std::string* lowerbound, 
          const std::string* upperbound )
{
   while(n) 
   {
      if( lowerbound && !before( *lowerbound, n -> val ))
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if( upperbound && !before( n -> val, *upperbound ))
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checksorted( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
} 

void writecopy( treenode** to, treenode* from )
{
   while( from )
   {
      *to = new treenode{ from -> val };

      writecopy( & (*to) -> left, from -> left );
      to = & (*to) -> right;
      from = from -> right;
   }
}

void deallocate( treenode* n )
{
   while(n)
   {
      deallocate( n -> left );
      treenode* bye = n;
      n = n -> right;
      delete bye;
   }
}

size_t log_base2( size_t s )
{  
   size_t count = 0;
   
   while( s >= 2 )
   {
      s = s / 2;
      ++ count;
   }

   return count;
}

bool equal( const std::string& s1, const std::string& s2 )
{
   if( s1. size() != s2. size() ) return false;

   for( size_t i = 0; i != s1. size(); ++ i )
   {
      if( tolower( s1[i] ) == tolower( s2[i] ) ) continue;
      
      return false;	   
   }

return true;
}

bool before( const std::string& s1, const std::string& s2 )
{ 
   for( size_t i = 0; i != s1. size() || i != s2. size(); ++ i )
   {
      if( tolower( s1[i] ) == tolower( s2[i] ) ) continue;          
      else if( tolower( s1[i] ) < tolower( s2[i] ) ) return true;
      else return false;
   }  

   if( s1. size() <= s2. size() ) return true;
   else return false; 
}

const treenode* find( const treenode* n, const std::string& el )
{
   if( n == nullptr ) return n;
   else if( equal( n -> val, el ) ) return n;
   else if( before( el, n -> val ) ) return find( n -> left, el );
   else return find( n -> right, el );
   
}  

treenode** find( treenode** n, const std::string& el )
{
   if( *n == nullptr ) return n;
   else if( equal( (*n) -> val,el ) ) return n;
   else if( before( el, (*n) -> val ) ) return find( &( (*n) -> left ), el );
   else return find( &( (*n) -> right ), el );
   
}
 
void rightinsert( treenode** into, treenode* n )
{
   while( ( *into ) -> right != nullptr )
      into = (& ( *into ) -> right );
   
   ( *into ) -> right = n;
   
}

size_t size( const treenode* n )
{
   if( n == nullptr ) return 0;

   return 1 + size( n -> left ) + size( n -> right );
}
 
size_t height( const treenode* n )
{ 
   if( n == nullptr ) return 0;

   size_t height_left = height( n -> left );
   size_t height_right = height( n -> right );
  
   if (n -> left == nullptr && n -> right == nullptr) return 1;
    
   if( height_left >= height_right )
   {  
      ++height_left;
      return height_left;
   }
   else 
   {
      ++height_right;
      return height_right;
   }   	  
}

bool set::insert( const std::string& el ) 
{
   treenode **n = find( &tr, el );

   if( *n != nullptr ) return false;
   else
   {
      *n = new treenode{ el };   
      return true;
   }
}

bool set::contains( const std::string& el ) const 
{
   return find( tr, el ) != nullptr; 
}

bool set::remove( const std::string& el ) 
{ 
   treenode **n = find( &tr, el );
   if( (*n) == nullptr ) return false;

   if( (*n) -> left == nullptr && (*n) -> right == nullptr )
   {
      treenode *bye = *n;	
      *n = nullptr;
      delete bye;
   }
   else if( (*n) -> left != nullptr && (*n) -> right == nullptr )
   {
      treenode *bye = *n;
      *n = (*n) -> left;      
      delete bye;
      
   }
   else if( (*n) -> right != nullptr && (*n) -> left == nullptr )
   {
      treenode *bye = *n;
      *n = (*n) -> right;
      delete bye;
      
   }
   else 
   {
      treenode *bye = *n;
      rightinsert( &( (*n) -> left ),  (*n) -> right );
      *n = (*n) -> left;
      delete bye;
   }
   return true;
}

void set::checksorted( ) const
{
   ::checksorted( tr, nullptr, nullptr );
      // :: for the other checksorted which is not in the class. 
}

std::ostream& set::print( size_t indent, std::ostream& out ) const
{
   ::print( out, tr, indent );
   return out;
}


