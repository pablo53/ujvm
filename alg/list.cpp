#ifndef _ALG_LIST_H
#define _ALG_LIST_H


#include "list.h"

#include "../defs/types.h"


ListContainer::ListContainer(const void * element, ListContainer * next)
{
  this->element = element;
  this->next = next;
}

ListContainer::~ListContainer()
{
  /* this is "void List::predelete(void *)"" that should clean up this->element */
}

List::List(ListContainer * head, ListContainer * tail, void (*predelete)(const void *))
{
  this->head = head;
  this->tail = tail;
  this->predelete = predelete;
}

List::~List()
{
  ListContainer *curs = this->head;
  ListContainer *next;
  while (curs)
  {
    next = curs->next;
    if (predelete)
      predelete(curs->element);
    delete curs;
    curs = next;
  }
}

List * List::create(void (*predelete)(const void *))
{
  return new List(nullptr, nullptr, predelete); /* returns also ownership */
}

List * List::append(const void * element)
{
  ListContainer *container = new ListContainer(element);
  if (!tail)
    head = tail = container;
  else
  {
    tail->next = container;
    tail = container;
  }
  return this;
}

List * List::prepend(const void * element)
{
  ListContainer *container = new ListContainer(element);
  if (!head)
    head = tail = container;
  else
  {
    container->next = head;
    head = container;
  }
  return this;
}

u64 List::size()
{
  ListContainer * cur = head;
  u64 sz = 0;
  while (cur)
  {
    if (!++sz)
      return U64_MAX; /* overflow, return possible max */
    cur = cur->next;
  }
}


#endif
