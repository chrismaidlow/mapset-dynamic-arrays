#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound; using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;
#include<iterator>
using std::distance;

//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node() = default;
  Node(K,V);
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){

    out << n.first << ":" << n.second;
    
    return out;
  }
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    
    first = key;
    second = value;

}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const
{
    if(first < n.first)
    {
        return true;
    }
 
    return false;
    
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const
{
    if(first == n.first)
    {
        return true;
    }

    return false;    
    
}

//
// MapSet
// 
template<typename K, typename V>
class MapSet{
 private:
  Node<K,V>* ary_;
  size_t last_;
  size_t capacity_;
  Node<K,V>* find_key(K);
  void grow ();
 public:
  MapSet(int sz = 2);
  MapSet(initializer_list< Node<K,V> >);
  MapSet (const MapSet&);
  MapSet operator=(MapSet);
  ~MapSet();
  size_t size();
  bool remove (K);  
  bool add(Node<K,V>);
  Node<K,V> get(K);
  bool update(K,V);  
  int compare(MapSet&);
  MapSet mapset_union (MapSet&);
  MapSet mapset_intersection(MapSet&);
  
  
  //DONE
  friend ostream& operator<<(ostream &out, const MapSet &ms)
  {
    
    if(ms.last_ == 0)
    {
        out << "NO";
    }

    for (auto i = 0; i < ms.last_; i++) 
    {
        if(i == (ms.last_-1))
        {
            out << ms.ary_[i].first << ":" << ms.ary_[i].second;
        }
        else
        {
            out << ms.ary_[i].first << ":" << ms.ary_[i].second << ", ";
        }
    }
    
    return out;
    
  }  
};

//DONE
template<typename K, typename V>
MapSet<K,V>::MapSet(int capacity)
{
    capacity_ = capacity;
    last_ = 0;
    
    ary_ = new Node<K,V>[capacity];
}

//DONE
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il)
{
    capacity_ = il.size();
    ary_ = new Node<K,V>[capacity_];
    last_ = 0;

    for(auto i = il.begin(); i < il.end(); ++i)
    {
       //iterate through init adding each valid pair
       Node<K,V> new_node = *i;
       auto result = add(new_node);
     
    }

}

//DONE
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms)
{
    last_ = ms.last_;
    capacity_ = ms.capacity_;
    
    ary_ = new Node<K,V>[capacity_];
    
    copy(ms.ary_, ms.ary_ + ms.last_, ary_);
    
}

// copy and swap
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms)
{
    copy(ms.ary_, ms.ary_ + last_, ary_);
    swap(ary_, ms.ary_);
}

template<typename K, typename V>
MapSet<K,V>::~MapSet()
{
    //delete[] ary_;
}

//DONE
template<typename K, typename V>
size_t MapSet<K,V>::size()
{
    return last_;
}

//DONE
template<typename K, typename V>
void MapSet<K,V>::grow()
{
    Node<K, V>* new_ary = new Node<K,V>[capacity_ * 2];
    copy(ary_, ary_+last_, new_ary);
    
    swap(ary_, new_ary);
    delete[] new_ary;
    
    capacity_ = (capacity_ * 2);
    
}

template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key)
{
    Node<K, V> new_node = {key, 200};
   // lower_bound algo with string/pair comparison lambda
   Node<K,V>* pntr = lower_bound(ary_ , ary_ + last_, new_node);
   
   return pntr;
}


template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n)
{
    if(last_ == capacity_)
    {
        grow();
    }

    auto pntr = find_key(n.first);
    auto dist = distance(ary_, pntr);
    
    if (pntr != nullptr && (*pntr).first == n.first)
    {
        return false;
    }
    
    Node<K, V>* new_ary = new Node<K,V>[capacity_];
    
    copy(ary_, ary_+dist, new_ary);
    
    new_ary[dist] = n;
    
    copy(ary_ + dist, ary_ + last_, new_ary + dist + 1);
    swap(ary_, new_ary);

    delete[] new_ary;
    
    last_ = last_ + 1;

    return true;
    
}

template<typename K, typename V>
bool MapSet<K,V>::remove(K key)
{
    auto pntr = find_key(key);
    auto dist = distance(ary_, pntr);
    
    
    if ((*pntr).first == key)
    {
        Node<K, V>* new_ary = new Node<K,V>[capacity_];
    
        copy(ary_, ary_+dist, new_ary);
    
        copy(ary_ + dist + 1, ary_ + last_, new_ary + dist);
        swap(ary_, new_ary);

        delete[] new_ary;
    
        last_ = last_ - 1;

        return true;
    }
    else
    {
         return false;
    }
  
}

template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key)
{
     auto pntr = find_key(key);
     if((*pntr).first == key)
     {
         auto new_node = *pntr;
         return (new_node);
     }
     else
     {
         Node<K,V> blank = {"",0};
         return blank;
     }
}

template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value)
{
    auto pntr = find_key(key);
    if((*pntr).first == key)
    {
        (*pntr).second = value;
        return true;
    }
    else     
    {
        
        return false;
    }
}

template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms)
{
    size_t size_arg = ms.size();
    size_t size_call = size();
    
    size_t standard;
    
    //smaller size vector is chosen
    if(size_arg < size_call)
    {
        standard = size_arg;
    }
    else
    {
        standard = size_call;
    }
    
    //iterate through 
    for(auto i = 0; i < standard; ++i)
    {
        //if equal continue
        if(ms.ary_[i].first == ary_[i].first)
        {
            continue;
        }
        //if calling is greater return 1
        else if(ms.ary_[i].first < ary_[i].first)
        {
            return 1;
        }
        //if arg is greater return -1
        else if(ms.ary_[i].first > ary_[i].first)
        {
            return -1;
        }

    }
    
    //size comparison if equality doesn't work out
    if(size() > ms.size())
    {
        return 1;
    }
    else if (size() < ms.size())
    {
        return -1;
    }
    else if (size() == ms.size() )
    {
        return 0;
    }
    
    return 0;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms)
{
    
    MapSet<K,V> new_map;
    
    for(auto i = ary_; i < ary_ + last_; ++i)
    {
        new_map.add(*i);   
    }
    
    //iterate through mapset 2 and add
    for(auto i = ms.ary_; i < ms.ary_ + ms.last_; ++i)
    {
        new_map.add(*i);   
    }
    
    //iterate through mapset 1 and add

    
    return new_map; 
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms)
{
   MapSet<K,V> new_map;  
    
    for(auto i = ary_; i < ary_ + last_; ++i)
    {
        auto key = ms.find_key((*i).first);
        
        if((*key).first == (*i).first)
        {
            new_map.add(*i);
        }
        
    }
    
    return new_map;
}


#endif