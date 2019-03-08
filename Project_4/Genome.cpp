#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_size;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
    m_size = sequence.size();
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    string name;
    string sequence;
    char c;
    genomeSource.get(c);
    if(c == '>')
    {
        getline(genomeSource, name);
        name = name.substr(1,name.length());
        if(name == "")
            return false;
    }
    else
        return false;
    while(genomeSource.get(c))
    {
        switch(c)
        {
            case 'A':
            case 'T':
            case 'C':
            case 'G':
            case 'N':
                sequence += c;
                break;
            case 'a':
            case 't':
            case 'c':
            case 'g':
            case 'n':
                sequence += toupper(c);
                break;
            default:
                break;
        }
    }
    genomes.push_back(Genome(name, sequence));
    return true;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
    return m_size;  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if((position + length) >= m_size)
        return false;
    if(length < 0)
        return false;
    if(position < 0 || position >= m_size)
        return false;
    fragment = m_sequence.substr(position, length);
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
