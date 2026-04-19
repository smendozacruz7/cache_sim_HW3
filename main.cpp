#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cache_class.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: " << endl;
        cout << "   ./cache_sim num_entries associativity filename" << endl;
        return 0;
    }

    unsigned entries = atoi(argv[1]);
    unsigned assoc = atoi(argv[2]);
    string input_filename = argv[3];

    ifstream input(input_filename);
    if (!input.is_open()) {
        cerr << "Could not open input file " << input_filename << endl;
        return 1;
    }

    ofstream output("cache_sim_output");
    if (!output.is_open()) {
        cerr << "Could not open output file cache_sim_output" << endl;
        return 1;
    }

    Cache cache(entries, assoc);

    unsigned long addr;
    while (input >> addr) {
        if (!cache.hit(output, addr)) {
            cache.update(output, addr);
        }
    }

    input.close();
    output.close();

    return 0;
}