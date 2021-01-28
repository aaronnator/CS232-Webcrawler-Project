// uhhh here's where the code goes

#include"crawler.h"
#include"indexPage.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int checkString(char* jim);
// idk where this came from but if you look at the other .c and the .h files, it actually declares some functions and structs there
// when they get included the code is basically appended to the top of this code


// trieNode* indexPage(const char* url, int* totalTerms);

// trieNode* indexPage(const char* url, int* totalTerms)
// {
// 	trieNode * root;
// 	root = malloc(sizeof(trieNode));
// 	root->children = NULL;
// 	root->letter = ' ';
// 	root->childrenCount = 0;
// 	root->wordCount = 0;  

// 	char resultBuffer[BUFFER_SIZE]; //contains the web page contents
// 	getText(url, resultBuffer, BUFFER_SIZE);
// 	printf("%s\n", url);
// 	int i = 0;

// 	//clean up resultBuffer (remove non-alpha chars and make lowercase)

// 	while(i<BUFFER_SIZE && resultBuffer[i] != '\0')
// 	{

// 		if (isalpha(resultBuffer[i]))
// 		{
// 			//change to lowercase
// 			resultBuffer[i] = tolower(resultBuffer[i]);
// 		}

// 		else
// 		{
// 			resultBuffer[i] = ' ';
// 		} 
// 		i++;
// 	}
// 	i=0;
// 	char* pch;
// 	//while resultBuffer has more words, scan resultBuffer for the next word
// 	//Tokenize the buffer into pch
// 	pch = strtok(resultBuffer, " ");
// 	while(pch != NULL)
// 	{
// 		printf("\t%s\n", pch);
// 		addWordOccurrence(pch, strlen(pch), root);
// 		pch = strtok (NULL, " ");
// 	}  

// 	return root;

// }

int main(int argc, char **argv)
{
	int termz = 0;
	char *url = argv[1];
	char url2[2000];
	int MAX_N = atoi(argv[2]);
	int seed = atoi(argv[3]);
	char line[2000];
	srand(seed);
	
	//printf("\t \t \targs:%s,%d.\n", url, MAX_N);
	FILE *urlFile;
	urlFile = fopen(url,"r");
	//printf("\t \t \tfile: %s  opened.\n", url);
	int n = 0;
	int hopsLimit = 0;
	
	listNode *pListStart;
	pListStart = malloc(sizeof(listNode));
	pListStart->next = NULL;
	char lank[2000];
	char newUrl[2000];
	printf("Indexing...\n");
	
	trieNode* rootStructure[MAX_N];
	
	while(fgets(line,2000,urlFile) && n < MAX_N)
	{	// Get line, print line
		//fgets(line, 2000, urlFile);
		//printf("Line: |%s|\n", line);
		
		//get first token
		char* tokens = strtok(line, " ");
		strncpy(url2,tokens,2000);
		//printf("|%s|\n", url);
		// get second token
		tokens = strtok(NULL, " ");
		hopsLimit = atoi(tokens);
		//printf("|%d|\n", hopsLimit);
		
		int hopNum = 0;
		 
		while(1)
		{
			if(!contains(pListStart,url2))
			{
				insertBack(pListStart,url2);
				rootStructure[n] = indexPage(url2,&termz);
				n++;
			}
		
			hopNum++;
			
			if(hopNum <= hopsLimit && n < MAX_N)
			{
				int isValid = getLink(url2,lank,150);
				strncpy(url2, lank, 2000);
				if(!isValid)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
		
		//n++; // delete this when the pg.2 pseudocode segment is complete.
		//printf("n: %d\n", n);
	}
	
	// making the user say yes--------------------------------YAS
	int userSaysYes=1;
	while(userSaysYes)
	{
		
		printf("\nEnter a web query: ");
		scanf("%d",&userSaysYes);
		fgets(line, 2000,stdin);
		
		int intJared = strlen(line);
		line[intJared-1] = '\0';
		
		
		printf("Query is \"%s\".\n",line);
		//if(line[0] == '\0'){printf("jeremy\n");}
		int jimCases = checkString(line);
		//printf("%d\n", jimCases);
		
		
		char* userTokens = strtok(line, " ");
		
		while (userTokens != NULL)
		{
			int userTokensLen = strlen(userTokens);
			double idfScore = idfCalculate(termz,userTokensLen,rootStructure,userTokens);
			printf("IDF (%s) : %lf", userTokens, idfScore);
		}
		
	}
	
	fclose(urlFile);
}


int checkString(char* jim)
{
	int i = 0;
	int length = strlen(jim);
	
	for(; i < length; i++,jim++)
	{
		//printf("%d\n",i);
		if(*jim == 32 || *jim == '\n' || *jim == '\0')
		{
			
		}
		else if(*jim < 97 || *jim > 122 )
		{
			return 0;
		}
	}
	
	return 1;
}


