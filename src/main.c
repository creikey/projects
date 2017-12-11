#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>


#include "prj_parser.h"

void print_help( const char * help_file );

static int verbose_flag;

typedef enum _action {
  check_error,
  parse_file,
  show_help,
  nothing
} action;

int main( int argc, char ** argv ) {
  action todo;
  int c;
  FILE * ep = NULL;
  prj_file * cur_file;
  while( 1 ) {
    static struct option long_options[] =
    {
      {"verbose", no_argument, &verbose_flag, 1},
      {"brief", no_argument, &verbose_flag, 0},
      {"err", required_argument, 0, 'e'},
      {"parse", required_argument, 0, 'p'},
      {"help", no_argument, 0, 'h'},
      {0,0,0,0}
    };
    int option_index = 0;
    c = getopt_long( argc, argv, "vbhe:p:", long_options, &option_index );
    if( c == -1 ) {
      break;
    }
    switch( c ) {
      case 0:
      /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0) {
            break;
          }  bool ex = false;
          printf ("unknown option %s", long_options[option_index].name);
          if (optarg) {
            printf (" with arg %s", optarg);
          }
          printf ("\n");
          break;
      case 'v':
        verbose_flag = 1;
        break;
      case 'b':
        verbose_flag = 0;
      case 'e':
        if( verbose_flag ) {
          printf( "--Checking file %s for errors--\n", optarg );
        }
        //printf( "Option c\n" );
        todo = check_error;
        break;
      case 'p':
        if( verbose_flag ) {
          printf( "--Parsing file %s--\n", optarg );
        }
        //printf( "Option p\n" );
        todo = parse_file;
        break;
      case 'h':
        todo = show_help;
        break;
      default:
        if( verbose_flag ) {
          printf( "ABORTING with case %d\n", c );
        }
        //abort ();
        return -1;
      //return -1;
    }
  }
  if( verbose_flag ) {
    printf( "-- Verbose Mode --\n" );
  }

  if( optind < argc ) {
    printf( "non-option ARGV-elements: " );
    while(optind < argc) {
      printf( "%s ", argv[optind++]);
    }
    putchar( '\n' );
  }
  switch( todo ) {
    case show_help:
      print_help("help.txt");
      break;
    case check_error:
      ep = fopen( optarg, "r" );
      error_check_file( ep, verbose_flag );
    case parse_file:
      cur_file = parse_project_file( optarg );
      printf( "Parsed file %s\n", optarg );
      break;
    case nothing:
      printf("-- Doing nothing --\n__\n__\n__\n" );
      break;
  }
  return 0;
  //exit(0);
  /*if( argc > 1 ) {

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
  }*/

}

void print_help( const char * help_file ) {
  FILE * hp = fopen(help_file, "r");
  if(hp == NULL) {
    printf("ERROR READING HELP FILE\n");
    return;
  }
  while( true ) {
    char * to_print = smart_fgets( hp, BUFFER_SIZE );
    if( to_print == NULL ) {
      break;
    }
    printf( "%s", to_print );
  }
  return;
}
