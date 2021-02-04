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
};

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
};

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
};


#endif
