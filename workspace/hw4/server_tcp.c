#include "FileReadWrite.h"

DATA *
read_1_svc(READ_ARGS *argp, struct svc_req *rqstp)
{
	static DATA  result;

    FILE* fp = fopen(argp->filename, "r");
    fseek(fp, argp->offset, SEEK_SET);

    result.length = fread(result.buffer, 1, sizeof(result.buffer), fp);

    if(feof(fp)) {
        result.moreData = 0;
    } else {
        result.moreData = 1;
    }

	return &result;
}
