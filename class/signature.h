#ifndef _CLASS_SIGNATURE_H
#define _CLASS_SIGNATURE_H


#include "../defs/types.h"
#include "../alg/buf.h"


class SignatureNode
{
    public:
    SignatureNode();
    SignatureNode(const SignatureNode &) = delete;
    SignatureNode(SignatureNode &&) = delete;
    virtual ~SignatureNode() = 0;
};

class IdentifierSignatureNode : public SignatureNode
{
    public:
    JavaUtf8 * identifier; /* with ownership */

    IdentifierSignatureNode(const IdentifierSignatureNode &) = delete;
    IdentifierSignatureNode(IdentifierSignatureNode &&) = delete;
    virtual ~IdentifierSignatureNode();

    protected:
    static IdentifierSignatureNode * from(Utf8Buffer &); /* returns IdentifierSignatureNode with ownership */

    private:
    IdentifierSignatureNode(JavaUtf8 *);

    friend class TypeVariableSignatureNode;
    friend class ClassTypeSignatureNode;
};

class RefTypeSignature;

class TypeVariableSignatureNode : public SignatureNode
{
    public:
    IdentifierSignatureNode * identifier_node; /* with ownership */

    TypeVariableSignatureNode(const TypeVariableSignatureNode &) = delete;
    TypeVariableSignatureNode(TypeVariableSignatureNode &&) = delete;
    virtual ~TypeVariableSignatureNode();

    protected:
    static TypeVariableSignatureNode * from(Utf8Buffer &); /* returns TypeVariableSignatureNode with ownership */

    private:
    TypeVariableSignatureNode(IdentifierSignatureNode *);

    friend class RefTypeSignature;
};

class ArrayTypeSignatureNode;

class BaseTypeSignatureNode : public SignatureNode
{
    public:
    jchar type_symbol;

    BaseTypeSignatureNode(const BaseTypeSignatureNode &) = delete;
    BaseTypeSignatureNode(BaseTypeSignatureNode &&) = delete;
    virtual ~BaseTypeSignatureNode();

    protected:
    static BaseTypeSignatureNode * from(Utf8Buffer &); /* returns BaseTypeSignatureNode with ownership */

    private:
    BaseTypeSignatureNode(jchar);

    friend class ArrayTypeSignatureNode;
};

class TypeArgumentsSignatureNode;

class ClassTypeSignatureNode : public SignatureNode
{
    public:
    u8 no_id_nodes; /* size of array of identifier nodes, no more than 255 as per JVM specs */
    IdentifierSignatureNode ** identifier_nodes; /* with ownership */
    TypeArgumentsSignatureNode * type_arguments_node; /* with ownership, can be nullptr */

    ClassTypeSignatureNode(const ClassTypeSignatureNode &) = delete;
    ClassTypeSignatureNode(ClassTypeSignatureNode &&) = delete;
    virtual ~ClassTypeSignatureNode();

    protected:
    static ClassTypeSignatureNode * from(Utf8Buffer &); /* returns ClassTypeSignatureNode with ownership */

    private:
    ClassTypeSignatureNode(u8, IdentifierSignatureNode **, TypeArgumentsSignatureNode *);

    friend class RefTypeSignature;
};

class ArrayTypeSignatureNode;
class TypeArgumentSignatureNode;

class RefTypeSignature : public SignatureNode
{
    public:
    ClassTypeSignatureNode * class_type_node;
    TypeVariableSignatureNode * type_variable_node;
    ArrayTypeSignatureNode * array_type_node;

    RefTypeSignature(const RefTypeSignature &) = delete;
    RefTypeSignature(RefTypeSignature &&) = delete;
    virtual ~RefTypeSignature();

    protected:
    static RefTypeSignature * from(Utf8Buffer &); /* returns RefTypeSignature with ownership */

    private:
    RefTypeSignature(ClassTypeSignatureNode * class_type_node, TypeVariableSignatureNode * type_variable_node, ArrayTypeSignatureNode * array_type_node);

    friend class ArrayTypeSignatureNode;
    friend class TypeArgumentSignatureNode;
};

class ArrayTypeSignatureNode : public SignatureNode
{
    public:
    RefTypeSignature * ref_type_node;
    BaseTypeSignatureNode * base_type_node;

    ArrayTypeSignatureNode(const ArrayTypeSignatureNode &) = delete;
    ArrayTypeSignatureNode(ArrayTypeSignatureNode &&) = delete;
    virtual ~ArrayTypeSignatureNode();

    protected:
    static ArrayTypeSignatureNode * from(Utf8Buffer &); /* returns ArrayTypeSignatureNode with ownership */

    private:
    ArrayTypeSignatureNode(RefTypeSignature *, BaseTypeSignatureNode *);

    friend class RefTypeSignature;
};

class TypeArgumentSignatureNode : public SignatureNode
{
    public:
    jchar vartype; /* variance ('+' or '-') or asterisk ('*') */
    RefTypeSignature * ref_type_node; /* if not asterisk */

    TypeArgumentSignatureNode(const TypeArgumentSignatureNode &) = delete;
    TypeArgumentSignatureNode(TypeArgumentSignatureNode &&) = delete;
    virtual ~TypeArgumentSignatureNode();

    protected:
    static TypeArgumentSignatureNode * from(Utf8Buffer &); /* returns TypeArgumentSignatureNode with ownership */

    private:
    TypeArgumentSignatureNode(jchar, RefTypeSignature *);

    friend class TypeArgumentsSignatureNode;
};

class TypeArgumentsSignatureNode : public SignatureNode
{
    public:
    u8 no_typ_args; /* size of table type_arguments */
    TypeArgumentSignatureNode ** type_arguments;

    TypeArgumentsSignatureNode(const TypeArgumentsSignatureNode &) = delete;
    TypeArgumentsSignatureNode(TypeArgumentsSignatureNode &&) = delete;
    virtual ~TypeArgumentsSignatureNode();

    protected:
    static TypeArgumentsSignatureNode * from(Utf8Buffer &); /* returns TypeArgumentsSignatureNode with ownership */

    private:
    TypeArgumentsSignatureNode(u8, TypeArgumentSignatureNode **);

    friend class ClassTypeSignatureNode;
};


#endif
