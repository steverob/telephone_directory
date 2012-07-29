#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

#include <iostream.h>
#include <string.h>
//encrypt data


class user_details
{
    public:
        char usr_name[30],login_name[10],password[10],file_name[14];
        int entries;

};

class entry
{
    public:
        char entry_name[30];
        double ph_no;
        int status_flag;//1 - Present ::  0 - Deleted
};

void encrypt (char e[] );


//decrypt data
void decrypt( char * ePtr );
#endif // DEFINITIONS_H_INCLUDED
