// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


//recursive helper function 
//go through all letters in the string putting in all possible combinations for that spot if it is '-'
//skip the letter if it is already set
std::set<std::string> recursiveHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict){
  std::set<std::string> matchingWords;
    
  size_t dashIndex = in.find('-');
  
  // if there was a dash
  if (dashIndex != std::string::npos)
  {
    //set to each letter
    for (char j = 'a'; j <= 'z'; j++)
    {
      std::string inCopy = in;
      inCopy.at(dashIndex) = j;
      // find returns the index of the character in the string
      size_t floatingIndex = floating.find(j);
      // if the character std::string::npos
      if (floatingIndex != std::string::npos)
      {
        //remove from floating
        std::string newFloating = floating;
        // erases at a given index a certain number of characters
        newFloating.erase(floatingIndex,1);

        //recurse with new in and floating
        std::set<std::string> tempSet = recursiveHelper(inCopy, newFloating, dict);
        matchingWords.insert(tempSet.begin(), tempSet.end());
      }

      else 
      {
        //recurse with new in and floating
        std::set<std::string> tempSet =  recursiveHelper(inCopy, floating, dict);
        matchingWords.insert(tempSet.begin(), tempSet.end());
      }
    }

    return matchingWords;
  }
  
  else // we didn't find a dash
  {
    //return an empty set
    if (floating.empty()!= true)
    {
      return std::set<std::string>();
    }
    
    //check if word is in the dictionary
    if (dict.find(in) != dict.end())
    {
      //return the word if it is
      return std::set<std::string>({in});
    }
    
  }
  
  return std::set<std::string>();
}





// Definition of primary wordle function

//in is input string
//floating is yellow letters
//dict is all possible dictionary words
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
  
  //return call to the recursive helper
  
  return recursiveHelper(in, floating, dict);
  

}



