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
		//h(k) 
        HASH_INDEX_T val = 0;
        HASH_INDEX_T w[5];
        for (int i = 0; i < 5; i++)
        {
            w[i] = 0;  //initialize
        }
        calculateW(k, w); //w
        for (int i = 0; i < 5; i++)
        {
            val += rValues[i] * w[i]; //calculate h(k)
        }
        return val;
    }
   
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
		int val = 0;
		if (isdigit(letter)) val = (int)letter - 22; //0-9 conversion
		else
		{
			if (isupper(letter)) letter += 32;  //convert to lowercase 
			val = (int)letter - 97;  //a-z conversion
		}
		return static_cast<HASH_INDEX_T>(val);
    }

     //base-36 to decimal conversion
	void calculateW(const std::string& k, HASH_INDEX_T finalW[5]) const //output no more than 5 characters
	{
        size_t strlen = k.size();
        size_t cap = 0; 
        while (strlen != cap) 
        {
            size_t lengthOfSubStr = strlen - cap;
            if (lengthOfSubStr < 6)  
            {
                HASH_INDEX_T w = 0;
                for (size_t i = 0; i < lengthOfSubStr; i++)
                {
                    w = letterDigitToNumber(k[i]) + w*36;
                }
                finalW[4 - cap/6] = w;
                cap = strlen;
            }
            else
            {
                HASH_INDEX_T w = 0;
                for (size_t i = lengthOfSubStr - 6; i < lengthOfSubStr; i++)
                {
                    w = letterDigitToNumber(k[i]) + w*36;
                }
                finalW[4 - cap/6] = w;
                cap += 6;
            }
        }
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
