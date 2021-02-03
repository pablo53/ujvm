#ifndef _ALG_REGEXP_H
#define _ALG_REGEXP_H


#include "list.h"
#include "buf.h"
#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../class/utf8.h"


#define REGEXP_NODE_ABSTRACT  0
#define REGEXP_NODE_RANGE     1
#define REGEXP_NODE_SET       2
#define REGEXP_NODE_ALT       3
#define REGEXP_NODE_REPEAT    4
#define REGEXP_NODE_GROUP     5
#define REGEXP_NODE_STRING    6

class RegTreeNode
{
  public:
  int node_type;
  const RegTreeNode * parent;

  RegTreeNode() = delete;
  RegTreeNode(const RegTreeNode &) = delete;
  RegTreeNode(RegTreeNode &&) = delete;
  virtual ~RegTreeNode() = 0;

  static RegTreeNode * from(const JavaUtf8 *); /* returns with ownership */

  protected:
  RegTreeNode(const RegTreeNode *);
  static RegTreeNode * from(Utf8Buffer &, const RegTreeNode * = nullptr); /* returns with ownership */
};

class RegTreeSequenceNode : public RegTreeNode
{
  public:
  List * node_list; /* list of RegTreeNode alternatives */

  RegTreeSequenceNode(const RegTreeSequenceNode &) = delete;
  RegTreeSequenceNode(RegTreeSequenceNode &&) = delete;
  virtual ~RegTreeSequenceNode();

  protected:
  RegTreeSequenceNode(); /* creates and initializes an empty sequence */
  static RegTreeSequenceNode * from(Utf8Buffer &); /* Returns null, if buffer content does not match */

  private:
  static void predelete(const void *);

  friend class RegTreeNode;
};

class RegTreeRangeNode : public RegTreeNode
{
  public:
  jchar char_min, char_max;
  
  RegTreeRangeNode() = delete;
  RegTreeRangeNode(const RegTreeRangeNode &) = delete;
  RegTreeRangeNode(RegTreeRangeNode &&) = delete;

  protected:
  RegTreeRangeNode(const RegTreeNode * parent, jchar ch);
  RegTreeRangeNode(const RegTreeNode * parent, jchar ch_min, jchar ch_max);

  static RegTreeRangeNode * from(Utf8Buffer &, const RegTreeNode * = nullptr); /* Returns null, if buffer content does not match */

  friend class RegTreeNode;
  friend class RegTreeSetNode;
};

class RegTreeSetNode : public RegTreeNode
{
  public:
  bool neg; /* it means [^...], instead of [...] (note '^' character at the beginning) */
  List * node_list; /* these are elements "..." from [...] or [^...] - a list of RegTreeRangeNode */
  
  RegTreeSetNode() = delete;
  RegTreeSetNode(const RegTreeSetNode &) = delete;
  RegTreeSetNode(RegTreeSetNode &&) = delete;
  virtual ~RegTreeSetNode();

  protected:
  RegTreeSetNode(const RegTreeNode * parent); /* creates and initializes an empty set */
  static RegTreeSetNode * from(Utf8Buffer &, const RegTreeNode * = nullptr); /* Returns null, if buffer content does not match */

  private:
  static void predelete(const void *);

  friend class RegTreeNode;
};

class RegTreeAltNode : public RegTreeNode
{
  public:
  List * node_list; /* list of RegTreeNode alternatives */

  RegTreeAltNode() = delete;
  RegTreeAltNode(const RegTreeAltNode &) = delete;
  RegTreeAltNode(RegTreeAltNode &&) = delete;
  virtual ~RegTreeAltNode();

  protected:
  RegTreeAltNode(const RegTreeNode * parent); /* creates and initializes an empty list of alternatives */
  static RegTreeAltNode * from(const RegTreeNode *, Utf8Buffer &, const RegTreeNode * = nullptr); /* Returns null, if buffer content does not match */

  private:
  static void predelete(const void *);

  friend class RegTreeNode;
};

class RegTreeRepeatNode : public RegTreeNode
{
  public:
  const RegTreeNode * node;
  u16 repeat_min;
  u16 repeat_max; /* here, 0 means +infinity */

  RegTreeRepeatNode() = delete;
  RegTreeRepeatNode(const RegTreeRepeatNode &) = delete;
  RegTreeRepeatNode(RegTreeRepeatNode &&) = delete;
  virtual ~RegTreeRepeatNode();

  protected:
  RegTreeRepeatNode(const RegTreeNode *, const RegTreeNode *, u16 = 1, u16 = 1); /* {min,max}; "*"={0,+infty}; "+"={1,+infty}; "?"={0,1} */ // TODO: infinity
  static RegTreeRepeatNode * from(const RegTreeNode *, Utf8Buffer &, const RegTreeNode * = nullptr); /* Returns null, if buffer content does not match */

  friend class RegTreeNode;
};

class RegTreeGroupNode : public RegTreeNode
{
  public:
  const RegTreeNode * node; /* inner node */

  RegTreeGroupNode() = delete;
  RegTreeGroupNode(const RegTreeGroupNode &) = delete;
  RegTreeGroupNode(RegTreeGroupNode &&) = delete;
  virtual ~RegTreeGroupNode();

  protected:
  RegTreeGroupNode(const RegTreeNode * node, const RegTreeNode * parent = nullptr);
  static RegTreeGroupNode * from(Utf8Buffer &, const RegTreeNode * = nullptr); /* Returns null, if buffer content does not match */

  friend class RegTreeNode;
};

class RegTreeStringNode : public RegTreeNode
{
  public:
  JavaUtf8 * utf8; /* string, with ownership */

  RegTreeStringNode() = delete;
  RegTreeStringNode(const RegTreeStringNode &) = delete;
  RegTreeStringNode(RegTreeStringNode &&) = delete;
  virtual ~RegTreeStringNode();

  protected:
  RegTreeStringNode(const RegTreeNode *, JavaUtf8 *);
  static RegTreeStringNode * from(Utf8Buffer &, const RegTreeNode * = nullptr); /* Returns null, if buffer content does not match */

  private:
  struct Utf8Context;
  static bool predicate(jchar, void *);

  friend class RegTreeNode;
};

struct RegTreeStringNode::Utf8Context
{
  bool esc = false;
};


#endif

