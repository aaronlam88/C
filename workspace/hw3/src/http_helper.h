/*********************************************************************/
/* Author: Aaron Lam                                                 */
/* Description: create HTTP header to be return to HTTP client       */
/*              currently only support 3 status code: 200, 400, 404  */
/*              max header length is 8KB                             */
/*********************************************************************/

#ifndef HTTP_HELPER_H_
#define HTTP_HELPER_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_http_header (char* header, int status_code, char* filename, int length, int keep_alive);
char* _GET(char* header, char* get);

#endif