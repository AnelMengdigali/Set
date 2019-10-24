
#include "set.h"

bool equal( const std::string& s1, const std::string& s2 )
{ 
   if( s1. size() != s2. size() )  return false;
   
   else
   {
      for( size_t i = 0; i < s1. size(); ++ i )
      {
         if( tolower( s1[i] ) != tolower( s2[i] ) )
            return false;
      }
      return true;
   } 
}

size_t hash( const std::string& st )
{
   size_t hash_val = 0;
 
   for( size_t i = 0; i != st. size(); ++ i ) 
   {
      hash_val = ( ( tolower( st[i] ) ) + ( 31 * hash_val ) ); 
   } 
   return hash_val;
}

bool set::contains( const std::string& s ) const
{
   size_t index;
   index = hash(s) % buckets. size();

   for( const auto& el : buckets[ index ] )    
   {
      if( equal( s, el ) )
         return true;
   }
   return false;
}

bool set::simp_insert( const std::string& s )
{
   if( !contains(s) )
   {
      size_t index;
      index = hash(s) % buckets. size(); 
      buckets[ index ]. push_back(s);
      ++ set_size;
      return true;
   }

   return false;
}

bool set::insert( const std::string& s )
{
   if( !simp_insert(s) )  return false;

   else
   {
      double load_factor = loadfactor();

      if( load_factor >= max_load_factor)
         rehash( 2 * buckets. size() );

      return true;
   }
}

void set::rehash( size_t newbucketsize )
{
   if( newbucketsize < 4 )
      newbucketsize = 4;
   
   std::vector< std::list< std::string >> newbuckets = 
      std::vector< std::list< std::string >> ( newbucketsize );
   
   size_t i = 0;
   
   while( i != buckets. size() )
   {
      for( const auto& el : buckets[i] )
      {
         size_t index;
         index = hash( el ) % newbuckets. size();
         
         newbuckets[ index ]. push_back( el );   
      }
      ++ i;
    }  

    buckets = newbuckets;
}

bool set::remove( const std::string& s )
{
   size_t index;
   index = hash(s) % buckets. size();

   for( std::list< std::string > :: const_iterator it = buckets[ index ]. begin(); it != buckets[ index ]. end(); ++ it ) 
   {
      if( equal( s, *it ) ) 
      {
         buckets[ index ]. erase( it );
         -- set_size;
         return true;
      }      
   }

   return false;
}

void set::clear( )
{
   for( size_t i = 0; i != buckets. size(); ++ i )
      buckets[i]. clear();

   set_size = 0;
}

std::ostream& set::print( std::ostream& out ) const
{
   size_t i = 0;
   
   while( i != buckets. size() )
   {
      out << "buckets[ " << i << " ] : { ";
      for( std::list< std::string > :: const_iterator it = buckets[i]. begin(); it != buckets[i]. end(); ++ it )
      {
         if( it != buckets[i]. begin() ) out << ", ";
         out << *it;    
      }
      ++ i; 
      out << " }\n";
    }

    return out;
}

std::ostream& set::printstatistics( std::ostream& out ) const
{
   std::cout << "set size =            " << size( ) << "\n";
   std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
   std::cout << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


