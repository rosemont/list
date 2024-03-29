/* a rather concise non-template list implementation
 * a doubly linked list
 *
 */

#ifndef __XLIST_H__
#define __XLIST_H__

struct _list_node {
  int data;
  _list_node* next;
  _list_node* prev;
};

struct _list_iterator {
  typedef _list_iterator    _Self;
  typedef _list_node        _Node;
  typedef std::ptrdiff_t               difference_type;
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
  typedef _list_iterator          iterator;

  typedef std::ptrdiff_t               difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef int                     value_type;
  typedef const int*              pointer;
  typedef const int&              reference;

  _list_const_iterator()
    :nodep(){}
  explicit
    _list_const_iterator(const _list_node* __x)
    :nodep(__x) { }
  _list_const_iterator(const iterator& __x)
    :nodep(__x.nodep) { }
  reference
    operator *() const 
    {return nodep->data;}
  pointer 
    operator->() const
    { return std::__addressof(nodep->data); }
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
      nodep = nodep->next;
      return __tmp;
    }
  bool 
    operator==(const _Self& __x) {return (nodep==__x.nodep);}
  bool 
    operator!=(const _Self& __x) {return (nodep!=__x.nodep);}
  const _list_node* nodep;
};

class xlist {
  public:
    typedef _list_iterator           iterator;
    typedef _list_const_iterator      const_iterator;
    typedef int&                            reference;
    typedef const int&                      const_reference;
    typedef std::ptrdiff_t                 difference_type;
    typedef size_t                          size_type;

    // list default constructor
    xlist(){head=new _list_node(); head->next = head; head->prev = head;}
    // list copy constructor
    xlist(const xlist& __x) 
    { 
      _init();
      _initialize_dispatcher(__x.begin(), __x.end()); 
    }
    xlist(const_iterator __first, const_iterator __last)
    { _init();
      _initialize_dispatcher(__first, __last);
    }
    // list assignment operator
    xlist& operator = (const xlist &__x);
    iterator begin() {return iterator(head->next);}
    iterator end() {return iterator(head);}
    const_iterator 
      begin() const
      { return const_iterator(head->next); }
    const_iterator 
      end() const
      { return const_iterator(head); }
    void push_front(const int &val);
    void push_back(const int &val);
    size_type size() const {return std::distance(begin(), end()); }
    bool empty();
    reference
      front()
      { return *begin();}
    const_reference
      front() const
      { return *begin(); }
    reference
      back()
      {
        iterator __tmp = end();
        --__tmp;
        return *__tmp;
      }
    const_reference
      back() const
      {
        const_iterator __tmp = end();
        --__tmp;
        return *__tmp;
      }
    void clear();
    virtual ~xlist();
  protected:
    void _init() {head=new _list_node;head->next=head;head->prev=head;}
    void _initialize_dispatcher(const_iterator __first, const_iterator __last)
    {
      for (; __first != __last; ++__first)
        push_back(*__first);
    }
  private:
    _list_node *head;
};

// list assignment operator
xlist& xlist::operator = (const xlist &rhs)
{
  if (this != &rhs) {
    clear();
    _list_node *cur(rhs.head->next);
    while (cur != rhs.head) {
      push_back(cur->data);
      cur = cur->next;
    }
  }
  return *this;
}

void xlist::push_front(const int &val)
{
  _list_node *nodep(new _list_node);
  nodep->data = val;

  nodep->next = head->next;
  head->next->prev = nodep;
  head->next = nodep;
  nodep->prev = head;
}

void xlist::push_back(const int &val)
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
