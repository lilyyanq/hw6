#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0,0,0,0,0};
        int len = k.length();
        int groupIndex = 4;
        while(len > 0 && groupIndex >= 0)
        {
          int charsToProcess = std::min(len, 6); 
          unsigned long long value = 0;
          for(int i = 0; i < charsToProcess; ++i)
          {
            char c = k[len - charsToProcess + i];
            value = value * 36 + letterDigitToNumber(c);
          }
          w[groupIndex] = value;
          len -= charsToProcess;
          groupIndex--;
        }
      HASH_INDEX_T hash = 0;
      for(int i = 0; i < 5; ++i)
      {
        hash += static_cast<HASH_INDEX_T>(rValues[i]*w[i]);
      }
      for(int i = 0; i < 5; ++i) 
      {
        std::cout << "w[" << i << "] = " << w[i] << std::endl;
      }
      return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        char lower = std::tolower(letter);
        if(lower >= 'a' && lower <= 'z')
        {
          return lower - 'a';
        }
        else if(lower >= '0' && lower <= '9')
        {
          return 26 + (lower - '0');
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
