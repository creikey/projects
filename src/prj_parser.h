#ifndef H_PRJ_PARSER
#define H_PRJ_PARSER

typedef struct _prj_file {
  char ** data;
  size_t size;
} prj_file;

int get_numb_lines( FILE * to_read );

char * smart_fgets( FILE * to_read, size_t buffer_size );

prj_file * parse_project_file( const char * file_name );

void free_project_file( prj_file * in_project_file );

#endif
