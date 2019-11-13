#include "plane.h"
#include "places.h"
#include <errno.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <bits/stdc++.h>

bool BUILD = 1;

const int ALPHABET_SIZE = 57;
const int RETURN_ARR_SIZE = 2;
const char ALPHA[ALPHABET_SIZE]= {'A','B','C','D','E','F','G','H','I','J'
                                  ,'K','L','M','N','O','P','Q','R','S','T'
                                  ,'U','V','W','X','Y','Z','a','b','c','d','e'
                                  ,'f','g','h','i','j','k','l','m','n','o','p'
                                  ,'q','r','s','t','u','v','w','x','y','z'
                                  ,' ','.','-','(',')'};

struct position2{
  float lon;
  float lat;
};



struct TrieNode
{
  struct TrieNode *children[ALPHABET_SIZE]; //array of potential children
  //isEndOfWord is true if the node
  //represents end of a word
  bool isEndOfWord;
  position2 location;
};

TrieNode * globRoot;
typedef struct TrieNode TrieNode;
struct returnSearch
{
  float* arr;
  std::string output;
};
struct TrieNode *getNode(void)
{
  struct TrieNode *pNode =  new TrieNode;//allocates space for new node entry
  pNode->isEndOfWord = false;

  for (int i = 0; i < ALPHABET_SIZE; i++) //sets all child nodes to null
    pNode->children[i] = NULL;
  return pNode;
}


int findIndexInAlpha(char * letter) //helper function to find
{
  for(int i = 0;i<ALPHABET_SIZE;i++)
    {
      if(*letter==*&ALPHA[i])
        {
          return i;
        }
    }
  return -1;
}


void insert(struct TrieNode *root, std::string key, float lat, float lon)
{
  struct TrieNode *pCrawl = root;
  for (int i = 0; i < key.length(); i++)
    {

      int index = findIndexInAlpha(&key[i]);
      if(index!=-1)
        {
          if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
          pCrawl->location.lat = pCrawl->location.lon = -200;
          pCrawl = pCrawl->children[index];
        }
    }
  pCrawl->isEndOfWord = true;
  pCrawl->location.lat = lat;
  pCrawl->location.lon = lon;
}


std::string formatOutput(struct returnSearch done)
{
  std::string finalOutput;
  int i = 2;
  while(*&done.output[i]!=' ' || *&done.output[i+1]!=' ')
    {
      finalOutput+=done.output[i];
      i++;
    }
  finalOutput+=", ";
  for(int j=0;j < 2;j++)
    finalOutput+=done.output[j];
  finalOutput+=": ";
  finalOutput+= std::to_string(done.arr[0]);
  finalOutput+= ", ";
  finalOutput+= std::to_string(done.arr[1]);
  return finalOutput;
}
returnSearch searchTrie(struct TrieNode *root, std::string key, float arr[])
{
  returnSearch returnMe;
  returnMe.arr = NULL;
returnMe.output = "";
std::string output = "";
arr[0]=arr[1]=-1;
struct TrieNode *pCrawl = root;
for (int i = 0; i < key.length(); i++)
  {
    int index = findIndexInAlpha(&key[i]); // - 'a';
    if(index!=-1)
      {
        if (!pCrawl->children[index])
          return returnMe;
        output += ALPHA[index];
        pCrawl = pCrawl->children[index];
      }
  }

while(pCrawl != NULL && !pCrawl->isEndOfWord)
  {
    bool done = 0;
    for (int i = 0; i < ALPHABET_SIZE;i++)
      {
        if(pCrawl->children[i]!=NULL && !done && !pCrawl->isEndOfWord)
          {
            done = 1;
            output+=ALPHA[i];
            pCrawl=pCrawl->children[i];
          }
      }
  }

if (pCrawl != NULL && pCrawl->isEndOfWord)
  {
    arr[0] = pCrawl->location.lat;
    arr[1] = pCrawl->location.lon;
    returnMe.arr = arr;
    returnMe.output = output;
    return returnMe;
  }
return returnMe;
}


std::string formatInput(std::string line)
{
  std::string input;
  for(int i = 0; i<2; i++)
    input += line[i];
  for(int i = 9; i<54;i++)
    input += line[i];
  return input;
}
float formatlat(std::string line)
{
  return atof(line.substr(143,9).c_str());
}
float formatlon(std::string line)
{
  return atof(line.substr(153,11).c_str());
}




//Copies heap allocated planeListRet into stack allocated version
void ptrToStatic(planeListRet &s, planeListRet *ptr);
//Takes cityname and state name and sets lat and lon of that location
//Also sets place info for city state
//const char* setCoords(location *loc, double &lat, double &lon);

planeListRet* query_places_1_svc(location *argp, struct svc_req *rqstp)
{
  //No need to xdr_free(), no structures allocated on the heap 
  errno = 0;//clear garbage data
  static planeListRet result_1;	
  planeListRet *resultPtr = nullptr;
  CLIENT *clnt = nullptr;
  position query_airports_1_arg;//just two doubles
  //Use the city and state name to find client coordinates 
  
  if(BUILD)
    {
      
      std::ifstream file;
      
      file.open("places2k.txt");
      struct TrieNode * root = getNode();
      std::string placename = ""; //stored as STATE CODE + FULL NAME ex. WASeattle City
      std::string city;
      float lati;
      float longi;
      
      
  
  
  
      std::string line;
      while(getline(file,line))
        {
          placename = formatInput(line);
          // string placename = line.substr(0,2)+line.substr(9,63);
          lati = formatlat(line);
          longi = formatlon(line);
          insert(root, placename, lati, longi);
        }
      globRoot = root;
      BUILD = 0;
    }

  float helper[2] = {0,0};

  //passing ARGUMENT into search function

  std::string input = "";
  input += argp->state;
  input += argp->place;

  struct returnSearch done = searchTrie(globRoot, input, helper);

  
  std::string output = formatOutput(done);

  const char* outputMe = output.c_str();
    
  //const char* info = setCoords(argp, query_airports_1_arg.lat, query_airports_1_arg.lon);
  query_airports_1_arg.lat = (double)helper[0];
  query_airports_1_arg.lon = (double)helper[1];
  
  #ifndef	DEBUG	
  clnt = clnt_create (argp->host, AIRPORT_LOOKUP_PROG, AIRPORT_LOOKUP_VERS, "udp");
  #endif
  
  errno = 0;//clnt_create is setting errno to 13 = no permission

  
  
  resultPtr = query_airports_1(&query_airports_1_arg, clnt);
  ptrToStatic(result_1, resultPtr);  
  
  #ifndef	DEBUG
  //Free xdr memory
  
  clnt_freeres(clnt, (xdrproc_t)xdr_planeListRet, (char *)resultPtr); 
  clnt_destroy(clnt);
  #endif

  
  
  result_1.planeListRet_u.airp.p = (char*)outputMe;
  result_1.err = errno;
	return &result_1;
}

void ptrToStatic(planeListRet &s, planeListRet *ptr){
  
  s.planeListRet_u.airp.p = ptr->planeListRet_u.airp.p;
  
  s.planeListRet_u.airp.port1 = ptr->planeListRet_u.airp.port1;
  ptr->planeListRet_u.airp.port1 = nullptr;  
  s.planeListRet_u.airp.port2 = ptr->planeListRet_u.airp.port2;
  ptr->planeListRet_u.airp.port2 = nullptr;  
  s.planeListRet_u.airp.port3 = ptr->planeListRet_u.airp.port3;
  ptr->planeListRet_u.airp.port3 = nullptr;  
  s.planeListRet_u.airp.port4 = ptr->planeListRet_u.airp.port4;
  ptr->planeListRet_u.airp.port4 = nullptr;  
  s.planeListRet_u.airp.port5 = ptr->planeListRet_u.airp.port5;
  ptr->planeListRet_u.airp.port5 = nullptr;  
} 





