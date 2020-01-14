//
//  word.hpp
//  assignment4
//
//  Created by Hansika Sundaresan on 11/13/19.
//  Copyright © 2019 Hansika Sundaresan. All rights reserved.
//

#ifndef word_h
#define word_h

#include <stdio.h>
#include <vector>
#include <algorithm>
#include "binarySearchTree.h"

class word
{
private:
    std::string key;
    std::vector<std::string> actualWords;
public:
    word();
    word(std::string& otherWord);
    word(const word& other);
    
    //equals overloading operator
    bool operator==(const word& entry) const
    {
        return key == entry.key;
    }
    
    //not equal overloading operator
    bool operator!=(const word& entry) const
    {
        return key != entry.key;
    }
    
    //less than overloading operator
    bool operator<(const word& entry) const
    {
        return key < entry.key;
    }
    
    //less than or equal to overloading operator
    bool operator<=(const word& entry) const
    {
        return key <= entry.key;
    }
    
    //greater than overloading operator
    bool operator>(const word& entry) const
    {
        return key > entry.key;
    }
    
    //greater than or equal to overloading operator
    bool operator>=(const word& entry) const
    {
        return key >= entry.key;
    }

    //get method for key
    std::string getKey() const
    {
        return key;
    }
    
    //gt method for vector Actual Words
    std::vector<std::string> getVector() const
    {
        return actualWords;
    }
    
    //updates actualWords to include more unscarmbled words
    static void update(word &exsitingItem, const word &newItem)
    {
        for(const auto& item: newItem.getVector())
        {
            exsitingItem.actualWords.push_back(item);
        }
    }
    
};





#endif /* word_hpp */
