#ifndef indexPageh
#define indexPageh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE (26)
#define BUFFER_SIZE (300000)
// this is the definition of a node. the specific character, the count for the character, and the link to the child node
typedef struct trieNode
{ 
  
  char letter;
  struct trieNode** children;
  int wordCount;
  int childrenCount;
  
  
}trieNode;
// PROTOTYPES ---------------------------------------------------------------------------
/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */
trieNode* indexPage(const char* url, int *p);
// Trie* indexPage(const char* url);
int addWordOccurrence(const char* word, const int wordLength, trieNode* root, int *p);
// int addWordOccurrence(const char* word, const int wordLength, trieNode* root);
char* printTrieContents(trieNode root, char* buffer);
// char* printTrieContents(trieNode root, char* buffer);
int freeTrieMemory(trieNode* root);

void joshSearch(trieNode* joshNode, char* werd, int length, int * count);
//Node *getNode(void);

int getText(const char* srcAddr, char* buffer, const int bufSize);


#endif