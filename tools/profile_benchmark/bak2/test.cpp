#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <errno.h>
#include <string.h>

/* The name of the test file to read. */

static const char * file_name = "trace_2.raw";

/* Size of the block of memory to use for reading. */

#define LENGTH 0x1000

int main ()
{
    gzFile file;
    file = gzopen ("trace_2.raw.gz", "r");
    if (! file) {
        fprintf (stderr, "gzopen of '%s' failed: %s.\n", file_name,
                 strerror (errno));
            exit (EXIT_FAILURE);
    }
    while (1) {
        int err;                    
        int bytes_read;
        unsigned char buffer[LENGTH];
        bytes_read = gzread (file, buffer, LENGTH - 1);
        buffer[bytes_read] = '\0';
        printf ("%s", buffer);
        if (bytes_read < LENGTH - 1) {
            if (gzeof (file)) {
                break;
            }
            else {
                const char * error_string;
                error_string = gzerror (file, & err);
                if (err) {
                    fprintf (stderr, "Error: %s.\n", error_string);
                    exit (EXIT_FAILURE);
                }
            }
        }
    }
    gzclose (file);
    return 0;
}
