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
        unsigned long long w[5] ={0};
        int len = k.length();

        for(int i = len, wi = 4; i > 0; i -= 6, wi--){
            unsigned long long temp[6] ={0};
            int group_len = std::min(6 ,i);
            for(int j = 0; j < group_len; ++j){
                temp[j] = letterDigitToNumber(k[i - group_len + j]);
            }

            unsigned long long num = 0;
            for(int j = 0; j < group_len; j++){
                num = num * 36 + temp[j];
            }
            w[wi] = num;
        }
        return w[0]*rValues[0] + w[1]*rValues[1] + w[2]*rValues[2] + w[3]*rValues[3] + w[4]*rValues[4];
    }

    



    

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        if (letter >= 'A' && letter <= 'Z') {
            letter = letter + 32;
        }

        if (letter >= 'a' && letter <= 'z') {
            return letter - 97;
        }

        else if (letter >= '0' && letter <= '9') {
            return letter - 22;
        }
        return -1;
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
