
#include <canvas/image32.hpp>

#include <utility/algorithm.hpp>

#include <boost/tuple/tuple_io.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

typedef boost::tuple<std::string,double,double,double> check_point_3;

typedef std::vector<check_point_3> container_type;

int main( int argc, char* argv[] )
{
  std::string check_points_fname( argv[1] );
  std::string dtm_set_fname( argv[2] );

  boost::shared_ptr<container_type> check_points(
    utility::algorithm::load<container_type>( check_points_fname )
  );

  boost::shared_ptr<container_type> dtm_files(
    utility::algorithm::load<container_type>( dtm_set_fname )
  );

  container_type::const_iterator p_it;
  container_type::const_iterator p_end = check_points->end();

  for( std::vector<std::string>::const_iterator it = dtm_files->begin();
    it != dtm_files->end(); ++it ) {

    canvas::image32 dtm( *it );
    dtm.display_info( "\nDTM file: " + *it );

    for( p_it = check_points->begin(); p_it != p_end; ++p_it ) {

      Kernel::Point_2 node( p_it->get<1>(), p_it->get<2>() );

      if( dtm.contains( node ) ) {

        canvas::image32::pixel px( dtm.compute_position( node ) );
        boost::shared_array<double> g( dtm.compute_values( px ) );
        px.get<2>() = g;

        if( dtm.is_valid( px ) ) {

          std::cout << '\t' << p_it->get<0>() << '\t' << node
                    << " | H_REF: " << p_it->get<3>()
                    << " | H_DTM: " << g[0] << std::endl;
        }
      }
    }
  }

  return 0;
}
