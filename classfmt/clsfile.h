#ifndef _CLSFILE_H
#define _CLSFILE_H


#include "cpool.h"
#include "fld.h"
#include "meth.h"
#include "attr.h"

#include "../defs/types.h"

/*
 * A class representing a raw *.class.
 * Originally, *.class files use BigEndian convention.
 * Here, the number are converted accordingly to represent
 * the numbers as per the underlying architecture.
 * 
 * This is the 1st-stage representation of a Java class.
 */
class ClassFile
{
  public:
  u32 magic;          /* 0xCAFEBABE */
  u16 minor_ver;      /* Minor version number of the class file format. */
  u16 major_ver;      /* Major version number of the class file format. Java 1.1 = 0x2D, 1.2 = 0x2E, ... */
  u16 const_pool_cnt; /* Constant pool count (N+1). */
  ConstPoolEntry * const_pool; /* Indexed 1..N (1-based) */
  u16 access_flags;
  u16 this_class;     /* An index of a const_pool entry (of type "Class") */
  u16 super_class;    /* An index of a const_pool entry (of type "Class") */
  u16 iface_cnt;      /* Interface count. */
  u16 * interfaces;   /* An array of iface_cnt indices of const_pool entries. */
  u16 field_cnt;      /* Field count. */
  FieldInfo * fields; /* An array of field_cnt Field infos. */
  u16 method_cnt;       /* Method count. */
  MethodInfo * methods; /* An array of method_cnt Method infos. */
  u16 attr_cnt;               /* Attribute count. */
  AttributeInfo * attributes; /* An array of attr_cnt indices of pointers to Attribute infos. */
  
  ClassFile(const u8 * buf, size_t buflen);
  ClassFile(const ClassFile &) = delete; /* No implicit copying constructor */
  ClassFile(ClassFile &&); /* Explicit moving constructor (no implicit one due to the existing destructor) */
  ~ClassFile();

  protected:
  void load(const u8 * buf, size_t buflen);
  void unlink(void);
};

CPUtf8Info * class_name_from_file(const ClassFile &clsfile);


#endif
