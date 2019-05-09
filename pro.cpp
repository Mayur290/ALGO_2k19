#include<iostream>
#include<bits/stdc++.h>
#include<cstring>
#include<windows.h>
#include<time.h>
#include<conio.h>

using namespace std;
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

const int alphabet_size=128;
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void brick1()
{
    int i;
    for(i=0;i<30;i++)
        printf("\xB2\xB2  ");
}
void brick2()
{
    int i;
    for(i=0;i<30;i++)
        printf("  \xB2\xB2");
}
void patternline1()
{
    int i;
    for(i=0; i<60; i++)
        printf("\xDB\xB2");
}
void patternline2()
{
    int i;
    for(i=0; i<30; i++)
        printf("\xDB\xDB\xB2\xB2");
}
void patternline3()
{
    int i;
    for(i=0; i<60; i++)
        printf("\xB2\xDB");
}
void patternline4()
{
    int i;
    for(i=0; i<30; i++)
        printf("\xB2\xB2\xDB\xDB");
}

struct word
{
    string key;
    string meaning;
};

struct node
{
    struct node *children[alphabet_size];

    bool endofword;
};

// class implementation of dictionary
class dictionary
{
public:
    string s;
    void insert(struct node *,string);
    node *getnode();

    void search(node *,string);
    void fileRead(node *);
    bool deleteWord(struct node *root, string word);
    void alphabeticalOrder(struct node* root, char allWords[], int index);
    void prefix_search(struct node* root, string prefix);
    void print_prefix_search(struct node* root, char allWords[], int index, string prefix);
};

node * dictionary::getnode()
{
    struct node *tnode=new node;
    tnode->endofword=false;

    for(int i=0; i<alphabet_size; i++)
        tnode->children[i]=NULL;

    return tnode;
}

//function for insertion
void dictionary::insert(struct node *root,string m)
{
    struct node *temp=root;
    int index;
    for(int i=0; i<m.length(); i++)
    {

        index=m[i];

        if(temp->children[index]==NULL)
        {
            temp->children[index]=getnode();
        }
        temp=temp->children[index];
    }
    temp->endofword=true;
}

//function for searching
void dictionary::search(struct node * root,string var)
{
    struct node * temp=root;
    int index;
    for(int i=0; i<var.length(); i++)
    {
        index=var[i];
        if(root->children[index]==NULL)
        {
            cout<<"word not found";
            return;
        }
        root=root->children[index];
    }



    string bigstring,str;
    char c[200],a[200];
    int i;


    ifstream myfile2;
    myfile2.open("myfile2.dat");
    while(!myfile2.eof())
    {
        getline(myfile2,bigstring);
        i=bigstring.find(".");
        str=bigstring.substr(0,i);
        //c=str;

        strcpy(c, str.c_str());
        //a=var;
        strcpy(a, var.c_str());
        if(strcmp(a,c)==0)
        {
            cout<<endl<<" | "<<var<<" |"<<" ---> "<<bigstring.substr(i+1)<<endl;
        }


    }

    myfile2.close();


}

//function for deletion
bool dictionary:: deleteWord(struct node *root, string word)
{
    struct node *temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = (word[i]);

        if (!temp->children[index])
            return false;

        temp = temp->children[index];
    }
    string c;
    if (temp != NULL && temp->endofword)
    {
        temp->endofword = false;

        ifstream myfile;
        ifstream myfile2;
        ofstream temp;
        ofstream temp2;

        myfile.open("myfile.dat");
        myfile2.open("myfile2.dat");
        temp.open("temp.dat");
        temp2.open("temp2.dat");

        while(getline(myfile,c))
        {
            if(c!=word)
                temp<<c<<endl;
        }
        int i;
        string bigstring,str;
        char c[2000],a[2000];
        while(!myfile2.eof())
        {
            getline(myfile2,bigstring);
            i=bigstring.find(".");
            str=bigstring.substr(0,i);
            //c=str;

            strcpy(c, str.c_str());
            //a=var;
            strcpy(a, word.c_str());
            if(strcmp(a,c)!=0)
                temp2<<bigstring<<endl;
        }

        myfile.close();
        temp.close();

        remove("myfile.dat");

        rename("temp.dat","myfile.dat");

        myfile2.close();
        temp2.close();

        remove("myfile2.dat");

        rename("temp2.dat","myfile2.dat");
        return true;
    }
}

//function for reading from file
void dictionary:: fileRead(struct node * root)
{
    string data;
    ifstream myfile;

    myfile.open("myfile.dat");
    while(!myfile.eof())
    {
        getline(myfile,data);
        insert(root,data);
    }
    myfile.close();
}

//functiion to print in alphabetical order
void dictionary:: alphabeticalOrder(struct node* root, char allWords[], int index)
{
    struct node* temp = root;

    if(temp != NULL && temp->endofword == true)
    {
        for(int j = 0; j < index; j++)
        {
            cout <<allWords[j];
        }

        cout << " ";
        cout << "\n";
    }

    for(int i = 0; i < alphabet_size; i++)
    {
        if(temp->children[i] != NULL)
        {
            allWords[index] =  i;

            alphabeticalOrder(temp->children[i], allWords, index + 1 );
        }
    }
}

// function to print the results of a given prefix search
void dictionary:: print_prefix_search(struct node* root, char allWords[], int index, string prefix)
{
    struct node* temp = root;

    if(temp != NULL && temp->endofword == true)
    {
        cout << prefix;

        for(int j = 0; j < index; j++)
        {
            cout << allWords[j];
        }

        cout << " ";
        cout << "\n";
    }

    for(int i = 0; i < alphabet_size; i++)
    {
        if(temp->children[i] != NULL)
        {
            allWords[index] =  i;
            print_prefix_search(temp->children[i], allWords, index + 1, prefix);
        }
    }
}

// function to search the words that match the prefix entered
void dictionary::prefix_search(struct node* root, string prefix)
{
    struct node* temp = root;

    for(int i = 0; i < prefix.length(); i++)
    {
        int index = (prefix[i]);
        temp = temp->children[index];
    }

    char allWords[50];
    print_prefix_search(temp, allWords, 0, prefix);
}

void mainmenu1()
{
    dictionary d;
    struct word w;
    string data;
    struct node *root=d.getnode();
    d.fileRead(root);


label:
    system("color f0");
    system("CLS");
    gotoxy(30,7);
    for(int i=0; i<30; i++)
        printf("\xB2\xDB");
    for(int i=0; i<14; i++)
    {
        gotoxy(30,8+i);
        printf("\xDB\xB2\n");
    }
    for(int i=0; i<14; i++)
    {
        gotoxy(88,8+i);
        printf("\xB2\xDB\n");
    }
    gotoxy(32,21);
    for(int i=0; i<28; i++)
        printf("\xB2\xDB");


    int a;
    gotoxy(50,9);
    cout << "What would you like to do? ";
    cout << "\n";
    gotoxy(32,11);
    for(int i=0; i<28; i++)
        printf("\xB2\xDB");
    gotoxy(48,13);
    cout << "1. Insert a word.\n";
    gotoxy(48,14);
    cout << "2. Search a word.\n";
    gotoxy(48,15);
    cout << "3. Delete a word.\n";
    gotoxy(48,16);
    cout << "4. Print entries of dictionary \n";
    gotoxy(48,17);
    cout << "5. Prefix search.\n";
    gotoxy(48,18);
    cout<<"6: Exit"<<endl;
    cout << "\n";

    fflush(stdin);
    string word;
    gotoxy(50,19);
    cout<<"Enter your option: ";
    cin>>a;
    switch(a)
    {
    case 1:
    {
        system("cls");
        system("color F1");
        gotoxy(0,0);
        patternline1();
        gotoxy(0,1);
        patternline3();
        gotoxy(0,2);
        patternline1();
        gotoxy(0,3);
        patternline3();

        gotoxy(0,26);
        patternline1();
        gotoxy(0,27);
        patternline3();
        gotoxy(0,28);
        patternline1();
        gotoxy(0,29);
        patternline3();
        gotoxy(48,6);
        cout<<"Enter the word \t -->"<<endl;
        gotoxy(48,7);
        cin>>w.key;
        gotoxy(48,9);
        cout<<endl<<"Enter the meaning \t -->";
        gotoxy(48,10);
        cin.ignore();
        getline(cin,w.meaning);
        string bigstring;
        bigstring=w.key+"."+w.meaning;

        ofstream myfile2;
        myfile2.open("myfile2.dat",ios::app);
        myfile2<<bigstring;
        myfile2<<endl;
        ofstream  myfile;
        myfile.open("myfile.dat",ios::app);
        myfile<<w.key;
        myfile<<endl;
        d.insert(root,w.key);

        myfile.close();
        myfile2.close();
        gotoxy(46,23);
        cout<<"Press any key to continue!"<<endl;
        gotoxy(46,24);
        cout<<"=========================";
        getch();
        system("CLS");
        goto label;
        break;
    }


    case 2:
    {
         system("cls");
        system("color F4");
        gotoxy(0,1);
    patternline1();
    gotoxy(0,2);
    patternline2();
    gotoxy(0,3);
    patternline3();
    gotoxy(0,4);
    patternline4();
    gotoxy(0,5);
    patternline1();
    gotoxy(0,6);
    patternline2();
        cout<<"\t\t\t\tenter word to be search -->  ";
        cin>>word;
        d.search(root,word);

        cout<<"\t\t\t\tPress any key to continue!"<<endl;

        cout<<"\t\t\t\t=========================";
        getch();
        system("CLS");
        goto label;
        break;
    }

    case 3:
    {
        system("cls");
        system("color F2");
                 for(int j=0;j<2;j++)
    {
       gotoxy(0,2*j);
       brick1();
       gotoxy(0,(2*j)+1);
       brick2();
    }


        cout << "Which word would you like to delete? ";

        cin >> word;
        if(d.deleteWord(root, word))
        {
            cout << word << " has been successfully deleted from the Dictionary.\n";
        }

        else
        {
            cout << "No such word exists in the Dictionary.\n";
        }

        cout<<"\t\t\t\tPress any key to continue!"<<endl;

        cout<<"\t\t\t\t=========================";
        getch();
        system("CLS");
        goto label;
        break;
    }


    case 4:
    {
        system("cls");
        system("color F4");
        char allWords[50];
        d.alphabeticalOrder(root, allWords, 0);
        cout << "\n";

        cout<<"\t\t\t\tPress any key to continue!"<<endl;

        cout<<"\t\t\t\t=========================";
        getch();
        system("CLS");
        goto label;

        break;
    }

    case 5:
    {
        system("cls");
        system("color F2");
         gotoxy(0,1);
    patternline1();
    gotoxy(0,2);
    patternline2();
    gotoxy(0,3);
    patternline3();
    gotoxy(0,4);
    patternline4();
    gotoxy(0,5);
    patternline1();
    gotoxy(0,6);
    patternline2();
        cout << "\n\tEnter the word you would like to use as a prefix: ";
        cin >> word;
        cout << "\n";

        d.prefix_search(root, word);
         cout<<"\t\t\t\tPress any key to continue!"<<endl;

        cout<<"\t\t\t\t=========================";
        getch();
        system("CLS");
        goto label;
        break;
    }


    case 6:
                   {
                      system("cls");
                      system("color 0F");
                      gotoxy(20,8);
                      for(int i=0;i<54;i++)
                       {    delay(15);
                            printf("\xB2");
                       }
                      gotoxy(20,10);
                      printf("\xB2\xB2        Thanks for using the Program..            \xB2\xB2");
                      gotoxy(20,12);
                      for(int i=0;i<54;i++)
                       {     delay(15);
                             printf("\xB2");
                       }
                      gotoxy(30,16);
                      printf("Exiting...........>");

                      exit(0);
                   }
        default:
                   {gotoxy(24,24);
                    printf("\aWrong Entry!!Please re-entered correct option\n");
                    cout<<"\t\t\t\tPress any key to continue!"<<endl;

        cout<<"\t\t\t\t=========================";
        getch();
        system("CLS");
        goto label;
                   }
    }



}



void start()
{int i,j;
system("color E0");
 for(j=0;j<3;j++)
    {
       gotoxy(0,2*j);
       brick1();
       gotoxy(0,(2*j)+1);
       brick2();
    }
     for(j=13;j<16;j++)
    {
       gotoxy(0,2*j);
       brick1();
       gotoxy(0,(2*j)+1);
       brick2();
    }
     gotoxy(4,8);
    for(i=0;i<40;i++)
        printf("\xDB");
        printf("   TRIE ALGO APPLICATION   ");
    for(i=0;i<40;i++)
        printf("\xDB");
        gotoxy(55,10);
        printf("BATCH-B7");
        gotoxy(55,12);
        printf("MADE BY");
        gotoxy(0,14);
        patternline4();
        gotoxy(35,16);printf("VAIDYANATH SINGH");
        gotoxy(65,16);printf("(17103284)");

         gotoxy(35,18);printf("MAYUR BANSAL");
        gotoxy(65,18);printf("(17103291)");

         gotoxy(35,20);printf("AMAN PATEL");
        gotoxy(65,20);printf("(17103264)");

         gotoxy(35,22);printf("BHARAT PANJWANI");
        gotoxy(65,22);printf("(17103288)");
        getch();
         mainmenu1();



}

int main()
{
   start();
   return 0;
 }
// the driver function of the program
