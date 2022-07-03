#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define READ 0
#define WRITE 1
int main ( )
{
char* phrase = "This is OS lab time" ;
int fd [2], bytesread ;
char message [100] ;
pipe ( fd ) ;
if ( fork ( ) == 0 ) /* child, writer */
{
close ( fd [READ] ) ; /* close unused end */
write ( fd [WRITE], phrase, strlen (phrase) + 1) ;
close ( fd [WRITE] ) ; /* close used end */
}
else /* parent, reader */
{
close ( fd [WRITE] ) ; /* close unused end */
bytesread = read (fd [READ], message, 100) ;
printf ("Read %d bytes : %s\n", bytesread, message) ;
close ( fd [READ] ) ; /* close used end */
}
}
