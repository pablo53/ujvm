#ifndef _ALG_REGEXP_CPP
#define _ALG_REGEXP_CPP


#include "regexp.h"

#include "list.h"
#include "buf.h"
#include "../defs/types.h"
#include "../defs/err.h"
#include "../defs/utf8.h"
#include "../class/utf8.h"


#define REGEXP_CHAR_GROUP_OPEN  '('
#define REGEXP_CHAR_GROUP_CLOSE ')'
#define REGEXP_CHAR_SET_OPEN    '['
#define REGEXP_CHAR_SET_CLOSE   ']'
#define REGEXP_CHAR_ARITY_OPEN  '{'
#define REGEXP_CHAR_ARITY_CLOSE '}'
#define REGEXP_CHAR_COMMA       ','
#define REGEXP_CHAR_RANGE       '-'
#define REGEXP_CHAR_ANY_CHAR    '.'
#define REGEXP_CHAR_MANY        '*'
#define REGEXP_CHAR_EXIST       '+'
#define REGEXP_CHAR_MAYBE       '?'
#define REGEXP_CHAR_OR          '|'
#define REGEXP_CHAR_NOT         '^'
#define REGEXP_CHAR_ESCAPE      '\\'


static inline bool is_special_char(jchar ch)
{
  return ch == REGEXP_CHAR_GROUP_OPEN
      || ch == REGEXP_CHAR_GROUP_CLOSE
      || ch == REGEXP_CHAR_SET_OPEN
      || ch == REGEXP_CHAR_SET_CLOSE
      || ch == REGEXP_CHAR_ARITY_OPEN
      || ch == REGEXP_CHAR_ARITY_CLOSE
      || ch == REGEXP_CHAR_ANY_CHAR
      || ch == REGEXP_CHAR_MANY
      || ch == REGEXP_CHAR_EXIST
      || ch == REGEXP_CHAR_MAYBE
      || ch == REGEXP_CHAR_OR
      || ch == REGEXP_CHAR_ESCAPE;
}


RegTreeNode::RegTreeNode(const RegTreeNode * parent) : node_type(REGEXP_NODE_ABSTRACT)
{
  this->parent = parent;
}

RegTreeNode::~RegTreeNode()
{
}

RegTreeNode * RegTreeNode::from(const JavaUtf8 * utf8)
{
  Utf8Buffer buf(utf8);
  RegTreeNode *node = RegTreeSequenceNode::from(buf);
  return node;
}

typedef RegTreeNode * (*from_f_t)(Utf8Buffer &, const RegTreeNode *);

RegTreeNode * RegTreeNode::from(Utf8Buffer & buf, const RegTreeNode * parent)
{
  if (!buf.chars_left())
    return nullptr;
  RegTreeNode * node;
  u16 curs = buf.curs;
  static from_f_t froms[] =
  {
    (from_f_t)RegTreeSetNode::from,
    (from_f_t)RegTreeGroupNode::from,
    nullptr
  };
  int i = 0;
  from_f_t from = froms[i++];
  while (from)
  {
    node = from(buf, parent);
    if (node)
      return node;
    else if (buf.curs > curs)
      return nullptr;
    from = froms[i++];
  }
  return nullptr; // TODO
}


RegTreeSequenceNode::RegTreeSequenceNode() : RegTreeNode(nullptr)
{
  node_list = List::create(predelete);
}

RegTreeSequenceNode::~RegTreeSequenceNode()
{
  delete node_list;
}

void RegTreeSequenceNode::predelete(const void * ptr)
{
  delete (RegTreeNode *)ptr;
}

RegTreeSequenceNode * RegTreeSequenceNode::from(Utf8Buffer & buf)
{
  if (!buf.chars_left())
    return nullptr;
  RegTreeSequenceNode * node = new RegTreeSequenceNode();
  RegTreeNode *last, *next = nullptr;
  do
  {
    last = next;
    next = RegTreeNode::from(buf, node);
    if (next)
      node->node_list->append(next);
  } while (buf.chars_left() && next);
  if (buf.chars_left()) /* early exit from the loop means some error has occurred */
  {
    delete node;
    node = nullptr;
  }
  return node;
}


RegTreeRangeNode::RegTreeRangeNode(const RegTreeNode * parent, jchar ch) : RegTreeNode(parent)
{
  this->char_min = this->char_max = ch;
  this->node_type = REGEXP_NODE_RANGE;
}

RegTreeRangeNode::RegTreeRangeNode(const RegTreeNode * parent, jchar ch_min, jchar ch_max) : RegTreeNode(parent)
{
  this->char_min = char_min;
  this->char_max = char_max;
  this->node_type = REGEXP_NODE_RANGE;
}

RegTreeRangeNode * RegTreeRangeNode::from(Utf8Buffer & buf, const RegTreeNode * parent)
{
  jchar ch = buf.peek();
  if (!buf.chars_left() || (is_special_char(ch) && ch != REGEXP_CHAR_ESCAPE))
    return nullptr;
  buf.next(); // consume what has been peeked
  if (ch == REGEXP_CHAR_ESCAPE)
  {
    if (!buf.chars_left())
      return nullptr; // run out of buffer after an escape character
    ch = buf.next(); // we accept any character as the range limit, if it follows the escape character
  }
  if (buf.peek() == REGEXP_CHAR_RANGE)
  {
    buf.next(); // consume what has been peeked
    if (!buf.chars_left())
      return nullptr; // run out of buffer after a range marking character
    jchar ch_max = buf.next();
    if (ch_max == REGEXP_CHAR_ESCAPE)
    {
      if (!buf.chars_left())
        return nullptr; // run out of buffer after an escape character
      ch_max = buf.next(); // we accept any character as the range limit, if it follows the escape character
    }
    return new RegTreeRangeNode(parent, ch, ch_max);
  }
  else
    return new RegTreeRangeNode(parent, ch);
}


void RegTreeSetNode::predelete(const void * ptr)
{
  delete (RegTreeRangeNode*)ptr;
}

RegTreeSetNode::RegTreeSetNode(const RegTreeNode * parent) : RegTreeNode(parent)
{
  neg = false;
  node_list = List::create(predelete);
  this->node_type = REGEXP_NODE_SET;
}

RegTreeSetNode::~RegTreeSetNode()
{
  delete node_list;
}

RegTreeSetNode * RegTreeSetNode::from(Utf8Buffer & buf, const RegTreeNode * parent)
{
  if (buf.peek() != REGEXP_CHAR_SET_OPEN)
    return nullptr; /* this is not a regexp group */
  buf.next(); /* consume the openning square bracket */
  RegTreeSetNode * node = new RegTreeSetNode(parent);
  jchar ch = buf.peek();
  if (ch == REGEXP_CHAR_NOT)
  {
    node->neg = true;
    buf.next(); /* consume the negation sign */
  }
  RegTreeRangeNode * subnode;
  bool closed = false;
  while (buf.chars_left())
  {
    ch = buf.peek();
    if (ch == REGEXP_CHAR_SET_CLOSE)
    {
      closed = true;
      buf.next(); /* consume the peeked closing square bracket */
      break;
    }
    subnode = RegTreeRangeNode::from(buf, node);
    if (!subnode) /* if some error occurs */
    {
      delete node;
      return nullptr;
    }
    node->node_list->append(subnode);
  }
  if (!closed)
  {
    delete node;
    return nullptr;
  }
  return node;
}


void RegTreeAltNode::predelete(const void * ptr)
{
  delete (RegTreeNode*)ptr;
}

RegTreeAltNode::RegTreeAltNode(const RegTreeNode * parent) : RegTreeNode(parent)
{
  node_list = List::create(predelete);
}

RegTreeAltNode::~RegTreeAltNode()
{
  delete node_list;
}

RegTreeAltNode * RegTreeAltNode::from(const RegTreeNode * prev, Utf8Buffer & buf, const RegTreeNode * parent)
{
  if (buf.peek() != REGEXP_CHAR_OR)
    return nullptr; /* this is not a regexp group */
  buf.next(); /* consume the pipe sign */
  RegTreeNode * next = RegTreeNode::from(buf, parent);
  if (!next)
    return nullptr; /* sth must have gone wrong */
  if (next->node_type == REGEXP_NODE_ALT)
  {
    ((RegTreeAltNode *)next)->node_list->prepend(prev);
    return (RegTreeAltNode *)next;
  }
  else
  {
    RegTreeAltNode * alt = new RegTreeAltNode(parent);
    alt->node_list->append(prev);
    alt->node_list->append(next);
    return alt;
  }
}


RegTreeRepeatNode::RegTreeRepeatNode(const RegTreeNode * parent, const RegTreeNode * node, u16 repeat_min, u16 repeat_max) : RegTreeNode(parent)
{
  this->node = node;
  this->repeat_min = repeat_min;
  this->repeat_max = repeat_max;
}

RegTreeRepeatNode::~RegTreeRepeatNode()
{
  delete node;
}

RegTreeRepeatNode * RegTreeRepeatNode::from(const RegTreeNode * node, Utf8Buffer & buf, const RegTreeNode * parent)
{
  if (buf.peek() == REGEXP_CHAR_MANY)
  {
    buf.next();
    return new RegTreeRepeatNode(parent, node, 0, 0);
  }
  else if (buf.peek() == REGEXP_CHAR_EXIST)
  {
    buf.next();
    return new RegTreeRepeatNode(parent, node, 1, 0);
  }
  else if (buf.peek() == REGEXP_CHAR_MAYBE)
  {
    buf.next();
    return new RegTreeRepeatNode(parent, node, 0, 1);
  }
  else if (buf.peek() != REGEXP_CHAR_ARITY_OPEN)
    return nullptr;
  buf.next(); /* consume openning curly bracket */
  u64 llimit;
  int res = buf.read_number(llimit);
  if (res == ERR_NOT_A_NUMBER)
    llimit = 0; /* default, if not provided */
  else if (res || llimit > U16_MAX)
    return nullptr; /* some error */
  if (buf.next() != REGEXP_CHAR_COMMA)
    return nullptr; /* syntax error */
  u64 ulimit;
  res = buf.read_number(ulimit);
  if (res == ERR_NOT_A_NUMBER)
    ulimit = 0; /* default, if not provided */
  else if (res || ulimit > U16_MAX)
    return nullptr; /* some error */
  if (buf.next() != REGEXP_CHAR_ARITY_CLOSE)
    return nullptr; /* syntax error */
  return new RegTreeRepeatNode(parent, node, (u16)llimit, (u16)ulimit);
}


RegTreeGroupNode::RegTreeGroupNode(const RegTreeNode * node, const RegTreeNode * parent) : RegTreeNode(parent)
{
  this->node = node;
  this->node_type = REGEXP_NODE_GROUP;
}

RegTreeGroupNode::~RegTreeGroupNode()
{
  delete node;
}

RegTreeGroupNode * RegTreeGroupNode::from(Utf8Buffer & buf, const RegTreeNode * parent)
{
  if (buf.peek() != REGEXP_CHAR_GROUP_OPEN)
    return nullptr; /* this is not a regexp group */
  buf.next(); /* consume the openning bracket */
  RegTreeNode *innernode = RegTreeNode::from(buf);
  if (!innernode)
    return nullptr; /* inner regexp was somehow incorrect */
  if (buf.next() != REGEXP_CHAR_GROUP_CLOSE)
  {
    delete innernode;
    return nullptr; /* the regexp group was not correctly closed */
  }
  RegTreeGroupNode *node = new RegTreeGroupNode(innernode);
  innernode->parent = node;
  return node;
}


RegTreeStringNode::RegTreeStringNode(const RegTreeNode * parent, JavaUtf8 * utf8) : RegTreeNode(parent)
{
  this->utf8 = utf8;
}

RegTreeStringNode::~RegTreeStringNode()
{
  delete utf8;
}

bool RegTreeStringNode::predicate(jchar ch, void * ctx)
{
  bool ret_val = ((Utf8Context *)ctx)->esc || !is_special_char(ch);
  ((Utf8Context *)ctx)->esc = (!((Utf8Context *)ctx)->esc && ch == REGEXP_CHAR_ESCAPE);
  return ret_val;
}

RegTreeStringNode * RegTreeStringNode::from(Utf8Buffer & buf, const RegTreeNode * parent)
{
  Utf8Context ctx;
  JavaUtf8 * utf8 = buf.take_until(predicate, &ctx);
  return utf8 ? new RegTreeStringNode(parent, utf8) : nullptr;
}


#endif

