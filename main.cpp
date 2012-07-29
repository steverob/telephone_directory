
#include <iostream>
#include "definitions.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <conio.h>
#include "create_acc.cpp"
using namespace std;

int user_no=0;

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
            getch();
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
                getch();
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
            getch();
            return 1;
          }

    }
    return 0;
}

int delete_entry(user_details & current_user)
{
    system("cls");
    entry temp_entry;
    char tmp_name[30];
    int flag;
    getentry:
    flag=0;
    system("cls");
    //strcpy(tmp_name,"XXXXXXXXXX");
    cout<<"\n----------------------------------------------------\n"<<"Please Enter the Name of the entry to be deleted..."<<"\n----------------------------------------------------\n";

    cout<<"\nName: ";
    fflush(stdin);
    gets(tmp_name);

    fstream fread(current_user.file_name,ios::in|ios::out|ios::binary);
    if(!fread.is_open())
    {
        cout<<"\nError: unable to access File!\n";
        getch();
        return 1;
    }

    while(fread.read((char *) &temp_entry, sizeof(temp_entry)))
    {
        if(strcmp(temp_entry.entry_name,tmp_name)==0&&temp_entry.status_flag==1)
        {
                flag =1;
                //cout<<fread.tellg();
                break;
        }
    }
    if(flag==0)
    {
        cout<<"\n\nError: Entry not found\n\n";
        cout<<"Try again? <yes = 1 || no = 0>....";
        if(getch())
        {
            fread.close();
            goto getentry;
        }
        else
            return 2;
    }
    cout<<"\n\nEntry Found. Deleting.....\n\n";
    temp_entry.status_flag=0;
  //  int position = fread.tellg();
  //  fread.close();

   // ofstream fwrite(current_user.file_name,ios::ate|ios::binary);
   // fwrite.seekp(position,ios::beg);
    //cout<<fread.tellg();
    fread.write((char*)&temp_entry,sizeof(temp_entry));
    fread.close();
    getch();
    return 0;
}

int search(user_details &current_user)
{
    system("cls");
    int ch,flag;
    char temp_name[30];
    double temp_no;
    entry temp_entry;
    search_menu:
    system("cls");

    cout<<"\n---------------------------------------\n"<<"SEARCH CONSOLE"<<"\n---------------------------------------\n";
    cout<<"\n\nMenu:\n1 -> Search by Name\n2 -> Search by Number\n3 -> Exit Search Console\nEnter Choice....";
    strcpy(temp_name,"XXXXXXXXXX");
    flag=0;
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
                    getch();
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
                    getch();
                    goto search_menu;
                }
                else
                {
                    system("cls");
                    cout<<"\n\nEntry Found!\n\nDetails: \nName: "<<temp_entry.entry_name<<"\nPhone Number: "<<temp_entry.ph_no<<endl;
                    cout<<"\nPress any key to return to search console...\n";
                    getch();
                }
                fread.close();
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
                    getch();
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
                    getch();
                }
                else
                {
                    system("cls");
                    cout<<"\n\nEntry Found!\n\nDetails: \nName: "<<temp_entry.entry_name<<"\nPhone Number: "<<temp_entry.ph_no<<endl;
                    cout<<"\nPress any key to return to search console...\n";
                    getch();
                }
            fread.close();
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
            goto search_menu;

    }
    goto search_menu;
}

void display(user_details &current_user)
{
    system("cls");
    cout<<"\n\n----------------------------------------------------\nTelephone Directory of "<<current_user.usr_name<<"\n----------------------------------------------------\n";
    ifstream fread(current_user.file_name,ios::in|ios::binary);
    entry online_list[100],tmp;
    //online_list=new entry[current_user.entries];
    int i=0;
    char temp[30];
    while(fread.read((char *)&tmp,sizeof(tmp)))
    {
        if(tmp.status_flag==1)
            online_list[i++]=tmp;
    }
    fread.close();

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
    cout.width(7);
    cout<<"Sn. No";
    cout.width(15);
    cout<<"Name";
    cout.width(15);
    cout.setf(ios::fixed);
    cout.precision(0);
    cout<<"Phone Number";
    cout<<"\n--------------------------------------------------\n";
    for(i=0;i<current_user.entries;i++)
    {
            cout<<endl;
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
    system("cls");
    cout<<"\n\nPlease Choose what you want to do.....\n\n1 -> Add Entry\n2 -> Delete Entry\n3 -> Search\n4 -> Display All\n5 -> User Information\n6 -> Logout\n\nEnter you choice.....";
    cin>>ch;
    switch(ch)
    {
        case 1:
                if(add_entry(current_user))
                {
                    cout<<"\n\n Add Entry operation Failed!!\n\n";
                    getch();
                }
                else
                {
                    ofstream fwrite("user_list.dat",ios::ate|ios::binary);
                    fwrite.seekp(position,ios::beg);
                    cout<<"XXX: "<<position;
                    getch();
                    current_user.entries++;
                    fwrite.write((char*)&current_user,sizeof(current_user));
                    fwrite.close();
                }
                break;
        case 2:
                int return_val;
                return_val=delete_entry(current_user);
                if(return_val==1)
                {
                    cout<<"\n\n Error:Delete Entry operation Failed due to File access error\n\n";
                    getch();
                    return 1;
                }
                else if(return_val==2)
                {
                    cout<<"\n\nDelete operation Cancelled by User. Returning to User root..";
                    getch();
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
                    getch();
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
                getch();
                goto menu;
    }
    goto menu;
}










int login()
{
    system("cls");
    int flag=0,cho=1;
    char tmp_login[10];
    user_details tempuser;
    char tmp_password[BUFSIZ];
    getlogin:
    system("cls");
    cout<<"\n----------------------------------------------\n"<<setw(23)<<"Login Name: ";
    cin>>tmp_login;
    ifstream fread("user_list.dat",ios::in|ios::binary);
    if(!fread.is_open())
    {
        cout<<"\nError: unable to access File!\n";
        getch();
        return 1;
    }

    while(fread.read((char *) &tempuser, sizeof(tempuser)))
    {
        if(strcmp(tempuser.login_name,tmp_login)==0)
        {
                flag =1;
                break;
        }
    }
    if(flag==0)
    {
        cout<<"\n\nError: Invalid Login Name!\n\n";
        cout<<"Try again? <yes = 1 || no = 0>";
        cin>>cho;
        if(cho==1)
            goto getlogin;
        else
            return 1;
    }
    cout<<setw(23)<<"Password: ";

    //Masking Code for Password

    int ch;
    int i=0;
    while((ch=getch())!=EOF&&ch!='\n'&&ch!='\r'&&i<10)
    {
        if(ch=='\b')
        {
            cout<<'\b';
            i--;
        }
        else
        {
            tmp_password[i++]=ch;
            cout<<'*';
        }
    }
    tmp_password[i]='\0';

    encrypt(tmp_password);

    if(strcmp(tmp_password,tempuser.password)!=0)
    {
        cout<<"\n\nError: Invalid Password!\n\n";
        cout<<"Try again? <yes = 1 || no = 0>";
        cin>>cho;
        if(cho==1)
            goto getlogin;
        else
            return 1;
    }
    cout<<"\n----------------------------------------------\n";

    cout<<setw(23)<<"\n\nLogin Successfull! <press any key to continue>";
    int position=fread.tellg();
    position-=sizeof(user_details);
    fread.close();
    getch();
    sec_main(tempuser,position);
    return 0;
}



















int main()
{
int ch;
 //int user_no=0;
//user_details tmp;
 menu:
    /*ifstream fread("user_list.dat",ios::in|ios::binary);
    user_no=0;

    while(fread.read((char *)&tmp,sizeof(tmp)))
        user_no++;
    fread.close();*/

 system("cls");
 cout<<"    ______________________________________________________________\n";
 cout<<"    |                   Personal Phone Book                       |\n";
 cout<<"    |                       Version 1.0                           |\n";
 cout<<"    |                   PIT CSE Software Co.                      |\n";
 cout<<"    |_____________________________________________________________|\n";
 cout<<endl<<endl<<endl;
 cout<<"\nTotal Number of Users: "<<user_no;
 cout<<endl<<endl;
 cout<<"                        MAIN MENU\n";
 cout<<"______________________________________________________________\n";
 cout<<"                        1 -> Login\n";
 cout<<"                        2 -> Create New User\n";
 cout<<"                        3 -> About\n";
 cout<<"                        4 -> Exit to Windows\n";
 cout<<"______________________________________________________________\n";
cout<<"\n\nEnter Choice.......";
 cin>>ch;

 switch(ch)
 {
    case 1:
            if(user_no!=0)
                login();
            else
            {
                cout<<"\n\nError: There are currently no users Created.\nPlease Create a new user from \"Create New User\" Menu.\n\n";
                getch();
            }
            break;
    case 2:
            if(create_user())
              cout<<"\n\nError: User Creation Failed. Please Check Disk Files.";
            else
                user_no++;
            break;
    case 3:
             system("cls");
             cout<<"______________________________________________________________\n";
             cout<<"|                   Personal Phone Book                       |\n";
             cout<<"|                       Version 1.0                           |\n";
             cout<<"|                    XXXXXXXXXXXXXXXXXX                       |\n";
             cout<<"|_____________________________________________________________|\n";
             cout<<endl<<endl;
             cout<<"Description.......\n";
             cout<<"______________________________________________________________\n";
             cout<<"Personal Phone Book is a full-featured console\n";
             cout<<"that allows users to store and manage thei telephone\n";
             cout<<"numbers in a secure and user-friendly manner. This program\n";
             cout<<"allows multiple users to manage their phone book with password \n";
             cout<<"protection support.\n\n";

             cout<<"Information.......\n";
             cout<<"______________________________________________________________\n";
             cout<<"Name: Personal Phone Book\nVersion: 1.0\nAuthors: Steve Robinson, N.S. Vishnu, V. Vignesh (PIT CSE Dept.) \n";
             cout<<"Language: C++\nLicense: free (Closed Source)\nEmail: steve_robinson@live.com\n\n";
             getch();
             break;

    case 4:
            cout<<"\n\nThanks for using!\nExiting to Windows.......";
            getch();
            return 0;
    default:
            cout<<"\n\nError: Invalid Menu Choice!";
            getch();
 }
 goto menu;
}






