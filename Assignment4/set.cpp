
#include "set.h"

//Function bodies:

bool set::equal( const std::string& s1, const std::string& s2 )
{
   if( s1. size() != s2. size() ) 
      return false;

   for( size_t i = 0; i != s1. size(); ++ i )
   {
      if( tolower( s1[i] ) == tolower( s2[i] ) ) 
         continue;
      
      return false;	   
    }

return true;
} 

bool set::contains( const std::string& el ) const
{   
   for( set::const_iterator p = data. begin(); p != data. end(); ++ p )
   {
      if( equal( *p, el ) ) 
         return true;
   }	
 
   return false;
}
    
bool set::insert( const std::string& el )
{
   if( contains( el ) ) 
      return false;
  
   else 
   {
      data. push_back( el );

      return true;
   }
}

size_t set::insert( const set& s )
{
   int count = 0;

   for( set::const_iterator p = s. begin(); p != s. end(); ++ p )
   {	
      if( insert( *p ) )
         ++ count;
   }

   return count;	
}

bool set::remove( const std::string& el )
{
   for( size_t i = 0; i != data. size(); ++ i ) 
   {   
      if( equal( data[i], el ) ) 
      {
         std::swap ( data[i], data. back() );
         
         data. pop_back();
	
         return true;
      }
   }

   return false;
}

size_t set::remove( const set& s )
{
   int count = 0;

   for( set::const_iterator p = s. begin(); p != s. end(); ++ p )
   {	
      if( remove( *p ) )
         ++ count;
   }
   return count;
}

std::ostream& operator << ( std::ostream& out, const set& s )
{ 
  out << "{ ";

   for( set::const_iterator p = s. begin(); p != s. end( ); ++ p )
   {
      if( p != s. begin() ) out << ", ";
      out << *p; 
   }

   out << " }";

   return out;
}

bool subset( const set& s1, const set& s2 )
{
    for( set::const_iterator p = s1. begin(); p != s1. end(); ++p )
    {	
       if( s2. contains( *p ) )
          continue;
 
       return false;
    }

return true;
}


  

