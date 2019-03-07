#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
using namespace std;

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node
    {
        vector<ValueType> m_value;
        Node* A = nullptr;
        Node* T = nullptr;
        Node* C = nullptr;
        Node* G = nullptr;
        Node* N = nullptr;
    };
    Node* m_root;
    void destroy(Node* x);
    Node* nextBase(Node* x, char base) const;
    void insertHelper(const std::string& key, const ValueType& value);
    void findHelper(string key, bool exactMatchOnly, vector<ValueType> &answer, Node* x) const;
};

template<typename ValueType>
inline
Trie<ValueType>::Trie()
{
    m_root = new Node;
}

template<typename ValueType>
inline
Trie<ValueType>::~Trie()
{
    destroy(m_root);
}

template<typename ValueType>
inline
void Trie<ValueType>::reset()
{
    destroy(m_root);
    m_root = new Node;
}

template<typename ValueType>
inline
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    Node* x = m_root;
    for(int i = 0;i < key.length();i++)
    {
        if(nextBase(x, key[i]) == nullptr)
        {
            switch(key[i])
            {
                case 'A':
                    x->A = new Node;
                    x = x->A;
                    break;
                case 'T':
                    x->T = new Node;
                    x = x->T;
                    break;
                case 'C':
                    x->C = new Node;
                    x = x->C;
                    break;
                case 'G':
                    x->G = new Node;
                    x = x->G;
                    break;
                case 'N':
                    x->N = new Node;
                    x = x->N;
                    break;
                default:
                    return;
            }
        }
        else
            x = nextBase(x, key[i]);
    }
    x->m_value.push_back(value);
}

template<typename ValueType>
inline
vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    vector<ValueType> answer;
    if(nextBase(m_root, key[0]) == nullptr)
        return answer;
    if(exactMatchOnly)
    {
        Node* x = m_root;
        for(int i = 0;i < key.length();i++)
        {
            if(nextBase(x, key[i]) == nullptr)
            {
                return answer;
            }
            else
                x = nextBase(x, key[i]);
        }
        return x->m_value;
    }
    else //need to implement this
    {
        findHelper(key.substr(1,key.length()), exactMatchOnly, answer, nextBase(m_root, key[0]));
        return answer;
    }
    
}

template<typename ValueType>
inline
void Trie<ValueType>::findHelper(string key, bool exactMatchOnly, vector<ValueType> &answer, Node* x) const
{
    if(nextBase(x,key[0]) == nullptr && exactMatchOnly == true)
        return;
    if(key == "")
    {
        cout << "i should be in here once" << endl;
        for(int i = 0;i < x->m_value.size();i++)
        {
            cout << "this hsould happen tice" << endl;
            answer.push_back(x->m_value[i]);
        }
        return;
    }
    if(x->A != nullptr)
    {
        cout << "this should happen 2 times" << endl;
        if(nextBase(x, key[0]) == x->A)
        {
            findHelper(key.substr(1,key.length()), false, answer, x->A);
            cout << "this should happen twie" << endl;
        }
        else
            findHelper(key.substr(1,key.length()), true, answer, x->A);
    }
    if(x->T != nullptr)
    {
        if(nextBase(x, key[0]) == x->T)
            findHelper(key.substr(1,key.length()), false, answer, x->T);
        else
            findHelper(key.substr(1,key.length()), true, answer, x->T);
    }
    if(x->C != nullptr)
    {
        if(nextBase(x, key[0]) == x->C)
            findHelper(key.substr(1,key.length()), false, answer, x->C);
        else
            findHelper(key.substr(1,key.length()), true, answer, x->C);
    }
    if(x->G != nullptr)
    {
        if(nextBase(x, key[0]) == x->G)
            findHelper(key.substr(1,key.length()), false, answer, x->G);
        else
            findHelper(key.substr(1,key.length()), true, answer, x->G);
    }
    if(x->N != nullptr)
    {
        if(nextBase(x, key[0]) == x->N)
            findHelper(key.substr(1,key.length()), false, answer, x->N);
        else
            findHelper(key.substr(1,key.length()), true, answer, x->N);
    }
}

template<typename ValueType>
inline
void Trie<ValueType>::destroy(Node* x)
{
    if(x == nullptr)
        return;
    destroy(x->A);
    destroy(x->T);
    destroy(x->C);
    destroy(x->G);
    destroy(x->N);
    delete x;
}


template<typename ValueType>
inline
typename Trie<ValueType>::Node* Trie<ValueType>::nextBase(Node* x, char base) const
{
    switch(base)
    {
        case 'A':
            return x->A;
        case 'T':
            return x->T;
        case 'C':
            return x->C;
        case 'G':
            return x->G;
        case 'N':
            return x->N;
        default:
            return nullptr;
    }
}
#endif // TRIE_INCLUDED
