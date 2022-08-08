#ifndef TCOMM_H
#define TCOMM_H

#include <Arduino.h>
#include <LinkedPointerList.h>

template <class T>
class List
{
  public:
    List() {}
    void add( T* input) { list.add(input); }
    int size() { return list.size(); }
    T* get(int index) { return list.get(index); }
  private:
    static LinkedPointerList<T> list;
};

template<class T> LinkedPointerList<T> List<T>::list; // enables the static list

template <class T>
class TComm
{
  public:
    List<TComm<T>> list;
    TComm() { TSize = sizeof(T); }
    void Xinit() { list.add(this); }
    void Xinit(String input) { list.add(this); commName = input; }
    bool peek() { return changed; }
    bool isChanged() { bool isChanged = changed; changed = false; return isChanged; }
    TComm<T>& operator = (const T& input) { if(!equals(input)) { changed = true; value = input; } return *this; }
    operator T&(){ return value; }
    void set(T input) { if(!equals(input)) { changed = true; value = input; }}
    T get() { return value; }
  private:
    int TSize;
    T value;
    bool changed;
    String commName;
    bool equals( T input) 
    { bool equals = true; 
      for(int i = 0; i < TSize; i++) { byte a = *((byte *)(&value) + i); byte b = *((byte *)(&input) + i);
      if(a != b) { equals = false; }};
      return equals; 
    }
};

#endif //TCOMM_H
