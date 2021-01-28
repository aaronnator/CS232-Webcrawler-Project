#include "indexPage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


trieNode* indexPage(const char* url, int *p)
{
	trieNode * root;
	root = malloc(sizeof(trieNode));
	root->children = NULL;
	root->letter = ' ';
	root->childrenCount = 0;
	root->wordCount = 0;  

	char resultBuffer[BUFFER_SIZE]; //contains the web page contents
	getText(url, resultBuffer, BUFFER_SIZE);
	printf("%s\n", url);
	int i = 0;

	//clean up resultBuffer (remove non-alpha chars and make lowercase)

	while(i<BUFFER_SIZE && resultBuffer[i] != '\0')
	{

		if (isalpha(resultBuffer[i]))
		{
			//change to lowercase
			resultBuffer[i] = tolower(resultBuffer[i]);
		}

		else
		{
			resultBuffer[i] = ' ';
		} 
		i++;
	}
	i=0;
	char* pch;
	//while resultBuffer has more words, scan resultBuffer for the next word
	//Tokenize the buffer into pch
	pch = strtok(resultBuffer, " ");
	while(pch != NULL)
	{
		printf("\t%s\n", pch);
		addWordOccurrence(pch, strlen(pch), root, p);
		pch = strtok (NULL, " ");
	}  

	return root;

}

 
int addWordOccurrence(const char* word, const int wordLength, trieNode* root, int *p)
{

	int result = 0;
	if ((*word == root->letter) && (wordLength == 1))
	{
		root->wordCount++;
		*p += root->wordCount;
		return 1;
	}  

	int i = 0;
	int childI; 
	if (root->letter == ' ' && root->childrenCount == 0)
	{
		
	}


	else if (root->letter == ' ')
	{
		for(childI = 0; childI < root->childrenCount; childI++)
		{
			if(*word == (root->children[childI])->letter && wordLength > 0)
			{
				result = addWordOccurrence((word), (wordLength), root->children[childI], p);
				if (result == 1)
					return 1;
			}

		}

	}

	else
	{	
		for(childI = 0; childI < root->childrenCount; childI++)
		{
			if(*(word+1) == (root->children[childI])->letter && wordLength > 0 && result == 0)
			{
				result = addWordOccurrence((word+1), (wordLength-1), root->children[childI], p);

				if (result == 1)
					return 1;
			}

		}

	}


	if (root->letter == ' ')
	{
		struct trieNode* newChild;
		root->childrenCount++;
		root->children = realloc(root->children, sizeof(trieNode) * root->childrenCount);
		newChild = malloc(sizeof(trieNode));
		newChild->wordCount = 0;
		newChild->childrenCount = 0;
		newChild->children = NULL;
		newChild->letter = word[0];
		root->children[root->childrenCount-1] = newChild;
		result = addWordOccurrence((word), (wordLength), newChild, p);
		if (result == 1)
			return 1;
	}


	else
	{
		struct trieNode* newChild;
		root->childrenCount++;
		root->children = realloc(root->children, sizeof(trieNode) * root->childrenCount);
		newChild = malloc(sizeof(trieNode));
		newChild->wordCount = 0;
		newChild->childrenCount = 0;
		newChild->children = NULL;
		newChild->letter = word[1];
		root->children[root->childrenCount-1] = newChild;
		result = addWordOccurrence((word+1), (wordLength-1), newChild, p);
		if (result == 1)
			return 1;

	}


return result;

}

char* printTrieContents(trieNode root, char* buffer)
{
  
  int length;
  if(root.letter != ' ' && root.letter != '\0') {
    length = strlen(buffer) + 2;
    buffer = realloc(buffer, sizeof(char)* length);
    buffer[length-2] = root.letter;
    buffer[length-1] = '\0';
    
    if(root.wordCount > 0 && strlen(buffer) > 0) {
      printf("%s: %d\n", buffer, root.wordCount);
    }
  }
  
  //If the current node has children
  
  if(root.childrenCount > 0) {
    int i;
    
    //sorting children
    trieNode* temp = NULL;
    
    for(i = 0; i < root.childrenCount - 1; i++) {
      int j = i;
      for(j = i + 1; j < root.childrenCount; j++) {
        if(root.children[i]->letter > root.children[j]->letter) {
          
          temp = root.children[i];
          root.children[i] = root.children[j];
          root.children[j] = temp;
          
        }
      }
    }
    
    //Loop for each child in the children array
    
    for(i = 0; i < root.childrenCount; i++) {
      buffer = printTrieContents(*(root.children[i]), buffer);
    }
  }
  //remove last char from top of trie
  length = strlen(buffer);
  buffer[length - 1] = '\0';
  
  return buffer;
  
}

int freeTrieMemory(trieNode* root)
{
  
  while(root->childrenCount > 0) {
    if(freeTrieMemory((root->children[root->childrenCount-1])) == 1) {
      root->childrenCount--;
    }else {
      printf("Error");
    }
  }
  
  char letter = root->letter;
  free(root->children);
  free(root);
  
  return 1;
}

void joshSearch(trieNode* joshNode, char* werd, int length, int * count) 
{
    int i = *werd - 'a';
    if(length == 0)
    {
        *count = joshNode->wordCount;
        //printf("Count inside treeSearch: %i\n", *count);
        return;
    }
    else
    {
        if(joshNode == NULL)
        {
            *count = 0;
            return;
        }
        if(joshNode->children[i] != NULL)
        {
            joshSearch(joshNode->children[i], ++werd, --length, count);
        }
    }
}
/* You should not need to modify this function --------------------------------------------------------------------*/
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
