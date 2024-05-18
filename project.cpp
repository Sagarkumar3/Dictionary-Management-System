/*
made by:
Rohan 201114

prefix searching mean words you want specially like starting with "a"
 or "an" or "z" etc 
*/
#include<iostream>
#include<cstring>
#include<windows.h>
#include <fstream>
#include<string.h>
#include<conio.h>
using namespace std;
bool check (string);
bool  searchdeleteWord(struct node *root, string word);
void gotoxy(short x, short y) 
{
	
COORD pos = {x, y};

SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}
const int alphabet_size=26;

struct word{
string key;
char meaning[800];
};

struct node
{
    struct node *children[alphabet_size];

    bool endofword;
};

// class implementation of dictionary
class dictionary{
public:
    string s;
    /* Functions Declaration */
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

        for(int i=0;i<alphabet_size;i++)
            tnode->children[i]=NULL;

        return tnode;
}

void dictionary::insert(struct node *root,string m)
{
	//system("cls");
    struct node *temp=root;
    int index;
    for(int i=0;i<m.length();i++)
    {
        index=m[i]-'a';
        if(temp->children[index]==NULL)
            {
                temp->children[index]=getnode();
            }
        temp=temp->children[index];
    }
    temp->endofword=true;
}

void dictionary::search(struct node * root,string var)
{
    struct node * temp=root;
    if(!searchdeleteWord(root, var)){
                cout<<"\n\n\t \xDB\xDB\xDB\xDb\xB2 No Any Word Found Named " << " [" << var << "]\n\n"  ;
				return ;
	}
    int index;
    for(int i=0;i<var.length();i++)
    {
        index=var[i]-'a';
        if(index<0){
        	return ;
		}
        if(root->children[index]==NULL)
            {
            	
                cout<<"\n\n\t \xDB\xDB\xDB\xDb\xB2 No Any Word Found Named " << " [" << var << "]\n\n"  ;
				return ;
            }
        root=root->children[index];
    }



string bigstring,str;
char c[400],a[400];
int i;


    ifstream myfile2;
    myfile2.open("myfile2.dat");
    while(!myfile2.eof())
        {
        getline(myfile2,bigstring);
        i=bigstring.find(".");
        str=bigstring.substr(0,i);
        strcpy(c, str.c_str());
        strcpy(a, var.c_str());
            if(strcmp(a ,c)==0)
                {
                cout<<endl<<"\n\t  \xDB\xDB\xDB\xDb\xB2 Meaning of The Word  ' "<< var <<" '  :\n =>  "<<bigstring.substr(i+1)<<endl;
                }
        }
        myfile2.close();
}

bool dictionary:: deleteWord(struct node *root, string word)
{
    if(!searchdeleteWord(root,word)){
    	return false;
	}
    struct node *temp = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = (word[i]-'a');
        if(index<0){
        	return false;
		}

        if (!temp->children[index])
            return false;

        temp = temp->children[index];
    }
string c;
    if (temp != NULL && temp->endofword)
    {
        temp->endofword = false;

        ifstream myfile;
        ofstream temp;

        myfile.open("myfile.dat");
        temp.open("temp.dat");

        while(getline(myfile,c))
        {
            if(c!=word)
                temp<<c<<endl;
        }

        myfile.close();
        temp.close();
        remove("myfile.dat");
        rename("temp.dat","myfile.dat");
            return true;
    }
}
bool  searchdeleteWord(struct node *root, string word)
{
    struct node *temp = root;
    int flag=0;
    for (int i = 0; i < word.length(); i++)
    {
        int index = (word[i]-'a');
        if(index<0){
        	return false;
		}

        if (!temp->children[index])
            return false;

        temp = temp->children[index];
    }
string c;
    if (temp != NULL && temp->endofword)
    {
        fstream myfile;

        myfile.open("myfile.dat");

        while(getline(myfile,c))
        {
            if(c==word)
            flag=1;
        }

        myfile.close();
    }
    if(flag==1){
    	return true;
	}
	else{
		return false;
	}
}

//function for reading from file
void dictionary:: fileRead(struct node * root)
{
    string data;
    ifstream myfile;

    myfile.open("myfile.dat",ios::app);
    while(!myfile.eof())
{
    getline(myfile,data);
    insert(root,data);
}
    myfile.close();
}

//functiion to print in alphabetical order through recursion
void dictionary:: alphabeticalOrder(struct node* root, char allWords[], int index)
{
    struct node* temp = root;
    if(temp != NULL && temp->endofword == true)
        {
        
		for(int j = 0; j < index; j++)
         {
            cout << allWords[j];
         }
         cout << " ";
        cout << "\n\t\xB2->  ";
        
        }

    for(int i = 0; i < alphabet_size; i++)
        {
        if(temp->children[i] != NULL)
        {
            allWords[index] = 'a' + i;
            alphabeticalOrder(temp->children[i], allWords, index + 1);
        }
        }
}

// function to print the results of a given prefix search
void dictionary:: print_prefix_search(struct node* root, char allWords[], int index, string prefix)
{
	 struct node* temp = root;
    if(temp != NULL && temp->endofword == true)
        {
        	
        cout <<"\n\t  \xB2->"<< prefix;

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
            allWords[index] = 'a' + i;
            print_prefix_search(temp->children[i], allWords, index + 1, prefix);
        }
        }
}

// function to search the words that match the prefix entered
void dictionary::prefix_search(struct node* root, string prefix)
{
    struct node* temp = root;
	char allWords[50];
    int index = 0 , i;
    for( i = 0; i < prefix.length(); i++)
        {
        index = prefix[i]-'a';
        if(index<0){
        	return ;
		}
        if(temp->children[index]==false)
        {
        cout << "\n\n\t\xB2--> No Any Word Is present In Dictionary With This Prefix: ";
        Sleep(300);
    	return ;
		}
        temp = temp->children[index];
        }
    print_prefix_search(temp, allWords, 0, prefix);
}
bool check(string word)
{
	int index =  0;
	for(int i=0 ; i<word.length() ; i++){
		index = word[i] - 'a';
		if(index < 0){
			return false;
		}
	}
	return true;
}
void start(void)
{
	long int r;
	int i,j;
	int y=5;
	char c = 177;
	for(i=0;i<20;i++)
	{
		gotoxy(25,y);
		if(i==0||i==19)
	
		for(j=0;j<50;j++)
		{
	
			cout << c;
			for(r=0;r<10000000;r++);
	
		}
	
		else
	{
			for(j=0;j<50;j++)
			{
				
				if(j==0||j==49)
				cout << c;
		
				else 
				cout << " ";
			
			}
			
			for(r=0;r<10000000;r++);
	
	}
	
		cout<< "";
		y++;
	}
	
	gotoxy(32,14);
	cout << "!!! ENGLISH SEARCH DICTIONARY !!!";
    getch();
	
}
int main()
{
	
		dictionary d;
        struct word w;
	    string data,data1;
	    int flag;
        struct node *root=d.getnode();      // root node points to whole trie
        d.fileRead(root);
		string word;
		char choice='0';
		start();
   while(choice != '7')
{
		system("cls");
        cout << "\n\t\t\t \xDB\xDB\xDB\xDb\xB2 Please Choose Ralevant Option Provided Below \xB2\xDB\xDB\xDB\xDb" << endl;
        cout << "\n";
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 1. Insert a word.\n";
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 2. Search a word.\n";
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 3. Delete a word.\n";
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 4. Print All Words Present in dictionary in alphabetical order.\n";
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 5. Prefix search.\n";
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 6. How Prefix search Works.\n";
		cout <<"\n\t \xDB\xDB\xDB\xDb\xB2 7. Exit.__";
			
        fflush(stdin);
        choice=getch();
       switch(choice)
{
   case '1':
    {
    	system("cls");
        cout<<"\n\t \xDB\xDB\xDB\xDb\xB2 Enter A Word To Add into the Dictionary: " ;
        cin>>data1;
        if(!check(data1))
       {
          	cout << "\n -> Invalid Word  " ;
        	cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
    	    getch();
            break;
		}	
        if(searchdeleteWord(root , data1))
        {
        	cout << "\n -> This Word is Already Present in the Dictionary:  " ;
        	cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
    	    getch();
            break;
		}
		w.key  = data1;
        gotoxy(9,4);
        cout << endl << "\n\t \xDB\xDB\xDB\xDb\xB2 Enter the meaning :  ";
        fflush(stdin);
        gets(w.meaning);
        ofstream myfile2;
        myfile2.open("myfile2.dat",ios::app);
        myfile2 << w.key+"."+w.meaning;
		myfile2<<endl;
        ofstream  myfile;
        myfile.open("myfile.dat",ios::app);
        myfile<<w.key;
        myfile<<endl;
        d.insert(root,w.key);
		myfile.close();
    	myfile2.close();
    	cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
    	getch();
        break;
    }


    case '2':
     {
		system("cls");
        cout<<"\n\t \xDB\xDB\xDB\xDb\xB2 Enter word to be search : ";
        cin>>word;
        d.search(root,word);
        cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
        getch();
        break;
     }

    case '3':
     {
     	system("cls");
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 Which word would you like to delete? ";

        cin >> word;
        if(d.deleteWord(root, word))
        {
        cout <<"\n \t \xDB\xDB\xDB\xDb\xB2 ' "<< word << " ' has been successfully deleted from the Dictionary.\n";
        }

        else
        {
        cout << "\n\t \xDB\xDB\xDB\xDb\xB2 No such word exists in the Dictionary.\n";
        }
        cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
			getch();
        break;
        }


        case '4':
        {
		system("cls");
        char allWords[52]={0};
        cout<<"\n\t\t\t\xDB\xDB\xDB\xDb\xB2    WORDS IN DICTIONARY   	\xDB\xDB\xDB\xDb\xB2\n\n"<<endl;
        d.alphabeticalOrder(root, allWords, 0);
        cout << "\n";
        cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
			getch();
        break;
        }

        case '5':
        {
        system("cls");
        cout << "\t \xDB\xDB\xDB\xDb\xB2 Enter the word you would like to use as a prefix:  ";
        cin >> word;
        if(!check(word)){
        	cout << "\n -> Invalid Word  " ;
        	cout<<"\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
    	    getch();
            break;
		}
        d.prefix_search(root, word);
        cout<<"\n\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
      	getch();
        break;
        }
         case '6':
        {
        		system("cls");
          	cout << "\n\xDB\xDB\xDB\xDb\xB2 Prefix Search is Basically Based on "
	        " Prefixes of the WORD \ni.e, You want All Words Starting With Letter 'A' , OR 'An'"
			" & So on... \nSo in Prefix Search You Just Need To Insert letter or letters you want to search :) & \nthen Program With Show you all Results (Words) Available in Dictionary: "
        	"\n\n\n\t\t PRESS ANY KEY TO GO BACK TO MAIN MENU ";
            	fflush(stdin);   // clear buffer
				getch();
        		break;
		}
        case '7':
        {
        		exit(1);
        		break;
		}
		default:
		{
					cout<<"\t \xDB\xDB\xDB\xDb\xB2 Selected Option is Invalid ,  Choose Again: !" ;
                	Sleep(700);
                 	system("cls");
		}
			
}
}
}
