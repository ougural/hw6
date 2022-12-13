#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;
using namespace std;

struct MyStringHash {
    HASH_INDEX_T rValues[5]{ 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
			// convert string add values to initially 0'd array
			long long length = k.length();
			long long convStr[30];
			for(int i = 0; i < 30; i++){
				convStr[i] = 0;
			}
			int ctr = 0;
			for(int i = length - 1; i >= 0; i--){
				convStr[ctr] = letterDigitToNumber(k[i]);
				ctr++;
			}
			// iterate through conv, 
			unsigned long long w[5];
			unsigned long long totalForW = 0;
			int ctrW = 4;
			for(int i = 0; i < 30; i++){
				if((i + 1) % 6 == 0){
					totalForW = ((((convStr[i]*36+convStr[i-1])*36+convStr[i-2])*36+convStr[i-3])*36+convStr[i-4])*36+convStr[i-5];
					w[ctrW] = totalForW;
					ctrW--;
				}
			}
			// calculate h(k)
			unsigned long long h = 0;
			for(int i = 0; i < 5; i++){
				h += rValues[i] * w[i];
			}
			return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {	
			// if letter is an integer
			if(letter > 47 && letter < 58){
				return letter - 22;
			}
			// if letter is upper case
			else if(letter > 64 && letter < 91){
				return letter - 65;
			}
			// if letter is lower case
			else{
				return letter - 97;
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
