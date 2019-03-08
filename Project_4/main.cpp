//
//  main.cpp
//  Project_4
//
//  Created by Yunus Chang on 3/6/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Trie.h"
#include "provided.h"

void test1()
{
    Trie<int> tree;
    cout << 'i' << endl;
    tree.insert("AAA", 42);
    tree.insert("AAA", 43);
    tree.insert("ANA", 44);
    cout << "inserted" << endl;
    vector<int> vec = tree.find("AAA", false);
    cout << vec[0] << endl;
    cout << vec[2] << endl;
}

void test2()
{
    //Specify the full path and name of the gene data file on your hard drive.
    string filename = "/Users/yunus/Documents/UCLA_CSE/CS_32/Project_4/data/Ferroplasma_acidarmanus.txt";
    //Open the data file and get a ifstream object that can be used to read its contents.
    ifstream strm(filename);
    if(!strm)
    {
        cout << "Cannot open " << filename << endl;
        return;
    }
    vector<Genome> vg;
    bool success = Genome::load(strm, vg);  //Load the data via the stream.
    if(success)
    {
        cout << "Loaded " << vg.size() << " genomes successfully:" << endl;
        for    (int k = 0; k != vg.size(); k++)
            cout << vg[k].name() << endl;
    }
    else
        cout << "Error loading genome data" << endl;
    string fragment;
    assert(vg[0].extract(0,10,fragment) == true);
    cout << fragment << endl;
    assert(vg[0].extract(-1,9,fragment) == false);
}

void test3()
{
    Genome a("genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
    Genome b("genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
    Genome c("genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");
    GenomeMatcher z(3);
    z.addGenome(a);z.addGenome(b);z.addGenome(c);
    bool result;
    vector<DNAMatch> matches;
    string fragment;
    result = z.findGenomesWithThisDNA("GAAG", 4, true, matches);
    assert(result == true);
    for(int i = 0;i < matches.size();i++)
    {
        cout << matches[i].genomeName << " " << matches[i].length << " " << matches[i].position << endl;
    }
    result = z.findGenomesWithThisDNA("GAATAC", 6, false, matches);
    assert(result == true);
    for(int i = 0;i < matches.size();i++)
    {
        cout << matches[i].genomeName << " " << matches[i].length << " " << matches[i].position << endl;
    }
}

int main(int argc, const char * argv[])
{
//    test1();
//    test2();
    test3();
}
