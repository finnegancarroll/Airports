//kd tree and linked list from geeksforgeeks
//distance formulas from the code in the hw4 pdf
//other logic and conversion is my own

// A C++ program to demonstrate find minimum on KD tree
#include <iostream>
#include <fstream>
#include <string>
#include <vector> // for knn, used to sort a list of airports
#include <algorithm> //to sort vector of airports

#include <bits/stdc++.h>

#include <math.h>

#define pi 3.14159265358979323846 
using namespace std;

const int k = 2; //number of dimensions, aka (x,y) coords
//data structures
struct airport{
  char* acr; //state acronym
  char* name; //full city name + state (for now)
  float point[k]; //coordinates
  //point[0] = lat
  //point[1] = long

  double distance; // starts out at 0, will be filled when KNN is run
  //value will be distance from the origin of the KNN to this airport
};

// A structure to represent node of kd tree
struct airportNode {
  airport data;
  airportNode *left, *right;
};

//////////////////////////////////////////////////////////////////
//DISTANCE FORMULA THINGS
double deg2rad(double deg);  
double rad2deg(double rad);
  
double distance(double lat1, double lon1, double lat2, double lon2, char unit)
{
  double theta,dist;
  theta = lon1 - lon2;
  dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) *
    cos(deg2rad(lat2)) * cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;
  switch(unit) {
  case 'M':
    break;
  case 'K':
    dist = dist * 1.609344;
    break;
  case 'N':
    dist = dist * 0.8684;
    break;
  }
  //cout << "ADBK" << dist << endl;
  return (dist);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg)
{
  return (deg * pi / 180);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad)
{
  return (rad * 180 / pi);
} 

void getDistanceValues(airportNode * root, airport origin)
{
  //note:
  //root = root of the current tree section
  //origin = place we want to find the distance from 
  if(root == NULL)
    return;

  getDistanceValues(root->left, origin);
  getDistanceValues(root->right, origin);

  double dist = 0;
  //set values
  //coordinate 1 = root
  double lat1 = root->data.point[0];
  double long1 = root->data.point[1];
 
  //coordinate 2 = origin
  double lat2 = origin.point[0];
  double long2 = origin.point[1];
  cout << lat1 << " " << long1 << " " << lat2 << " " << long2 << endl; 
  //double distance(double lat1, double lon1, double lat2, double lon2, char unit)
  //find distance in miles. miles because this is america
  dist = distance(lat1, long1, lat2, long2, 'M');
  cout << "{}{}" << dist << endl;
  //string abc;
  //cin>> abc;
  root->data.distance = dist;
  //printf(root->data.acr);
  //printf(root->data.name);
  //cout << root->data.point[0] << " " << root->data.point[1] << endl;
  //cout << "\n";
}

//////////////////////////////////////////////////////////////////
//KD TREE CONSTRUCTION CODE
// A method to create a node of K D tree
struct airportNode* newNode(string acr, string name, float arr[])
{
  cout << acr << name << endl;

  char* temp2 = new char[acr.length() + 1];
  strcpy(temp2, acr.c_str());
  
  struct airportNode* temp = new airportNode;

  temp->data.acr = temp2;
  
  char* temp3 = new char[name.length() + 1];
  strcpy(temp3, name.c_str());
  
  temp->data.name = temp3;

  for (int i = 0; i < k; i++)
    {      
      temp->data.point[i] = arr[i];
    }
  temp->data.distance = 0;
  temp->left = temp->right = NULL;

  cout << "TEMP NODE INFO" << endl;

  printf(temp->data.acr);
  
  return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
airportNode* insertRec(airportNode* root, string acr, string name, float point[], unsigned depth)
{
  // Tree is empty?
  if (root == NULL)
    return newNode(acr, name, point);

  // Calculate current dimension (cd) of comparison
  unsigned cd = depth % k;

  // Compare the new point with root on current dimension 'cd'
  // and decide the left or right subtree
  if (point[cd] < (root->data.point[cd]))
    root->left = insertRec(root->left, acr, name, point, depth + 1);
  else
    root->right = insertRec(root->right, acr, name, point, depth + 1);

  return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
airportNode* insert(airportNode* root, string acr, string name, float point[])
{
  return insertRec(root, acr, name, point, 0);
}
////////////////////////////////////////////////////////////////
// functions to interact with the KD tree
// A utility function to find minimum of three integers
float min(float x, float y, float z)
{
  return min(x, min(y, z));
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
float findMinRec(airportNode* root, int d, unsigned depth)
{
  // Base cases
  if (root == NULL)
    return INT_MAX;

  // Current dimension is computed using current depth and total
  // dimensions (k)
  unsigned cd = depth % k;

  // Compare point with root with respect to cd (Current dimension)
  if (cd == d) {
    if (root->left == NULL)
      return root->data.point[d];
    return min(root->data.point[d], findMinRec(root->left, d, depth + 1));
  }

  // If current dimension is different then minimum can be anywhere
  // in this subtree
  return min(root->data.point[d],
             findMinRec(root->left, d, depth + 1),
             findMinRec(root->right, d, depth + 1));
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
float findMin(airportNode* root, float d)
{
  // Pass current level or depth as 0
  return findMinRec(root, d, 0);
}

//search functions, and every helper function related to search functions
// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(float point1[], float point2[])
{
  // Compare individual pointinate values
  for (int i = 0; i < k; ++i)
    if (point1[i] != point2[i])
      return false;

  return true;
}

// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
bool searchRec(airportNode* root, float point[], unsigned depth)
{
  // Base cases
  if (root == NULL)
    return false;
  cout << "search function is here, if it spits out pointer"
       << "garb it isnt working properly" << endl;
  cout << root->data.point[0] << "{}{}{}{}" << point[0] << endl;
  if (arePointsSame(root->data.point, point))
    return true;

  // Current dimension is computed using current depth and total
  // dimensions (k)
  unsigned cd = depth % k;

  // Compare point with root with respect to cd (Current dimension)
  if (point[cd] < root->data.point[cd])
    return searchRec(root->left, point, depth + 1);

  return searchRec(root->right, point, depth + 1);
}

// Searches a Point in the K D tree. It mainly uses
// searchRec()
bool search(airportNode* root, float point[])
{
  // Pass current depth as 0
  return searchRec(root, point, 0);
}

void printTree(airportNode * root)
{
  if(root == NULL)
    return;
  
  printTree(root->left);
  printTree(root->right);
  printf(root->data.acr);
  printf(root->data.name);
  cout << root->data.point[0] << " " << root->data.point[1] << endl;
  cout << "distance: " << root->data.distance << endl;
  cout << "\n";
}
/////////////////////////////////////////////////////////////////////


void fillVector(airportNode * root, vector<airport> &airportVector)
{
  if(root == NULL)
    return;

  fillVector(root->left, airportVector);
  fillVector(root->right, airportVector);
  airportVector.insert(airportVector.begin(), root->data); 
  /*
  printf(root->data.acr);
  printf(root->data.name);
  cout << root->data.point[0] << " " << root->data.point[1] << endl;
  cout << "distance: " << root->data.distance << endl;
  cout << "\n";
  */
}

// Compares two intervals according to staring times.
bool compareDistance(airport a1, airport a2)
{
  return (a1.distance < a2.distance);
} 

////////////////////////////////////////////////////////////////////////////
//LINKED LIST
class airportListNode
{
public:
  airport data;
  airportListNode *next;
};


/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end */
void append(airportListNode** head_ref, airport new_data)
{
  /* 1. allocate node */
  airportListNode* new_node = new airportListNode();

  airportListNode *last = *head_ref; /* used in step 5*/

  /* 2. put in the data */
  new_node->data = new_data;

  /* 3. This new node is going to be
     the last node, so make next of
     it as NULL*/
  new_node->next = NULL;

  /* 4. If the Linked List is empty,
     then make the new node as head */
  if (*head_ref == NULL)
    {
      *head_ref = new_node;
      return;
    }
  /* 5. Else traverse till the last node */
  while (last->next != NULL)
    last = last->next;

  /* 6. Change the next of last node */
  last->next = new_node;
  return;
}


void printList(airportListNode *node)
{
  while (node != NULL)
    {
      cout<<" "<<node->data.name;
      cout<<" "<<node->data.distance;
      node = node->next;
    }
}  
///////////////////////////////////////////////////////////////////////////

// Driver program to test above functions
int main()
{

  struct airportNode* root = NULL;

  //insert points using input file
  int count = 0;
  string line;
  ifstream file;
  file.open("airport-locations.txt");

  while(getline(file,line))
    {
      cout << count;
      cout << "while loop start";
      cout << "\n";
      count++;
      if(count>1) { //skip first line of airport-location file because it
        // is not a real airport location

        if(line.find(",") != string::npos) {

          string readAcr;
          string readName;
         
          float readToMe[] = {atof(line.substr(6,10).c_str()), atof(line.substr(12,17).c_str())};

          //parse airport abbreviation
          /*
          string str ="";
          for(int i=1; i<4; i++)
            str += line[i];
          */

          
          //parse name
          string str4 ="";

          //char holder = 'a';

          /*
          for(int i=20; i<line.length(); i++)
            str4 += line[i];
          cout << str4 << "[][][]" << endl;
          */
          int g = 20;
          while(line[g] != ','){
            str4+= line[g];
            //            holder = line[g];
            g++;
            //cout << holder << endl;
          }
          string str = "";
          for(int i = g+1; i<g+3; i++)
            str +=line[i];
          
          cout << "Inserting airport with info:"
               << str << " " << str4 << " "
               << readToMe[0] << " " << readToMe[1]
               << endl;
          root = insert(root, str, str4, readToMe);
          
          cout << "Root:";
          printf(root->data.acr);

          cout << root->data.point[0] << " " << root->data.point[1]
               << " " << "inserted" << endl;
               
          cout << "\n";
          cout << "insert called" ;
          cout << "\n";
        }
      }
    }
  cout << "End of insertion" << endl << endl;

  cout << "Testing find minimum" << endl;
  cout << "Minimum of 0'th dimension (lat) is " << findMin(root, 0) << endl;
  cout << "Minimum of 1'th dimension (long) is " << findMin(root, 1) << endl;

  cout << endl << "Testing searching for a node with specific coordinates" << endl;
  //for now this does not return an airport node so that needs to be
  //changed
  float point1[] = {43.97 -107.97};
  (search(root, point1))? cout << "Found\n": cout << "Not Found\n";

  //printTree(root);

  //testing distance function
  double long1 = 1;
  double lat1 = 1;
  double long2 = 2;
  double lat2 = 2;
  double dist = 0;
  
  //distance usage:
  //distance(double lat1, double lon1, double lat2, double lon2, char unit) 

  //dist = (lat1, long1, lat2, long2, 'M');
  //cout << "miles: " << dist << endl;

  airport test;
  test.point[0] = 69;
  test.point[1] = 3;
  
  getDistanceValues(root, test);
  printTree(root);
  vector<airport> airportVector;
  fillVector(root, airportVector);
  cout << "size: " << airportVector.size() << '\n';
  //sort the vector based off of distance
  //smaller distances -> largerr distances
  sort(airportVector.begin(), airportVector.end(), compareDistance);

  vector<airport> returnVector;
  int KNNk = 5;
  for(int i = 0; i < KNNk; i++)
    returnVector.push_back(airportVector.at(i));
    //returnVector.insert(airportVector.at(i));

  cout << "return vector info" << endl;
  for(int i = 0; i < KNNk; i++)
    cout << returnVector[i].distance <<endl;
  //myvector.at(i)

  //for(int i = 0; i < KNNk; i++)

  /* Start with the empty list */
  airportListNode* head = NULL;
  for(int i = 0; i < KNNk; i++)
    append(&head, returnVector[i]);
  cout<<"Linked list is: "; 
  printList(head);
  return 0;
} 
