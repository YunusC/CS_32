#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include <sstream>

using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    Trie<string> m_genomeTrie;
    vector<Genome> m_genome;
    int m_minSearchLength;
    int m_numOfGenomes;
    bool DNAMatcher(string genomeValue, const string& targetSequence, int totalLength, int minLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
    m_numOfGenomes = 0;
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genome.push_back(genome);
    int pos = 0;
    m_numOfGenomes++;
    string fragment;
    string input;
    ostringstream genomePosition;
    while(genome.extract(pos, m_minSearchLength, fragment))
    {
        genomePosition << "Genome " << m_numOfGenomes << ", position " << pos;
        input = genomePosition.str();
        genomePosition.str("");
        m_genomeTrie.insert(fragment, input);
        pos++;
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if(minimumLength < minimumSearchLength())
        return false;
    if(fragment.size() < minimumLength)
        return false;
    vector<string> vecString;
    if(exactMatchOnly)
    {
        vecString = m_genomeTrie.find(fragment.substr(0,minimumSearchLength()), true);
    }
    else
    {
        vecString = m_genomeTrie.find(fragment.substr(0,minimumSearchLength()),false);
    }
    if(vecString.empty())
        return false;
    for(int x = 0;x < vecString.size();x++)
    {
        cout << vecString[x] << endl;
    }
    matches.clear();
    bool matchFound = false;
    vector<string>::iterator i;
    i = vecString.begin();
    while(i != vecString.end())
    {
        if(DNAMatcher((*i), fragment, fragment.size(), minimumLength, exactMatchOnly, matches))
        {
            matchFound = true;
        }
        i++;
    }
    return matchFound;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    
    return false;  // This compiles, but may not be correct
}

bool GenomeMatcherImpl::DNAMatcher(string genomeValue, const string& targetSequence, int totalLength, int minLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    int genomeNum = 0;
    int posNum = 0;
    genomeValue = genomeValue.substr(7,genomeValue.size());
    int i = 0;
    while(isdigit(genomeValue[i]))
    {
        genomeNum *= 10;
        genomeNum += genomeValue[i] - 48;
        i++;
    }
    while(!isdigit(genomeValue[i]))
        i++;
    while(isdigit(genomeValue[i]))
    {
        posNum *= 10;
        posNum += genomeValue[i] - 48;
        i++;
    }
    string fragment;
    m_genome[genomeNum - 1].extract(posNum, totalLength, fragment);
    bool diffChar = exactMatchOnly;
    bool matchFound = false;
    int matchLength = 0;
    while(matchLength < totalLength)
    {
        if(targetSequence[matchLength] != fragment[matchLength])
        {
            if(diffChar == false)
            {
                diffChar = true;
                matchLength++;
                if(matchLength == minLength)
                    matchFound = true;
                continue;
            }
            return false;
        }
        matchLength++;
        if(matchLength == minLength)
            matchFound = true;
    }
    if(matchFound)
    {
        vector<DNAMatch>::iterator i;
        i = matches.begin();
        while(i != matches.end())
        {
            if(m_genome[genomeNum - 1].name() == (*i).genomeName)
            {
                if(matchLength > (*i).length)
                {
                    matches.erase(i);
                    matches.push_back(DNAMatch{m_genome[genomeNum - 1].name(), matchLength, posNum});
                    return true;
                }
                if(matchLength == (*i).length)
                {
                    if(posNum < (*i).position)
                    {
                        matches.erase(i);
                        matches.push_back(DNAMatch{m_genome[genomeNum - 1].name(), matchLength, posNum});
                        return true;
                    }
                    return false;
                }
            }
            i++;
        }
        matches.push_back(DNAMatch{m_genome[genomeNum - 1].name(), matchLength, posNum});
    }
    return matchFound;
}
//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
