/*
 * FileReadWrite service interface definition in file FileReadWrite.x
*/

const MAX_LEN = 104857600; /*max file chunk size is 100MB */

struct DATA {
    int length;
    char buffer[MAX_LEN];
    bool moreData;
};


struct READ_ARGS {
    string filename<256>;
    long offset;
};

program FILEREADWRITE {
    version VERSION {
        DATA read(READ_ARGS) = 1;
    } = 1;
} = 0x2070804;