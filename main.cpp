#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <windows.h>

using std::vector;
using std::ofstream;
using std::cout;
using std::endl;
using std::map;

vector<int> _primes = {1, 2, 3, 5}; //Store previously calculated primes, initialize with the first few.
unsigned int calculatedUpTo = 5; //Keep track of how far we've calculated

//Find if a specific number is prime, without cache checking
bool numIsPrime(int candidate) {
    //All numbers except primes can be made up of smaller primes.
    //Thus, check for divisibility of all smaller primes. If it is not divisible,
    //it is a prime.

    //Check if a number is divisible by any of the lower primes
    for (int j = 1; j < _primes.size(); ++j) { //Need to start at j = 1 because _primes[0] is 1
        if (candidate % _primes[j] == 0) {
            return false; //Not a prime
        }
    }

    return true;
}
//Screen all numbers up the 'limit' for primes
void calculatePrimesUpTo(int limit) {
    //Run through all the numbers between the current highest calculation and the desired
    //highest calculation
    while (calculatedUpTo < limit) {
        if (numIsPrime(++calculatedUpTo)) {
            //Number is a prime.
            _primes.push_back(calculatedUpTo);
        }
    }
}
//Find if a number is prime, using cache checking and screening all numbers before it
bool isPrime(int candidate) {
    //If we haven't already calculated this, do so
    if (candidate > calculatedUpTo) {
        calculatePrimesUpTo(candidate);
    }

    //Return true if the prime is on the list, false otherwise.
    return find(_primes.begin(), _primes.end(), candidate) != _primes.end();
}

map<int, int> _howManyFactors;
int howManyFactors(unsigned int inputNumber) {
    if (inputNumber == 0) {
        return 0;
    }

    //Check for previously cached results.
    if (_howManyFactors.find(inputNumber) != _howManyFactors.end()) {
        //Found cached result.
        return _howManyFactors[inputNumber];
    }

    //No cached results. Calculate.
    int numFactors = 1;
    int prime;
    int power;
    for (int i = 1, numPrimes = _primes.size(); i < numPrimes; ++i) { //Do not include the first prime
        power = 0;
        prime = _primes[i];
        while (inputNumber % prime == 0) {
            inputNumber /= prime;
            power++;
        }

        numFactors *= power + 1;

        if (inputNumber == 1) {
            break;
        }

        if (i + 1 == numPrimes) {
            calculatePrimesUpTo(calculatedUpTo + 100);
            numPrimes = _primes.size();
        }
    }

    //Cache calculated result.
    _howManyFactors[inputNumber] = numFactors;

    return numFactors;
}
vector<unsigned int> highlyComposites = {1, 2, 4};
unsigned int HCCalculatedUpTo = 4;
bool numIsHighlyComposite(unsigned int candidate) {
    return howManyFactors(candidate) > howManyFactors(highlyComposites[highlyComposites.size() - 1]);
}
void HCCalculateUpTo(unsigned int limit) {
    while (limit > HCCalculatedUpTo) {
        if (numIsHighlyComposite(++HCCalculatedUpTo)) {
            highlyComposites.push_back(HCCalculatedUpTo);
        }
    }
}
bool isHighlyComposite(unsigned int candidate) {
    if (candidate > HCCalculatedUpTo) {
        HCCalculateUpTo(candidate);
    }

    return find(highlyComposites.begin(), highlyComposites.end(), candidate) != highlyComposites.end();
}
bool isHighlyCompositeOld(unsigned int candidate) {
    int mostFactors = 0;

    for (int i = 0; i < candidate; i++) { // Loops `candidate` times. `i` is a number below `candidate`
        //Extracted variable here. Previously the function was being call twice. Redundantly.
        int factors = howManyFactors(i);
        if (factors >= mostFactors) { // If `i` is more composite than all numbers below it
            mostFactors = factors; // Make the number of factors `i` has the most composite number so far
        }
    }

    //I eliminated an if statement here, as it wasn't really necessary.
    //Maybe it was for code readability, but meh.. CLion was bugging me to simplify it. I caved.
    return howManyFactors(candidate) > mostFactors;
}

int main() {
    //Mimic output into a file, for easy copy-paste.
    ofstream fout("bakers_output.txt", ofstream::app);
    fout << endl << endl << "----------- New Calculation -------------" << endl;

    int numberOfItemsInSeries = 40;
    for (unsigned int i = 0, j = 0; j < numberOfItemsInSeries; i++) { // Loops for how many numbers to find
        if (isPrime(i) && isHighlyComposite(i - 1)) { // If bakery number
            j++;

            cout << j << ".\t" << i << endl;
            fout << j << ".\t" << i << endl;
        }
    }
    fout << endl;
}