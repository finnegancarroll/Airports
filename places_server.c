//kd tree and linked list based heavily on those found on geeksforgeeks
//modified to work with the custom made airport struct
//distance formulas from the code in the hw4 pdf
//other logic and conversion is my own

//RPC includes
#include "places.h"
#include <errno.h>

// A C++ program to demonstrate find minimum on KD tree
#include <fstream> //for filereads
#include <string> //for filereads
#include <vector> // for knn, used to sort a list of airports
#include <algorithm> //to sort vector of airports

#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>

#define pi 3.14159265358979323846 //used in distance formula
using namespace std;

const int dimensions = 2; //number of dimensions, aka (x,y) coords

void fiveClosest(position *p, planeListRet &list);

//data structures
struct airport{
  char* acr; //airport acronym
  char* stateAcr; //state acronym
  char* name; //full city name + state (for now)
  float point[dimensions]; //coordinates
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

planeListRet *
query_airports_1_svc(position *argp, struct svc_req *rqstp)
{
  //No need to xdr_free(), no structures allocated on the heap
  errno = 0;//clear garbage data
  static planeListRet result_1;
  //Default info value
  result_1.planeListRet_u.airp.p = "Error: No Place Info";
  
  result_1.planeListRet_u.airp.port1 = "TEST";
  result_1.planeListRet_u.airp.port2 = "TEST";
  result_1.planeListRet_u.airp.port3 = "TEST";
  result_1.planeListRet_u.airp.port4 = "TEST";
  result_1.planeListRet_u.airp.port5 = "TEST";
  
  //fiveClosest(argp, result_1);

  result_1.err = errno;
  return &result_1;
}

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
  return (dist);
}

//This function converts decimal degrees to radians
double deg2rad(double deg)
{
  return (deg * pi / 180);
}

//This function converts radians to decimal degrees
double rad2deg(double rad)
{
  return (rad * 180 / pi);
}

//fills the distance variable located in the airport variable of every node
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

  //distance formula usage =
  //distance(double lat1, double lon1, double lat2, double lon2, char unit)
  //find distance in miles. miles because this is america
  dist = distance(lat1, long1, lat2, long2, 'M');
  root->data.distance = dist;
}

//////////////////////////////////////////////////////////////////
//KD TREE CONSTRUCTION CODE
// A method to create a node of K D tree
struct airportNode* newNode(string acr, string stateAcr, string name, float arr[])
{
  char* acrHolder = new char[acr.length() + 1];
  strcpy(acrHolder, acr.c_str());

  char* stateAcrHolder = new char[stateAcr.length() + 1];
  strcpy(stateAcrHolder, stateAcr.c_str());

  char* nameHolder = new char[name.length() + 1];
  strcpy(nameHolder, name.c_str());

  struct airportNode* temp = new airportNode;
  temp->data.acr = acrHolder;
  temp->data.stateAcr = stateAcrHolder;
  temp->data.name = nameHolder;

  for (int i = 0; i < dimensions; i++){
    temp->data.point[i] = arr[i];
  }
  temp->data.distance = 0;
  temp->left = temp->right = NULL;
  return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
airportNode* insertRec(airportNode* root, string acr, string stateAcr, string name, float point[], unsigned depth)
{
  // Tree is empty?
  if (root == NULL)
    return newNode(acr, stateAcr, name, point);

  // Calculate current dimension (cd) of comparison
  unsigned cd = depth % dimensions;

  // Compare the new point with root on current dimension 'cd'
  // and decide the left or right subtree
  if (point[cd] < (root->data.point[cd]))
    root->left = insertRec(root->left, acr, stateAcr, name, point, depth + 1);
  else
    root->right = insertRec(root->right, acr, stateAcr, name, point, depth + 1);

  return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
airportNode* insert(airportNode* root, string acr, string stateAcr, string name, float point[])
{
  return insertRec(root, acr, stateAcr, name, point, 0);
}
////////////////////////////////////////////////////////////////
//KNN for KD TREE
//k = K in KNN
void findKMins(airportNode * root, vector<airport> &airportVector, int k)
{
  if(root == NULL)
    return;

  findKMins(root->left, airportVector, k);
  findKMins(root->right, airportVector, k);

  int i;
  for (i = k - 1; (i >= 0 && airportVector[i].distance > root->data.distance); i--){
    airportVector[i + 1] = airportVector[i];
  }
  airportVector[i + 1] = root->data;

}

////////////////////////////////////////////////////////////////////////////
//LINKED LIST functionality
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

///////////////////////////////////////////////////////////////////////////
// Driver program to test above functions

//planeListRet *
//query_airports_1_svc(position *argp, struct svc_req *rqstp)
void fiveClosest(position *p, planeListRet &list)
{
  errno = 0;//clear garbage data
  //static planeListRet result_1; //the value to be returned to the plane client

  //note on xdr_free: because we are using pointers alone, there actually is
  //no memory to be freed.
  //calling xdr_free is therefore impossible, and will try to free up memory
  // that isn't being used in the first place, seg faulting the program
  //xdr_free((xdrproc_t)xdr_planeListRet, (char*)&result_1);

  //SERVER CODE HERE
  struct airportNode* root = NULL; // starting node of the KD tree

  //KD tree construction begins
  //insert points using input file
  int count = 0;
  string line;
  ifstream file;
  file.open("airport-locations.txt");

  while(getline(file,line))
    {
      count++;
      if(count>1) { //skip first line of airport-location file because it
        // is not a real airport location

        if(line.find(",") != string::npos) {
          //reading in file
          //parse coordinates
          float coords[] = {atof(line.substr(6,10).c_str()), atof(line.substr(12,17).c_str())};

          //get airport acronym
          string acr = "";
          for(int i = 1; i < 4; i++)
            acr += line[i];
          //parse the city name
          string name ="";
          int g = 21;
          while(line[g] != ','){
            name+= line[g];
            g++;
          }
          
          //parse the state abbreviation
          string stateAcr = "";
          for(int i = g+1; i<g+3; i++)
            stateAcr +=line[i];
          
          //make new KD tree node with info from line
          root = insert(root, acr, stateAcr, name, coords);
        }
      }
    }
  file.close();




  
  //PLS REPLACE test with the coords from places!!!!
  //point[0] = lat
  //point[1] = long
  airport originCoords;
  originCoords.point[0] = 69;
  originCoords.point[1] = 3;
  //originCoords.point[0] = p->lat;
  //originCoords.point[1] = p->lon;






  
  //all airports start with distance 0, this iterates through all of them
  // and changes that value
  getDistanceValues(root, originCoords);

  //make a vector and fill it with the shortest 5 distances
  //we do this to make it so that you can change KNNk and still have the
  //program function as intended
  vector<airport> returnVector;
  int KNNk = 5;

  //fill returnVector with dummy data so that it doesn't segfault when
  //accessed for the first time
  //there is no way that there is a distance greater than 999999 because
  //the circumference of the earth is 24901 miles
  airport dummy;
  dummy.acr = "A";
  dummy.stateAcr = "B";
  dummy.name = "C";
  dummy.point[0] = 23;
  dummy.point[1] = 24;
  dummy.distance = 999999;

  for(int i = 0; i < KNNk; i++){
    returnVector.push_back(dummy);
  }

  //populate that empty vector with the KNNk shortest distances
  findKMins(root, returnVector, KNNk);
  ///////////////////////////////////////////

  //convert data in the vector into something we can send back to the client
  //to do this, we do this: airport->string->char*

  //turning data from airport into string
  vector<string> stringVector;
  string holder;

  for(int i = 0; i < KNNk; i++){
    holder += "code: ";
    holder += returnVector[i].acr;
    holder += ", name: ";
    holder += returnVector[i].name;
    holder += ", state: ";
    holder += returnVector[i].stateAcr;
    holder += ", distance: ";
    holder += to_string(returnVector[i].distance);
    stringVector.push_back(holder);
    holder = "";
  }

  //turning strings that contain airport data to char*s
  //allocate memory for each airport name we are returning
  //if I don't do the char*=new[variable length] thing, everything points
  //to the same thing
  char* temp0 = new char[stringVector[0].length() + 1];
  strcpy(temp0, stringVector[0].c_str());

  char* temp1 = new char[stringVector[1].length() + 1];
  strcpy(temp1, stringVector[1].c_str());

  char* temp2 = new char[stringVector[2].length() + 1];
  strcpy(temp2, stringVector[2].c_str());

  char* temp3 = new char[stringVector[3].length() + 1];
  strcpy(temp3, stringVector[3].c_str());

  char* temp4 = new char[stringVector[4].length() + 1];
  strcpy(temp4, stringVector[4].c_str());





  
  //CHANGE THIS!!!
  list.planeListRet_u.airp.p = "aBC";
  //CHANGE THIS!!








  
  list.planeListRet_u.airp.port1 = temp0;
  list.planeListRet_u.airp.port2 = temp1;
  list.planeListRet_u.airp.port3 = temp2;
  list.planeListRet_u.airp.port4 = temp3;
  list.planeListRet_u.airp.port5 = temp4;  

  //end of SERVER CODE HERE

  //result.err = errno;
  //return &result_1;
}