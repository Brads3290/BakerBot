#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

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
int howManyFactors(int inputNumber) {
    //Check for previously cached results.
    if (_howManyFactors.find(inputNumber) != _howManyFactors.end()) {
        //Found cached result.
        return _howManyFactors[inputNumber];
    }

    //No cached results. Calculate.
    int numOfFactors = 0;
    for (int i = 1; i <= inputNumber; i++) { // Look for factors
        if (inputNumber % i == 0) { // divides without remainder
            numOfFactors++; // Found another factor of `inputNumber`
        }
    }

    //Cache calculated result.
    _howManyFactors[inputNumber] = numOfFactors;

    return numOfFactors;
}

bool isHighlyComposite(int candidate) {
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
    for (int i = 0, j = 0; j < numberOfItemsInSeries; i++) { // Loops for how many numbers to find
        if (isPrime(i) && isHighlyComposite(i - 1)) { // If bakery number
            j++;

            cout << j << ".\t" << i << endl;
            fout << j << ".\t" << i << endl;
        }
    }
    fout << endl;
}