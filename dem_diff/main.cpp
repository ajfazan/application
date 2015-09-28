
#include <canvas/image32.hpp>

#include <utility/algorithm.hpp>

#include <boost/filesystem.hpp>
#include <boost/utility.hpp>

#include <string>

typedef std::vector<std::string> container_type;

typedef std::pair<std::string,std::string> dem_pair;

bool is_equal( const dem_pair& p1, const dem_pair& p2 )
{
  std::string f1[] = {
    boost::filesystem::path( p1.first  ).filename().string(),
    boost::filesystem::path( p1.second ).filename().string()
  };

  std::string f2[] = {
    boost::filesystem::path( p2.first  ).filename().string(),
    boost::filesystem::path( p2.second ).filename().string()
  };

  return ( ( ( f1[0] == f2[0] ) && ( f1[1] == f2[1] ) ) ||
           ( ( f1[0] == f2[1] ) && ( f1[1] == f2[0] ) ) );

}

int main( int argc, char* argv[] )
{
  std::string dem_set_fname( argv[1] );

  boost::shared_ptr<container_type> dem_set(
    utility::algorithm::load<container_type>( dem_set_fname )
  );

  container_type::const_iterator it1;
  container_type::const_iterator it2;
  container_type::const_iterator end = dem_set->end();

  std::list<dem_pair> pairs;

  for( it1 = dem_set->begin(); it1 != end; ++it1 ) {

    canvas::image32 base( *it1 );

    for( it2 = boost::next( it1 ); it2 != dem_set->end(); ++it2 ) {

      if( base.intersects( canvas::image32( *it2 ) ) ) {

        pairs.push_back( std::make_pair( *it1, *it2 ) );
      }
    }
  }

  std::cout << pairs.size() << std::endl;
  pairs.sort();
  pairs.unique( is_equal );
  std::cout << pairs.size() << std::endl;

  std::list<dem_pair>::const_iterator p_it;
  std::list<dem_pair>::const_iterator p_end = pairs.end();

  for( p_it = pairs.begin(); p_it != p_end; ++p_it ) {

    canvas::image32 dem1( p_it->first  );
    canvas::image32 dem2( p_it->second );

    canvas::image32::ptr diff( dem1.compute_difference( dem2 ) );

    canvas::image32::stats s( diff->compute_stats() );
  }

  return 0;
}
