#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 32;
const int RETURN_ARR_SIZE = 2;
struct position{
  float lon;
  float lat;
};

struct TrieNode
{
  struct TrieNode *children[ALPHABET_SIZE];
  // isEndOfWord is true if the node
  // represents end of a word
  bool isEndOfWord;
  position * location;
};
struct TrieNode *getNode(void)
{
  struct TrieNode *pNode =  new TrieNode;

  pNode->isEndOfWord = false;

  for (int i = 0; i < ALPHABET_SIZE; i++)
    pNode->children[i] = NULL;

  return pNode;
}
void insert(struct TrieNode *root, string key, float lat, float lon)
{
  struct TrieNode *pCrawl = root; 
  for (int i = 0; i < key.length(); i++)
    {
      int index = key[i] - 'a';
      if (!pCrawl->children[index])
        pCrawl->children[index] = getNode();
      pCrawl->location->lat = pCrawl->location->lon = -200;
      pCrawl = pCrawl->children[index];
    }
  // mark last node as leaf
  pCrawl->isEndOfWord = true;
  pCrawl->location->lat = lat;
  pCrawl->location->lon = lon;
}
float* search(struct TrieNode *root, string key, float arr[])
{
  arr[0]=arr[1]=-1;
  struct TrieNode *pCrawl = root;
  // struct TrieNode *returnMe = NULL;
  for (int i = 0; i < key.length(); i++)
    {
      int index = key[i] - 'a';
      if (!pCrawl->children[index])
        return arr;      
      pCrawl = pCrawl->children[index];
    }
  if (pCrawl != NULL && pCrawl->isEndOfWord)
    {
      arr[0] = pCrawl->location->lat;
      arr[1] = pCrawl->location->lon;
      return arr;
    }
  return arr;
}
int main()
{
  // Input keys (use only 'a' through 'z'
  // and lower case)
  
  string placename[] = {""}; //stored as STATE CODE + FULL NAME ex. WASeattle City
  string city;
  float lati;
  float longi;
  struct TrieNode * root = getNode();
  ifstream file;
  file.open("places2k.txt");
  string line;
  while(getline(file,line))
    {
      placename[0] = "";
      for(int i = 0; i<3; i++)
        placename[0] += line[i];
      for(int i = 143; i<153;i++)
        placename[0] += line[i];
      
      // string placename = line.substr(0,2)+line.substr(9,63);
      lati = atof(line.substr(143,9).c_str());
      longi = atof(line.substr(154,10).c_str());
      insert(root, placename[0], lati, longi);
    }
      
  



  // string keys[] = {"the", "a", "there",
  //               "answer", "any", "by",
  //               "bye", "their" };

  //  int n = sizeof(keys)/sizeof(keys[0]);
  
  // struct TrieNode *root = getNode();
  
  // Construct trie
  // for (int i = 0; i < n; i++)
  //  insert(root, keys[i]);

  // Search for different keys
  // search(root, "NJPrinceton bourough")? cout << "Yes\n" :
  //  cout << "No\n";
  // search(root, "these")? cout << "Yes\n" :
  //  cout << "No\n";
  return 0;
}
 
 
