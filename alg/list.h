#ifndef _ALG_LIST_CPP
#define _ALG_LIST_CPP


class ListContainer
{
  public:
  void * element; /* ownership here */
  ListContainer * next;

  ListContainer(void *, ListContainer * = nullptr);
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
  void (*predelete)(void *); /* a function to be called on non null element before destructing the list; this should be usually deallocating memory from the element */

  List(const List &) = delete;
  List(List &&) = delete;
  ~List();
  List * append(void *);

  static List * create(void (*)(void *) = nullptr);

  protected:
  List(ListContainer *, ListContainer *, void (*)(void *) = nullptr);
};

#endif

