#include <iostream>
#include <fstream>
#include <string>

#include<bits/stdc++.h> 
extern int smile = 0;
using namespace std;

const int k = 2;

typedef struct airports* airportList;

struct airports{
  char* acr;
  char* name;
  float lon;
  float lat;
  airportList next;
};
struct node{
  airports * thisPort;
  node * left;
  node * right;
};
struct node* newNode(airports addMe)
{
  
  node* temp = new node;

  temp->thisPort = &addMe;
  smile++;
  cout << smile;
  if(smile%100 == 0)
    cin >> smile;
  cout << "New Node Added";
  temp->left = NULL;
  temp->right = NULL;
  return temp;
  cout << "WEIRDNESS";
}
void printTree(node * root)
{
  if(root == NULL)
    return;
  printTree(root->left);
  printTree(root->right);
  cout << root->thisPort->name;
  cout << "\n";
}

node * insertNode(node * root, airports addMe, unsigned depth)
{
  cout << "inside insert node";
  cout << "\n";
  unsigned dim = depth%k;
  if (root == NULL) {
    
    cout << "Found Leaf";
    cout << "\n";
    return newNode(addMe);
  }
    //dimension we are in currently, start in long0
  else if(dim == 0) //Could be one ???
  {
    if(addMe.lon < root->thisPort->lon)
      root->left = insertNode(root->left, addMe, depth + 1);
    else
      root->right = insertNode(root->right, addMe, depth + 1);
  }
  else if(dim == 1); //Could be one ???
  {
    if(addMe.lat < root->thisPort->lat)
      root->left = insertNode(root->left, addMe, depth + 1);
    else
      root->right = insertNode(root->right, addMe, depth + 1);
  }
  return root;
};
node* insert(node * root, airports  addThis)
{
  cout << "inside insert og";
  cout << "\n";
  return insertNode(root, addThis, 0);
}
int main() {
  node * root = NULL;
  int count = 0;
  ifstream file;
  file.open("airport-locations.txt");
  string line;
  //  airports * readToMe = NULL;
  //  cout << "meme";
  while(getline(file,line))
    {
      
      cout << count;
      cout << "while loop start";
      cout << "\n";
      // cout << line;
      //readToMe = new airports;
      count++;
      if(count>1) {
        
        //  cout << "1";
        if(line.find(",") != string::npos) {
          cout << line;
          //  cout << " 2";
          cout << "airport made";
          cout << "\n";
          airports readToMe;
          readToMe.acr = (char*) line.substr(0,4).c_str();
          //          cout << readToMe.acr;
          readToMe.lat = atof(line.substr(6,10).c_str());
          readToMe.lon = atof(line.substr(12,17).c_str());
          readToMe.name = (char*) line.substr(18,line.length()-1).c_str();
          readToMe.next = NULL;
          cout << "calling insert";
          cout << "\n";
          
          root = insert(root,readToMe);
          cout << "\n";
          cout << "insert called" ;
          cout << "\n";
          //         ~readToMe();
          //          readToMe = NULL;
          //          delete readToMe->acr;
          // delete readToMe->name;
          // delete readToMe->next;
          // delete readToMe;
        }
      }                     
    }
  
  //printTree(root);
  return 0; 
}                          
