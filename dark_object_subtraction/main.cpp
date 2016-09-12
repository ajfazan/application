
#include <canvas/image8.hpp>
#include <canvas/image16.hpp>
#include <canvas/image32.hpp>

#include <utility/utility.hpp>

#include <algorithm>
#include <sstream>

int main( int argc, char* argv[] )
{
  canvas::image::pixel_type type(
    canvas::image::get_pixel_type( argv[1] )
  );

  std::string params( argv[2] );
  std::replace( params.begin(), params.end(), ';', ' ' );
  std::istringstream iss( params );

  switch( type ) {

    case canvas::image::Byte: {

      canvas::image8 input( argv[1] );
      size_t band_count( input.get_channels() );

      std::vector<boost::uint8_t> values;
      values.reserve( band_count );

      do {

        std::string sub;
        iss >> sub;
        values.push_back( utility::from_string<boost::uint8_t>( sub ) );

      } while( iss );

      // values.shrink_to_fit();

      if( values.size() == band_count ) {

        input.allocate();
        input.load();

        canvas::image8::ptr result( input.remove_additive_noise( values ) );

        result->write( argv[4] );
      }

      break;
    }

  }

  return 0;
}
