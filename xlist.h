/* a rather concise non-template list implementation
 *
 *
 */

#ifndef __XLIST_H__
#define __XLIST_H__

#include <iostream>
using namespace std;

struct _list_node {
  int data;
  _list_node* next;
  _list_node* prev;
};

struct _list_iterator {
  typedef _list_iterator    _Self;
  typedef _list_node        _Node;
  typedef int*        pointer;
  typedef int&        reference;

  _list_iterator():nodep(nullptr){}
  explicit
    _list_iterator(_list_node* __x)
    :nodep(__x) { }
  reference 
    operator *() const 
    {return nodep->data;}
  _Self& 
    operator++() 
    {
      nodep = nodep->next;
      return *this;
    }
  _Self
    operator++(int)
    {
      _Self __tmp = *this;
      nodep = nodep->next;
      return __tmp;
    }
  _Self&
    operator--()
    {
      nodep = nodep->prev;
      return *this;
    }
  _Self
    operator--(int)
    {
      _Self __tmp = *this;
      nodep = nodep->prev;
      return __tmp;
    }
  bool 
    operator==(const _Self& __x) const 
    {return (nodep==__x.nodep);}
  bool 
    operator!=(const _Self&__x) const 
    {return (nodep!=__x.nodep);}
  _list_node* nodep;
};

struct _list_const_iterator {
  typedef _list_const_iterator    _Self;
  typedef const _list_node        _Node;
  _list_const_iterator():nodep(nullptr){}
  int operator *() const {return nodep->data;}
  void operator++() {nodep = nodep->next;}
  void operator--() {nodep = nodep->prev;}
  bool operator==(const _Self& __x) {return (nodep==__x.nodep);}
  bool operator!=(const _Self& __x) {return (nodep!=__x.nodep);}
  _list_const_iterator(_list_node* pos):nodep(pos){}
  _list_node* nodep;
};

class xlist {
  public:
    typedef _list_iterator           iterator;
    typedef _list_const_iterator      const_iterator;

    xlist(){head=new _list_node(); head->next = head; head->prev = head;}
    xlist(const xlist& list1);
    xlist& operator = (const xlist &rhs);
    iterator begin() {return iterator(head->next);}
    iterator end() {return iterator(head);}
    void pushfront(const int &val);
    void pushback(const int &val);
    int size();
    bool empty();
    void clear();
    virtual ~xlist();
  private:
    _list_node *head;
};

xlist::xlist(const xlist& listobj)
{
  head = new _list_node;
  head->next = head;
  head->prev = head;

  _list_node* cur;
  cur = listobj.head->next;
  while (cur != listobj.head) {
    pushback(cur->data);
    cur = cur->next;
  }
}

xlist& xlist::operator = (const xlist &rhs)
{
  if (this != &rhs) {
    clear();
    _list_node *cur(rhs.head->next);
    while (cur != rhs.head) {
      pushback(cur->data);
      cur = cur->next;
    }
  }
  return *this;
}

void xlist::pushfront(const int &val)
{
  _list_node *nodep(new _list_node);
  nodep->data = val;

  nodep->next = head->next;
  head->next->prev = nodep;
  head->next = nodep;
  nodep->prev = head;
}

void xlist::pushback(const int &val)
{
  _list_node *nodep;
  nodep = new _list_node;
  nodep->data = val;

  nodep->prev = head->prev;
  head->prev->next = nodep;
  head->prev = nodep;
  nodep->next = head;
}

bool xlist::empty()
{
  return (head==head->next);
}

int xlist::size()
{
  int count(0);
  _list_node *cur = head->next;
  while (cur != head) count++;
  return count;
}

void xlist::clear() {
  _list_node* cur(head->next);

  while (cur != head) {
    cur = cur->next;
    delete cur->prev;
  }
}

xlist::~xlist()
{
  clear();
  delete head;
}

#endif // __XLIST_H__
