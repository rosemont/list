/* a rather concise non-template list implementation
 *
 *
 */

#ifndef __XLIST_H__
#define __XLIST_H__

#include <iostream>
using namespace std;

struct node {
  int data;
  node* next;
  node* prev;
};

class xlist {
  public:
    class iterator {
      friend xlist;
      public:
      iterator():nodep(nullptr){}
      int operator *() {return nodep->data;}
      void operator++() {nodep = nodep->next;}
      void operator--() {nodep = nodep->prev;}
      bool operator!=(iterator itor2) {return (nodep!=itor2.nodep);}
      private:
      iterator(node* pos):nodep(pos){}
      node* nodep;
    };

    xlist(){head=new node(); head->next = head; head->prev = head;}
    xlist(const xlist& list1);
    xlist& operator = (const xlist &rhs);
    iterator begin() {return iterator(head->next);}
    iterator end() {return iterator(head);}
    void pushfront(const int &val);
    void pushback(const int &val);
    int size();
    bool empty();
    void showme();
    void clear();
    virtual ~xlist();
  private:
    node *head;
};

xlist::xlist(const xlist& listobj)
{
  head = new node;
  head->next = head;
  head->prev = head;

  node* cur;
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
    node *cur(rhs.head->next);
    while (cur != rhs.head) {
      pushback(cur->data);
      cur = cur->next;
    }
  }
  return *this;
}

void xlist::pushfront(const int &val)
{
  node *nodep(new node);
  nodep->data = val;

  nodep->next = head->next;
  head->next->prev = nodep;
  head->next = nodep;
  nodep->prev = head;
}

void xlist::pushback(const int &val)
{
  node *nodep;
  nodep = new node;
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
  node *cur = head->next;
  while (cur != head) count++;
  return count;
}

void xlist::showme()
{
  node* cur(head->next);
  while (cur!=head) {
    cout << cur->data << " ";
    cur = cur->next;
  }
  cout << endl;
}

void xlist::clear() {
  node* cur(head->next);

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
