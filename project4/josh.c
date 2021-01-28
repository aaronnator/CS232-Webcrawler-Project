#include "josh.h"


double idfCalculate(int termz, int length, trieNode *theListNodeArgument, char* werd)
{
    int webWerdCount = 0;
    int k = 0;
    //void joshSearch(trieNode joshNode, char  werd, int length, int * count) 
    
    
    
    for(;k <= length;k++,theListNodeArgument++)
    {
        int isKarlInWebsite = 0;
        int werdLength = strlen(werd);
        joshSearch(theListNodeArgument,werd,werdLength,&isKarlInWebsite);
         
        if(isKarlInWebsite > 0)
        {
            webWerdCount++;
        }
        //leave all the space for room
        
        
        
        
        
        
        
        
        
    }
    // same here you need the extra room
    
    
    
// for    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // activities.
    return log((1.0+termz)/(1+webWerdCount));
}
