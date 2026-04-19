#include "cache_class.h"
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

Entry::Entry() {
    valid = false;
    tag = 0;
    ref = -1;
}

Entry::~Entry() {
}

void Entry::display(ofstream& outfile) {
    outfile << "[valid=" << valid << ", tag=" << tag << ", ref=" << ref << "]";
}

Cache::Cache(int _num_entries, int _assoc) {
    assoc = _assoc;
    num_entries = _num_entries;
    num_sets = num_entries / assoc;

    entries = new Entry*[num_sets];
    for (int i = 0; i < num_sets; i++) {
        entries[i] = new Entry[assoc];
    }
}

Cache::~Cache() {
    for (int i = 0; i < num_sets; i++) {
        delete[] entries[i];
    }
    delete[] entries;
}

void Cache::display(ofstream& outfile) {
    for (int i = 0; i < num_sets; i++) {
        outfile << "Set " << i << ": ";
        for (int j = 0; j < assoc; j++) {
            entries[i][j].display(outfile);
            outfile << " ";
        }
        outfile << endl;
    }
}

int Cache::get_index(unsigned long addr) {
    return addr % num_sets;
}

int Cache::get_tag(unsigned long addr) {
    return addr / num_sets;
}

unsigned long Cache::retrieve_addr(int way, int index) {
    return entries[index][way].get_tag() * num_sets + index;
}

bool Cache::hit(ofstream& outfile, unsigned long addr) {
    int index = get_index(addr);
    int tag = get_tag(addr);

    for (int way = 0; way < assoc; way++) {
        if (entries[index][way].get_valid() &&
            entries[index][way].get_tag() == (unsigned)tag) {
            outfile << addr << " : HIT" << endl;
            return true;
        }
    }

    outfile << addr << " : MISS" << endl;
    return false;
}

void Cache::update(ofstream& outfile, unsigned long addr) {
    int index = get_index(addr);
    int tag = get_tag(addr);

    static int global_ref = 0;

    for (int way = 0; way < assoc; way++) {
        if (!entries[index][way].get_valid()) {
            entries[index][way].set_valid(true);
            entries[index][way].set_tag(tag);
            entries[index][way].set_ref(global_ref++);
            return;
        }
    }

    int victim = 0;
    int smallest_ref = entries[index][0].get_ref();

    for (int way = 1; way < assoc; way++) {
        if (entries[index][way].get_ref() < smallest_ref) {
            smallest_ref = entries[index][way].get_ref();
            victim = way;
        }
    }

    entries[index][victim].set_tag(tag);
    entries[index][victim].set_valid(true);
    entries[index][victim].set_ref(global_ref++);
}