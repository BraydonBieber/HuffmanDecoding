/*
*  Name: Braydon Bieber
* myWSU: removed
* Description: Reading in encoded Huffman file and Huffman scheme, outputting decoded file 
*              Fixed Hw7 to get files outputting properly for this program
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

void decodeHuffman(string fnames[], unordered_map<string, int> hash) {
    std::ifstream ifile(fnames[0], std::ios::binary | std::ios::in);
    std::ofstream ofile(fnames[1], std::ios::binary | std::ios::out);
    if (!ifile || !ofile) {
        std::cerr << "\n Resource Unavailable\n";
        exit(1);
    }
    
    while (ifile) {
        bool Decoded = false;
        string key;
        while (ifile && !Decoded) {
            char temp = ifile.get();
            if (temp == '0' || temp == '1') {
                key += temp;
                Decoded = hash.count(key);
            }
        }
        char write = hash[key];
        ofile << write;
    }
}


unordered_map<string, int> loadScheme(string fname) {
    std::ifstream file(fname, std::ios::binary | std::ios::in);
    unordered_map<string, int> result;
    if (!file) {
        std::cerr << "\nResource unavailable\n";
        exit(1);
    }

    while (file) {
        int chr; 
        char temp = '0';
        file >> chr;
        string value;
        while (temp != '\n' && file) {
           
            temp = file.get();
            if (temp == '1' || temp == '0') {
                value += temp;
            }
        }
        result[value] = chr;
    }
    file.close();
    return result;
}


int main()
{
    string fnames[] = { "huff.sch", "pride.huff", "pride_decoded.txt" };
    unordered_map<string, int> scheme = loadScheme(fnames[0]);
    decodeHuffman(&fnames[1], scheme);
    return 0;
}


/*
ToDo
-From your code for hw 7, output Huffman coding scheme to a file (huff.sch).
-Open the scheme file, load coding scheme into a certain data structure. 
-Open the encoded file, use coding scheme to decode the encoded file. 
-Output plain text(after decoding) to pride_decoded.txt. 

Note
-There are three text files involved:
o huff.sch for coding scheme.
o pride.huff for encoded content. This file should be all 0s and 1s. 
o pride_decoded.txt for decoded content. This file should be inplain English.
*/