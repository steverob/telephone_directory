#include <iostream>
#include "definitions.h"
#include <iomanip>
#include <fstream>
#include <conio.h>
using namespace std;

int add_entry (user_details &current_user)
{
    system("cls");
    entry temp_entry;

    cout<<"\n----------------------------------------------\n"<<"Please Enter the Details for the New Entry..."<<"\n----------------------------------------------\n";
    cout<<"\n\nName: ";
    fflush(stdin);
    gets(temp_entry.entry_name);
    fflush(stdin);
    cout<<"\n\nPhone Number: ";
    cin>>temp_entry.ph_no;
    temp_entry.status_flag=1;

    ofstream fwrite(current_user.file_name,ios::app|ios::binary);
    if(fwrite.is_open())
    {
        fwrite.write((char *)&temp_entry,sizeof(temp_entry));

        if(fwrite.fail())
        {
            cout<<"\n\nError: Unable to write to disk file!\n\n";
            fwrite.close();
            return 1;
        }
        else
        {
            fwrite.close();
        }
    }

    else
    {
          ofstream fwrite(current_user.file_name,ios::out|ios::binary|ios::trunc);
          if(fwrite.is_open())
          {

            fwrite.write((char *)&temp_entry,sizeof(temp_entry));

            if(fwrite.fail())
            {
                cout<<"\n\nError: Unable to write to disk file!\n\n";
                fwrite.close();
                return 1;
            }
             else
            {
                fwrite.close();
            }

          }
          else
          {
            cout<<"\n\nError: Unable to Open file!\n\n";
            return 1;
          }

    }
    return 0;
}

int delete_entry(user_details & current_user)
{
    system("cls");
    entry temp_entry;
    char *tmp_name;
    int flag=0;
    getentry:
    system("cls");
    cout<<"\n----------------------------------------------------\n"<<"Please Enter the Name of the entry to be deleted..."<<"\n----------------------------------------------------\n";
    cin>>tmp_name;

    ifstream fread(current_user.file_name,ios::in|ios::binary);
    if(!fread.is_open())
    {
        cout<<"\nError: unable to access File!\n";
        return 1;
    }

    while(fread.read((char *) &temp_entry, sizeof(temp_entry)))
    {
        if(strcmp(temp_entry.entry_name,tmp_name)==0&&temp_entry.status_flag==1)
        {
                flag =1;
                break;
        }
    }
    if(flag==0)
    {
        cout<<"\n\nError: Entry not found\n\n";
        goto getentry;
    }
    temp_entry.status_flag=0;
    int position = fread.tellg();
    fread.close();

    ofstream fwrite(current_user.file_name,ios::out|ios::binary);
    fwrite.seekp(position,ios::beg);
    fwrite.write((char*)&temp_entry,sizeof(temp_entry));
    fwrite.close();
    return 0;
}

int search(user_details &current_user)
{
    system("cls");
    int ch,flag=0;
    char *temp_name;
    double temp_no;
    entry temp_entry;
    search_menu:
    system("cls");

    cout<<"\n---------------------------------------\n"<<"SEARCH CONSOLE"<<"\n---------------------------------------\n";
    cout<<"\n\nMenu:\n1 -> Search by Name\n2 -> Search by Number\n3 -> Exit Search Console\nEnter Choice....";
    cin>>ch;

    switch(ch)
    {
        case 1:
            {
                cout<<"\n\nEnter the Name of the Entry to be searched for....";
                fflush(stdin);
                gets(temp_name);
                ifstream fread(current_user.file_name,ios::in|ios::binary);
                if(!fread.is_open())
                {
                    cout<<"\nError: unable to access File!\n";
                    return 1;
                }

                while(fread.read((char *) &temp_entry, sizeof(temp_entry)))
                {
                    if(strcmp(temp_entry.entry_name,temp_name)==0&&temp_entry.status_flag==1)
                    {
                            flag =1;
                            break;
                    }
                }
                if(flag==0)
                {
                    cout<<"\n\nError: Entry not found\n\n";
                    goto search_menu;
                }
                else
                {
                    cout<<"\n\nEntry Found!\n\nDetails: \nName: "<<temp_entry.entry_name<<"\nPhone Number: "<<temp_entry.ph_no<<endl;
                }
            }
            break;

        case 2:
            {
                cout<<"\n\nEnter the Phone Number of the Entry to be searched for....";
                cin>>temp_no;
                ifstream fread(current_user.file_name,ios::in|ios::binary);
                if(!fread.is_open())
                {
                    cout<<"\nError: unable to access File!\n";
                    return 1;
                }

                while(fread.read((char *) &temp_entry, sizeof(temp_entry)))
                {
                    if(temp_entry.ph_no==temp_no&&temp_entry.status_flag==1)
                    {
                            flag =1;
                            break;
                    }
                }
                if(flag==0)
                {
                    cout<<"\n\nError: Entry not found\n\n";
                }
                else
                {
                    cout<<"\n\nEntry Found!\n\nDetails: \nName: "<<temp_entry.entry_name<<"\nPhone Number: "<<temp_entry.ph_no<<endl;
                }
            }
            break;
        case 3:
            {
                cout<<"\n\nExiting Search Console. Returning to user Root Menu\n\n";
                getch();
                return 0;
            }

        default:
            cout<<"\n\nError: Menu Item not found! Please enter proper Choice.\n\n";

    }
    goto search_menu;
}

void display(user_details &current_user)
{
    system("cls");
    cout<<"\n\n----------------------------------------------------\nTelephone Directory of "<<current_user.usr_name<<"\n----------------------------------------------------\n";
    ifstream fread(current_user.file_name,ios::in|ios::binary);
    entry *online_list,tmp;
    online_list=new entry[current_user.entries];
    int i=0;
    char *temp;
    while(fread.read((char *)&tmp,sizeof(tmp))&&tmp.status_flag==1)
        online_list[i++]=tmp;

    for(i=0;i<current_user.entries-1;i++)
        for(int j=i;j<current_user.entries;j++)
        {
            if(stricmp(online_list[i].entry_name,online_list[j].entry_name)>0)
            {
               strcpy(temp,online_list[i].entry_name);
               strcpy(online_list[i].entry_name,online_list[j].entry_name);
               strcpy(online_list[j].entry_name,temp);
            }
        }
    cout<<endl<<endl;
    cout<<"\n--------------------------------------------------\n";
    cout.setf(ios::left);
    cout.width(6);
    cout<<"Sn. No";
    cout.width(15);
    cout<<"Name";
    cout.width(15);
    cout<<"Phone Number";
    cout<<"\n--------------------------------------------------\n";
    for(i=0;i<current_user.entries;i++)
    {
            cout.width(6);
            cout<<i+1;
            cout.width(15);
            cout<<online_list[i].entry_name;
            cout.width(15);
            cout<<online_list[i].ph_no;
    }
    cout<<"\n--------------------------------------------------\n";

    cout<<endl<<endl<<"Return to User Root?? <press any key>";
    getch();
 //   return 0;
}

void user_info(user_details &current_user)
{
    system("cls");
    cout<<"\n\nUser Details:\n";
    cout<<"\nUser Name: "<<current_user.usr_name;
    cout<<"\nLogin Name: "<<current_user.login_name;
    cout<<"\nPassword: "<<"**********";
    cout<<"\nUser File Name:"<<current_user.file_name;
    cout<<"\nNumber of Directory Entries: "<<current_user.entries;
    cout<<"\n\n\nReturn to User Root? <press any key>";
    getch();
}




int sec_main(user_details &current_user,int position)
{
    system("cls");
    int ch;

    cout<<"\n---------------------------------------------------\nWelcome "<<current_user.usr_name<<" to your Personal Phone Directory\n---------------------------------------------------\n";
    cout<<endl<<endl;
    menu:
    cout<<"Please Choose what you want to do.....\n\n1 -> Add Entry\n2 -> Delete Entry\n3 -> Search\n4 -> Display All\n5 -> User Information\n6 -> Logout\n\nEnter you choice.....";
    cin>>ch;
    switch(ch)
    {
        case 1:
                if(add_entry(current_user))
                {
                    cout<<"\n\n Add Entry operation Failed!!\n\n";
                }
                else
                {
                    ofstream fwrite("user_list.dat",ios::out|ios::binary);
                    fwrite.seekp(position,ios::beg);
                    current_user.entries++;
                    fwrite.write((char*)&current_user,sizeof(current_user));
                    fwrite.close();
                }
                break;
        case 2:
                if(delete_entry(current_user))
                {
                    cout<<"\n\n Error:Delete Entry operation Failed due to File access error\n\n";
                    return 1;
                }
                else
                {
                    ofstream fwrite("user_list.dat",ios::out|ios::binary);
                    fwrite.seekp(position,ios::beg);
                    current_user.entries--;
                    fwrite.write((char*)&current_user,sizeof(current_user));
                    fwrite.close();
                }
                break;
        case 3:
                if(search(current_user))
                {
                    cout<<"\n\nError: Search operation Failed due to File access Error\n\n";
                    return 1;
                }
                break;
        case 4:
                display(current_user);
                break;
        case 5:
                user_info(current_user);
                break;
        case 6:
                cout<<"\n\n\n---------------------------------------------------\n::::Thank You::::Logging you Out::::\n---------------------------------------------------\n";
                return 0;
        default:
                cout<<"\n\nError: Menu Item not found. Please Enter Proper Choice!\n\n";
                goto menu;
    }
    goto menu;
}
