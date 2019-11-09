//IMPORTANT: I think what's happening with min.latitude is that
// the empty lines in the input file are being considered as viable nodes
// and are inserted as nodes with info 0 0 0 0 0 . not sure if this is true
//though but worth mentioning!!


// A C++ program to demonstrate find minimum on KD tree
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <bits/stdc++.h>
using namespace std;

const int k = 2; //number of dimensions, aka (x,y) coords

struct airport{
  char* acr; //airport acronym
  char* name; //full city name + state (for now)
  float point[k]; //coordinates
  airport * next;
};

// A structure to represent node of kd tree
struct airportNode {
  airport data;
  float point[k]; // To store k dimensional point
  airportNode *left, *right;
};

void printTree(airportNode * root)
{
  if(root == NULL)
    return;
  printTree(root->left);
  printTree(root->right);
  cout << " ACR: "; cout << root->data.name;
  cout << " LAT: "; cout << root->point[0];
  cout << " LON: "; cout << root->point[1];
  cout << "\n";
}

// A method to create a node of K D tree
struct airportNode* newNode(char* acr, char* name, float arr[])
{
  struct airportNode* temp = new airportNode;
  temp->data.acr = acr;
  temp->data.name = name;
  temp->data.next = NULL;
  for (int i = 0; i < k; i++)
    {
      temp->point[i] = arr[i];
      temp->data.point[i] = arr[i];
    }
  temp->left = temp->right = NULL;
  return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
airportNode* insertRec(airportNode* root, char* acr, char* name, float point[], unsigned depth)
{
  // Tree is empty?
  if (root == NULL)
    return newNode(acr, name, point);

  // Calculate current dimension (cd) of comparison
  unsigned cd = depth % k;

  // Compare the new point with root on current dimension 'cd'
  // and decide the left or right subtree
  if (point[cd] < (root->point[cd]))
    root->left = insertRec(root->left, acr, name, point, depth + 1);
  else
    root->right = insertRec(root->right, acr, name, point, depth + 1);

  return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
airportNode* insert(airportNode* root, char* acr, char* name, float point[])
{
  return insertRec(root, acr, name, point, 0);
}

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
    return 0;

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
  cout << &root->data.point << "{}{}{}{}" << &point << endl;
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



// Driver program to test above functions
int main()
{
  struct airportNode* root = NULL;
  //  float points[][k] = { { 30, 40 }, { 5, 25 },
  //                  { 70, 70 }, { 10, 12 }, { 50, 30 }, { 35, 45 } };

  //int n = sizeof(points) / sizeof(points[0]);

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
          char* readAcr;
          //char* readName;
          //        char* readAcr = (char*) line.substr(0,4).c_str();
          char* readName = (char*) line.substr(17,line.length()-17).c_str();
          float readToMe[] = {atof(line.substr(6,5).c_str()), atof(line.substr(12,6).c_str())};
          /*
            airports readToMe;
            readToMe.acr = (char*) line.substr(0,4).c_str()
            readToMe.lat = atof(line.substr(6,10).c_str());
            readToMe.lon = atof(line.substr(12,17).c_str());
            //          readToMe.coords.push_back(readToMe.lat);
            // readToMe.coords.push_back(readToMe.lon);
            readToMe.name = (char*) line.substr(18,line.length()-1).c_str();
            readToMe.next = NULL;
            cout << "calling insert";
            cout << "\n";
          */
          //

          //parse airport abbreviation
          string str ="";
          for(int i=1; i<4; i++)
            str += line[i];

          readAcr = const_cast<char*>(str.c_str());

          //parse name
          string str4 ="";
          for(int i=19; i<40; i++)
            str4 += line[i];

          readName = const_cast<char*>(str4.c_str());
          cout << "Inserting airport with info:"
               << readAcr << " " << readName << " "
               << readToMe[0] << " " << readToMe[1]
               << endl;

          root = insert(root, readAcr, readName, readToMe);

          cout << "Root:"
               << root->data.acr << " " << root->data.name << " "
               << root->data.point[0] << " " << root->data.point[1]
               << " " << "inserted" << endl;

          cout << "\n";
          cout << "insert called" ;
          cout << "\n";
        }
      }
    }
  cout << "End of insertion" << endl << endl;
  printTree(root);
  //
  //
  /*
    for (int i = 0; i < n; i++)
    root = insert(root, points[i]);
  */
  cout << "Testing find minimum" << endl;
  cout << "Minimum of 0'th dimension (lat) is " << findMin(root, 0) << endl;
  cout << "Minimum of 1'th dimension (long) is " << findMin(root, 1) << endl;

  //  airport test;
  //test.point = {33.58 -85.85};

  cout << endl << "Testing searching for a node with specific coordinates" << endl;
  //for now this does not return an airport node so that needs to be
  //changed
  float point1[] = {43.97 -107.97};
  (search(root, point1))? cout << "Found\n": cout << "Not Found\n";
  /*
    int point2[] = {12, 19};
    (search(root, point2))? cout << "Found\n": cout << "Not Found\n";
  */
  return 0;
}
