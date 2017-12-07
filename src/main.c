#include <stdio.h>
#include "prj_parser.h"

int main( int argc, char ** argv ) {
  if( argc > 1 ) {
    prj_file * info = parse_project_file( argv[1] );
    printf( "Info size is %lu\n", info->size );
    for( int i = 0; i < info->size; i++ ) {
      printf( "File data for %d: %s\n", i, info->data[i] );
    }
    free_project_file( info );
    return 0;
  } else {
    printf( "YOU MUST INPUT A FILE\n" );
    return -1;
  }
}
