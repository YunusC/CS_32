#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>
#include <set>
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
        Node(char ID){m_ID = ID;};
        bool operator<(Node &a);
        char m_ID;
        vector<ValueType> m_value;
        set<Node*> m_children;
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
    m_root = new Node(0);
}

template<typename ValueType>
inline
Trie<ValueType>::~Trie()
{
    destroy(m_root);
}

template<typename ValueType>
inline
bool Trie<ValueType>::Node::operator<(Node &a)
{
    if(a.m_ID < this->m_ID)
        return false;
    if(this->m_ID < a.m_ID)
        return true;
    return true;
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
            x->m_children.insert(new Node(key[i]));
            typename set<Node*>::iterator a;
            a = x->m_children.begin();
            for(;;)
            {
                if((*a)->m_ID == key[i])
                {
                    x = (*a);
                    break;
                }
                a++;
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
    else
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
        for(int i = 0;i < x->m_value.size();i++)
        {
            answer.push_back(x->m_value[i]);
        }
        return;
    }
    typename set<Node*>::iterator i;
    i = x->m_children.begin();
    while(i != x->m_children.end())
    {
        if(nextBase(x, key[0]) == (*i))
            findHelper(key.substr(1,key.length()), false, answer, (*i));
        else
            findHelper(key.substr(1,key.length()), true, answer, (*i));
        i++;
    }
}

template<typename ValueType>
inline
void Trie<ValueType>::destroy(Node* x)
{
    if(x == nullptr)
        return;
    typename set<Node*>::iterator i;
    i = x->m_children.begin();
    while(i != x->m_children.end())
    {
        destroy(*i);
        i++;
    }
    delete x;
}


template<typename ValueType>
inline
typename Trie<ValueType>::Node* Trie<ValueType>::nextBase(Node* x, char alpha) const
{
    typename set<Node*>::iterator i;
    i = x->m_children.begin();
    while(i != x->m_children.end())
    {
        if((*i)->m_ID == alpha)
            return (*i);
        i++;
    }
    return nullptr;
}
#endif // TRIE_INCLUDED
