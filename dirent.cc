#include "utility.h"

char *dup_str( const char *s ) {
	size_t n = strlen(s) + 1;
	char *t = (char*) malloc(n);
	if (t) {
		memcpy(t, s, n);
	}
	return t;
}
 
char **get_all_files( const char *path ) {
	DIR *dir;
	struct dirent *dp;
	char **files;
	size_t alloc, used;

	if (!(dir = opendir(path))) {
	  goto error;
	}

	used = 0;
	alloc = 10;
	if (!(files = (char**) malloc(alloc * sizeof *files))) {
	  goto error_close;
	}

	while ((dp = readdir(dir))) {
	  if (used + 1 >= alloc) {
      size_t new_thing = alloc / 2 * 3;
      char **tmp = (char**) realloc(files, new_thing * sizeof *files);
      if (!tmp) {
        goto error_free;
      }
      files = tmp;
      alloc = new_thing;
	  }
	  if (!(files[used] = dup_str(dp->d_name))) {
      goto error_free;
	  }
	  ++used;
	}

	files[used] = NULL;

	closedir(dir);
	return files;
 
error_free:
	while (used--) {
		  free(files[used]);
	}
	free(files);
 
error_close:
  closedir(dir);
 
error:
  return NULL;
}
