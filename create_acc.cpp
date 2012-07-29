//Returns 1 on Unsucceefull Execution
//Returns 0 on Succeefull Execution
//Used to Create an account for an User and appends that to user_list.dat file
//Copyright(2010) - Steve Robinson


#include <iostream>
#include "definitions.h"
#include <conio.h>
#include <iomanip>
using namespace std;

void encrypt (char e[] )
{
for( int i=0; e[i] != '\0'; ++i ) ++e[i];
} // encrypt

//decrypt data
void decrypt( char * ePtr ) {
for( ; * ePtr != '\0'; ++ ePtr ) --(* ePtr);
}

int create_user()
{
    system("cls");
    cout<<"\n----------------------------------------------\n"<<"Please Enter the Details for the New User..."<<"\n----------------------------------------------\n";
    cout<<endl<<endl;
    user_details tmpuser;
    cout<<"\n\nUser Name: ";
    fflush(stdin);
    gets(tmpuser.usr_name);
    fflush(stdin);
    cout<<"\n\nLogin Name: ";
    cin>>tmpuser.login_name;

    //Masking Code for Password

    int ch;
    char pword1[10],pword2[10];
    int i;
    getpass:
    cout<<"\n\nEnter Password (0 to 8 Characters): ";

    i=0;
    while((ch=getch())!=EOF&&ch!='\n'&&ch!='\r'&&i<10)
    {
        if(ch=='\b')
        {
            cout<<'\b';
            i--;
        }
        else
        {
            pword1[i++]=ch;
            cout<<'*';
        }
    }
    pword1[i]='\0';
    fflush (stdin);
    cout<<"\nRe-Enter Password: ";

    i=0;
    while((ch=getch())!=EOF&&ch!='\n'&&ch!='\r'&&i<10)
    {
        if(ch=='\b')
        {
            cout<<'\b';
            i--;
        }
        else
        {
            pword2[i++]=ch;
            cout<<'*';
        }
    }
    pword2[i]='\0';

    if(strcmp(pword1,pword2)!=0)
    {
        cout<<"\n\nEntered Passwords donot Match!\n\n";
        goto getpass;
    }

    //encryption and storing in object
    encrypt(pword1);
    strcpy(tmpuser.password,pword1);
    int len;
    len=strlen(tmpuser.login_name);
    strcpy(tmpuser.file_name,tmpuser.login_name);
    strcat(tmpuser.file_name,".dat");
    tmpuser.entries=0;

    cout<<"\n\n----------------------------------------------\nNew User Account Successfully Created!\n----------------------------------------------\n";

    cout<<endl<<endl;


    ofstream fwrite("user_list.dat",ios::app|ios::binary);
    if(fwrite.is_open())
    {
        fwrite.write((char *)&tmpuser,sizeof(tmpuser));
        if(fwrite.fail())
        {
            cout<<"\n\nError: Unable to write to Disk File!";
            fwrite.close();
            getch();
            return 1;
        }
        else
            fwrite.close();
    }
    else
    {
        ofstream fwrite("user_list.dat",ios::out|ios::binary|ios::trunc);
        if(fwrite.is_open())
        {
        fwrite.write((char *)&tmpuser,sizeof(tmpuser));
            if(fwrite.fail())
            {
                cout<<"\n\nError: Unable to write to disk file!\n\n";
                fwrite.close();
                getch();
                return 1;
            }
            else
            {
                fwrite.close();
            }
        }
    }

    cout<<"\nReturning to root.";
    getch();
    return 0;
}

