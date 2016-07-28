#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

const int ALPHA_SIZE = 26;
const string ACT_FREQ = "zqxjkvbpygfwmucldrhsnioate";
const string FILENAME = "text.txt";

//Comparitor for sorting by the second value of a pair
struct Comparitor {
    bool operator()(const pair<char, int> &pair1, const pair<char, int> &pair2) {
        return pair1.second < pair2.second;
    }
};


//Prints the pairs of the letter and the frequency
void printPairs(const vector<pair<char, int> > & vect) {
    for (char i = 0; i < 26; ++i) {
        cout << vect[i].first << ": " << vect[i].second << endl;
    }
    cout << endl;
}


//Finds the frequencies of all the alphabit characters in the file named fileName and sorts by frequency
void findFreq(string fileName, vector<pair<char, int> >& vect) {
    ifstream ins;
    ins.open(fileName);
    char nextChar;
    while (ins >> nextChar) {
        if (isAlpha(nextChar)) {
            ++(vect[nextChar - 'a'].second);
        }
    }
    ins.close();
    sort(vect.begin(), vect.end(), Comparitor());
}

//Actually "Decodes". This decode function goes exactly by the 
//    english frequency chart found on wikipedia 
//    with a large text file, it'll get you close but not exact
//    prints out the decoding stream
void decode(string fileName, unordered_map<char, char> & keyMap) {
    long long counter = 0;
    ifstream ins(fileName);
    char nextChar = ' ';
    while (ins >> nextChar) {
        cout << keyMap[nextChar];
        if (counter % 100 == 0) {
            cout << endl;
        }
        ++counter;
    }
    ins.close();
}

int main() {
    //Initialize freq vector
    vector<pair<char, int> > freqCount(26);
    for (int i = 0; i < ALPHA_SIZE; ++i) {
        freqCount[i].first = char(i + 'a');
        freqCount[i].second = 0;
    } 
    
    findFreq(FILE_NAME, freqCount);

    printPairs(freqCount);

    unordered_map<char, char> decodingKey;
    decodingKey.reserve(ALPHA_SIZE);
    
    //Build Map: Hash map where key == encryptedChar, and val == englishLetter
    //Can change this map by messing around with the string ACT_FREQ
    for (int i = 0; i < ALPHA_SIZE; ++i) {
        decodingKey.insert(pair<char, char>(freqCount[i].first, ACT_FREQ[i]));
    }

    decode(FILE_NAME, decodingKey);
}

