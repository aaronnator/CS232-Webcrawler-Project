#include "crawler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// FUNCTIONS -------------------------------------------------------------------





/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains(const listNode *pNode, const char *addr)
{
    if(pNode == NULL)
    {
      return 0;
    }
    else if (strcmp(pNode->addr, addr) == 0)
    {
      return 1;
    }
    return 0 + contains(pNode->next, addr);
}
    

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(  listNode *pNode, const char *addr)
{
    if(pNode->next == NULL)
    {
        listNode *endNode = malloc(sizeof(listNode));
      strncpy(endNode->addr, addr, strlen(addr)+1);
      pNode->next = endNode;
      endNode->next = NULL;
    }
    else
    {
      insertBack(pNode->next, addr);
    }
}


/*
 * prints the addresses from pNode to the end of the list,
 *   one on each line
 */
void printAddresses(const listNode *pNode)
{
   printf("%s\n", pNode->addr);
    if(pNode->next != NULL)
    {
        printAddresses(pNode->next);
    }
}

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList( listNode *pNode)
{
  if(pNode->next != NULL)
  {
      destroyList(pNode->next);
      free(pNode);
  }
  
}
  
// GETLINK ---------------------------------------------------------------------

int getLink(const char* srcAddr, char* link, const int maxLinkLength)
{
  const int bufSize = 1000;
  char buffer[bufSize];

  int numLinks = 0;

  FILE *pipe;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python getLinks.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL)
  {
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  fscanf(pipe, "%d\n", &numLinks);

  if(numLinks > 0)
  {
    int linkNum;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    for(linkNum=0; linkNum<numLinks; linkNum++)
    {
      fgets(buffer, bufSize, pipe);
      
      if(r < (linkNum + 1.0) / numLinks){
		break;
      }
    }

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';
    
    /* get rid of the newline */
    {
      char* pNewline = strchr(link, '\n');
      if(pNewline != NULL)
      {
		*pNewline = '\0';
      }
    }
  }

  pclose(pipe);

  if(numLinks > 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}