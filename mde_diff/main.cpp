
#include <utility/algorithm.hpp>

#include <boost/filesystem.hpp>

#include <string>

typedef std::vector<string> container_type;

int main( int argc, char* argv[] )
{
  std::string dem_set_fname( argv[1] );

  boost::shared_ptr<container_type> dem_set(
    utility::algorithm::load<container_type>( dem_set_fname )
  );

  return 0;
}
