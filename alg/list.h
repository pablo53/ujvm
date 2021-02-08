#ifndef _ALG_LIST_CPP
#define _ALG_LIST_CPP


#include "../defs/types.h"


class ListContainer
{
  public:
  const void * element; /* ownership here */
  ListContainer * next;

  ListContainer(const void *, ListContainer * = nullptr);
  ListContainer() = delete;
  ListContainer(const ListContainer &) = delete;
  ListContainer(ListContainer &&) = delete;
  ~ListContainer();
};

class List
{
  public:
  ListContainer * head;
  ListContainer * tail;
  void (*predelete)(const void *); /* a function to be called on non null element before destructing the list; this should be usually deallocating memory from the element */

  List(const List &) = delete;
  List(List &&) = delete;
  ~List();
  List * append(const void *);
  List * prepend(const void *);
  u64 size(); /* number of elements, no more than U64_MAX */

  static List * create(void (*)(const void *) = nullptr);

  protected:
  List(ListContainer *, ListContainer *, void (*)(const void *) = nullptr);
};

#endif

