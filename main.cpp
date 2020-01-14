//
//  main.cpp
//  assignment4
//
//  Created by Hansika Sundaresan on 11/13/19.
//  Copyright © 2019 Hansika Sundaresan. All rights reserved.
//

#include <iostream>
#include<vector>
#include <fstream>
#include "binarySearchTree.h"
#include "word.h"

void printWord(const word& entry)
{
    if(entry.getVector().size() > 1)
    {
        std::cout<<"maps to words: ";
    }
    else
        std::cout<<"maps to word: ";
    
    for(const auto& item :entry.getVector())
    {
        std::cout<<item<<" ";
    }
    std::cout<<std::endl;
}

int main()
{
    binarySearchTree<word> tree;
    std::string input;
    std:: ifstream dictFile;
    dictFile.open("english_words.txt");
    
    while(dictFile>>input)
    {
        word insertWord(input);
        tree.insert(insertWord, &word::update);
    }
    
    std::cout<<"Test of find words"<<std::endl<<std::endl;
    std::cout<<"The dictionary has been built with "<<tree.size()<<" keys in the dictionary"<<std::endl<<std::endl;
 
    while(true)
    {
        std::string mixedWord;
        std::cout<<" Word to unscramble (quit-now to stop):"<<std::endl;
        std::cin>>mixedWord;
        if(mixedWord == "quit-now") {
            break;
        }
        word insertWord(mixedWord);
        std::cout<<"Scrambled word "<<mixedWord<<" ";
        if(tree.find(insertWord, &printWord))
        {
            
            
        }
        else
        {
            std::cout<<"was not found"<<std::endl;
        }
        
        
        
    }
    return 0;
}
