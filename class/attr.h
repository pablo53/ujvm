#ifndef _CLASS_ATTR_H
#define _CLASS_ATTR_H


class JavaAttribute; /* forward declaration due to circular dependencies */

#include "utf8.h"
#include "class.h"
#include "code.h"
#include "../defs/types.h"
#include "../classfmt/attr.h"
#include "../classfmt/clsfile.h"
#include "../classldr/cloader.h"
#include "../defs/err.h"

/* The following constants are used internally, and are not defined by JVM specification. */
#define JATTR_UNKNOWN                                   0
#define JATTR_CONSTANT_VALUE                            1
#define JATTR_CODE                                      2
#define JATTR_STACK_MAP_TABLE                           3
#define JATTR_EXCEPTIONS                                4
#define JATTR_INNER_CLASSES                             5
#define JATTR_ENCLOSING_METHOD                          6
#define JATTR_SYNTHETIC                                 7
#define JATTR_SIGNATURE                                 8
#define JATTR_SOURCE_FILE                               9
#define JATTR_SOURCE_DEBUG_EXTENSION                   10
#define JATTR_LINE_NUMBER                              11
#define JATTR_LOCAL_VARIABLE_TABLE                     12
#define JATTR_LOCAL_VARIABLE_TYPE                      13
#define JATTR_DEPRECATED                               14
#define JATTR_RUNTIME_VISIBLE_ANNOTATIONS              15
#define JATTR_RUNTIME_INVISIBLE_ANNOTATIONS            16
#define JATTR_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS    17
#define JATTR_RUNTIME_INVISIBLE_PARAMETER_ANNOTATIONS  18
#define JATTR_RUNTIME_VISIBLE_TYPE_ANNOTATIONS         19
#define JATTR_RUNTIME_INVISIBLE_TYPE_ANNOTATIONS       20
#define JATTR_ANNOTATION_DEFAULT                       21
#define JATTR_BOOTSTRAP_METHODS                        22
#define JATTR_METHOD_PARAMETERS                        23

class JavaAttribute
{
  public:
  u8 jattr_typ; /* as per JATTR_* const */
  u8 err; /* state */

  JavaAttribute(const JavaAttribute &) = delete;
  JavaAttribute(JavaAttribute &&) = delete;
  virtual ~JavaAttribute() = 0;

  protected:
  JavaAttribute(u8);
};

class JavaAttributeUnknown : public JavaAttribute
{
  public:
  JavaUtf8 * name;
  u32 length;
  u8 * info; /* a table of 'length' elements */

  JavaAttributeUnknown() = delete;
  JavaAttributeUnknown(const AttributeInfo &, const ClassFile &);
  virtual ~JavaAttributeUnknown();
};

class JavaAttributeCode : public JavaAttribute
{
  public:
  u16 max_stack;
  u16 max_locals;
  u32 code_length;
  u8 * code;
  JavaInstruction ** instr; /* (sparse) array of instructions of length code_length, indexed by instruction offset (nullptr = no instruction at given offset) */
  u16 exception_cnt;
  struct Exception
  {
    u16 start_pc;
    u16 end_pc;
    u16 handler_pc;
    JavaClass * catch_type; /* no ownership of this pointer; it should come from Class Loader */
  } * exceptions;
  u16 attr_cnt;
  JavaAttribute ** attributes;

  JavaAttributeCode() = delete;
  JavaAttributeCode(const AttributeInfo &, const ClassFile &, JavaClassLoader *);
  virtual ~JavaAttributeCode();

  private:
  void decode_instr(u32 offset);
};

class JavaAttributeExceptions : public JavaAttribute
{
  public:
  u16 exception_cnt;
  JavaClass ** exceptions;
  
  JavaAttributeExceptions() = delete;
  JavaAttributeExceptions(const JavaAttributeExceptions &) = delete;
  JavaAttributeExceptions(AttributeInfo &, const ClassFile &, JavaClassLoader *); /* no ownership of ClassLoader taken */
  virtual ~JavaAttributeExceptions();
};

#ifndef BASIC_JATTR_ONLY

class JavaAttributeSourceFile : public JavaAttribute
{
  public:
  JavaUtf8 * src_file_name;

  JavaAttributeSourceFile() = delete;
  JavaAttributeSourceFile(const AttributeInfo &, const ClassFile &);
  virtual ~JavaAttributeSourceFile();
};

#endif

JavaAttribute * convert2jattr(AttributeInfo & attr_info, const ClassFile &clsfile, JavaClassLoader * clsloader); /* factory method */


#endif
