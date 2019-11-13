#include <bits/stdc++.h>
using namespace std;
//extern int count;                        
const int ALPHABET_SIZE = 57;
const int RETURN_ARR_SIZE = 2;
const char ALPHA[ALPHABET_SIZE]= {'A','B','C','D','E','F','G','H','I','J'
                            ,'K','L','M','N','O','P','Q','R','S','T'
                            ,'U','V','W','X','Y','Z','a','b','c','d','e'
                            ,'f','g','h','i','j','k','l','m','n','o','p'
                            ,'q','r','s','t','u','v','w','x','y','z'
                                  ,' ','.','-','(',')'};

struct position{
  float lon;
  float lat;
};
struct TrieNode
{  
  struct TrieNode *children[ALPHABET_SIZE]; //array of potential children
  //isEndOfWord is true if the node
  //represents end of a word
  bool isEndOfWord;
  position location;
};
struct TrieNode *getNode(void)
{
  //  cout << "IN GET NODE" << endl;
  struct TrieNode *pNode =  new TrieNode;//allocates space for new node entry
  pNode->isEndOfWord = false;
  
  for (int i = 0; i < ALPHABET_SIZE; i++) //sets all child nodes to null
    pNode->children[i] = NULL;
  return pNode;
}
int findIndexInAlpha(char * letter) //helper function to find 
{
  //  cout << "IN INDEX HELPER" << endl;
  // cout << "letter: ";
  // cout << *letter << endl;  
  for(int i = 0;i<ALPHABET_SIZE;i++)
    {
      //      cout << i << endl;
      // cout << *&ALPHA[i];
      if(*letter==*&ALPHA[i])
        {         
          //          cout << "XD" << endl; 
          return i;
        }
    }
  return -1;
}
void insert(struct TrieNode *root, string key, float lat, float lon)
{
  //  cout << key << endl;
  // cout << "In insert" << endl;
  //  count++;
  //  cout << count << endl;
  
  struct TrieNode *pCrawl = root; 
  for (int i = 0; i < key.length(); i++)
    {
      //  cout << "KEY I" ;
      // cout << key[i] << endl;
      
      int index = findIndexInAlpha(&key[i]);
      // int index = key[i] - 'a';
      if(index!=-1)
        {
          // cout << "MEME" << endl;
          if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
          pCrawl->location.lat = pCrawl->location.lon = -200;
          pCrawl = pCrawl->children[index];
        }
    }
  // mark last node as leaf
  pCrawl->isEndOfWord = true;
  pCrawl->location.lat = lat;
  pCrawl->location.lon = lon;
}
struct returnSearch
{
  float* arr;
  string output;
};
string formatOutput(struct returnSearch done)
{

  string finalOutput;
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
  finalOutput+= to_string(done.arr[0]);
  finalOutput+= ", ";
  finalOutput+= to_string(done.arr[1]);
  return finalOutput;
}
returnSearch search(struct TrieNode *root, string key, float arr[])
{
  returnSearch returnMe;
  returnMe.arr = NULL;
  returnMe.output = "";
  string output = "";
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

string formatInput(string line)
{
  string input;
  for(int i = 0; i<2; i++)
    input += line[i];
  for(int i = 9; i<54;i++)
    input += line[i];
  return input;
}
float formatlat(string line)
{
  return atof(line.substr(143,9).c_str());
}
float formatlon(string line)
{
  return atof(line.substr(153,11).c_str());
}
  
int main()
{
  string placename = ""; //stored as STATE CODE + FULL NAME ex. WASeattle City
  string city;
  float lati;
  float longi;
  struct TrieNode * root = getNode();
  ifstream file;
  file.open("places2k.txt");
  string line;
  while(getline(file,line))
    {
      placename = formatInput(line);
      // string placename = line.substr(0,2)+line.substr(9,63);
      lati = formatlat(line);
      longi = formatlon(line);
      insert(root, placename, lati, longi);
    }
  
  float returnTo[2] = {0,0};
  struct returnSearch done = search(root, "NJPrinceton", returnTo);

  cout << formatOutput(done);
  return 0;
}
 
 
