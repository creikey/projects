#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

#include "prj_parser.h"

const char * categories[] = { "dir", "exec", "description" };

/* An example project file --
 *
 * dir
 * /home/creikey/Documents/example/
 * exec
 * /home/creikey/Documents/example/exec
 * description
 * A small example program
*/

int check_prj_struct( prj_file * file ) {
  for( size_t i = 0; i < file->size; i+=2 ) {
    for( int ii = 0; i < sizeof(categories); ii++ ) {
      if( strcmp(file->data[i], categories[ii]) != 0 ) {
        printf( "Category not found: %s\n", file->data[i] );
        return -1;
      }
    }
  }
  printf( "Valid file\n" );
  return 0;
}

int get_numb_lines( FILE * to_read ) {
  int counter=0;
  while( smart_fgets( to_read, BUFFER_SIZE ) != NULL ) {
    counter += 1;
  }
  fseek( to_read, 0, SEEK_SET );
  return counter;
}

void error_check_file( FILE * to_check, bool verbose ) {
  if( verbose ) {
    printf( "Error checking file...\n" );
  }
  if( to_check == NULL ) {
    printf( "FATAL: Input file was null line %d function %s\n", __LINE__, __func__ );
  }
}

char * smart_fgets( FILE * to_read, size_t buffer_size ) {
  int cur_buff_size = 1;
  int cur = 0;
  char * to_return = malloc( cur_buff_size*buffer_size*sizeof(char) );
  while( true ) {
    char read = fgetc( to_read );
    /*if( read == '\n' || read == EOF ) {
      break;
    }*/
    if( cur > (buffer_size*cur_buff_size)-3 ) {
      size_t tmp_size = cur_buff_size*buffer_size*sizeof(char);
      char * tmp = malloc( tmp_size );
      memcpy( tmp, to_return, tmp_size );
      cur_buff_size += 1;
      free(to_return);
      to_return = malloc( cur_buff_size*buffer_size*sizeof(char) );
      memcpy( to_return, tmp, tmp_size );
      free(tmp);
    }
    to_return[cur] = read;
    if( read == '\n' || read == EOF ) {
      break;
    }
    cur += 1;
  }
  if( to_return[0] == EOF ) {
    free(to_return);
    return NULL;
  }
  to_return[cur+1] = '\0';
  return to_return;
}

// Returns an array of files, evens are the labels and odds are the data
prj_file * parse_project_file( const char * file_name ) {
  prj_file * to_return = malloc( sizeof *to_return );
  FILE * fp = fopen( file_name, "r" );
  if( fp == NULL ) {
    printf( "ERROR: FILE WAS NULL\n" );
    return NULL;
  }
  int lines = get_numb_lines(fp);
  printf( "Lines: %d\n", lines );
  char ** to_data = malloc( lines * sizeof(char*) );
  int i;
  for( i=0; i < lines; i++ ) {
    char * to_add = smart_fgets( fp, BUFFER_SIZE );
    //printf( "To add is %s\n", to_add );
    to_data[i] = to_add;
    //printf( "to_return for %d is: %s\n", i, to_return[i] );
  }
  to_return->size = i;
  to_return->data = to_data;
  fclose( fp );
  return to_return;
}

void free_project_file( prj_file * in_project_file ) {
  for( int i=0; i < in_project_file->size; i++ ) {
    free(in_project_file->data[i]);
  }
  free( in_project_file );
  return;
}
