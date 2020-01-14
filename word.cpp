//
//  word.cpp
//  assignment4
//
//  Created by Hansika Sundaresan on 11/13/19.
//  Copyright © 2019 Hansika Sundaresan. All rights reserved.
//

#include "word.h"

//dafault constructor
word:: word()
{
    key = "";
    actualWords = {};
}

//constructor with string parameter
word::word(std::string& otherWord)
{
    actualWords.push_back(otherWord);
    std::string tempWord;
    for(unsigned int i =0; i < otherWord.length(); i++)
    {
        tempWord+=tolower(otherWord[i]);
    }
    std::sort(tempWord.begin(), tempWord.end());
    key = tempWord;
    //std::cout << key << " " << otherWord << " " << tempWord << std::endl;
}

//copy constructor
word:: word(const word& other)
{
    key = other.key;
    for(unsigned int i = 0; i< other.actualWords.size(); i++)
    {
        actualWords.push_back(other.actualWords.at(i));
    }
}


std::ostream& operator<<(std::ostream &out, const word &outputWord)
{
    std::vector<std::string> tempVector = outputWord.getVector();
    out<<"["<<outputWord.getKey()<<", {";
    for(unsigned int i =0; i<outputWord.getVector().size()-1; i++)
    {
        out<<tempVector.at(i)<<", ";
    }
    out<<tempVector.at(outputWord.getVector().size()-1)<<"}]"<<std::endl;
    return out;
}



