//
//  landmark.cpp
//  Homework_3
//
//  Created by Yunus Chang on 2/7/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//


class Landmark
{
public:
    Landmark(string name)
    {
        m_name = name;
    };
    virtual string color() const = 0;
    virtual string icon() const = 0;
    virtual string location() const = 0;
    string name() const
    {
        return m_name;
    };
    void destructor(string location, string name) const
    {
        cout << "Destroying the " << location << " " << name << "." << endl;
    };
    virtual ~Landmark()
    {};
private:
    string m_name;
};


class Restaurant:public Landmark
{
public:
    Restaurant(string name, int capacity)
    :Landmark(name), m_capacity(capacity)
    {
    };
    virtual string color() const
    {
        return "yellow";
    };
    virtual string icon() const
    {
        if(m_capacity < 40)
            return "small fork/knife";
        else
            return "large fork/knife";
    };
    virtual string location() const
    {
        return "restaurant";
    };
    ~Restaurant()
    {
        destructor(location(),name());
    };
private:
    int m_capacity;
};

class Hotel:public Landmark
{
public:
    Hotel(string name)
    :Landmark(name)
    {
    };
    virtual string color() const
    {
        return "yellow";
    };
    virtual string icon() const
    {
        return "bed";
    };
    virtual string location() const
    {
        return "hotel";
    };
    ~Hotel()
    {
      destructor(location(),name());
    };
private:
};

class Hospital:public Landmark
{
public:
    Hospital(string name)
    :Landmark(name)
    {
    };
    virtual string color() const
    {
        return "blue";
    };
    virtual string icon() const
    {
        return "H";
    };
    virtual string location() const
    {
        return "hospital";
    };
    ~Hospital()
    {
        destructor(location(),name());
    };
private:
};


