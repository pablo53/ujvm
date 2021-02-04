#ifndef _CLASS_SIGNATURE_CPP
#define _CLASS_SIGNATURE_CPP


#include "signature.h"

#include "const.h"
#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../alg/buf.h"


inline bool is_identifier_char(jchar ch)
{
    return !(
        ch == SIGN_CLASS_TERM ||
        ch == SIGN_ARRAY ||
        ch == SIGN_SEPARATOR ||
        ch == SIGN_TYPE_BEGIN ||
        ch == SIGN_TYPE_END ||
        ch == SIGN_BOUND
    );
}

inline bool is_base_type_char(jchar ch)
{
    return !(
        ch == SIGN_BYTE ||
        ch == SIGN_CHAR ||
        ch == SIGN_DOUBLE ||
        ch == SIGN_FLOAT ||
        ch == SIGN_INT ||
        ch == SIGN_LONG ||
        ch == SIGN_SHORT ||
        ch == SIGN_BOOL
    );
}


SignatureNode::SignatureNode()
{
}

SignatureNode::~SignatureNode()
{
}


IdentifierSignatureNode::IdentifierSignatureNode(JavaUtf8 * identifier) : SignatureNode()
{
    this->identifier = identifier;
}

IdentifierSignatureNode * IdentifierSignatureNode::from(Utf8Buffer & buf)
{
    IdentifierSignatureNode * node = nullptr;
    
    JavaUtf8 * identifier =
        buf.take_until(
            [](jchar ch, void * ctx) -> bool { return is_identifier_char(ch); },
            nullptr
        );
    if (identifier)
        node = new IdentifierSignatureNode(identifier);

    return node;
}

IdentifierSignatureNode::~IdentifierSignatureNode()
{
    delete identifier;
}




TypeVariableSignatureNode::TypeVariableSignatureNode(IdentifierSignatureNode * identifier_node) : SignatureNode()
{
    this->identifier_node = identifier_node;
}

TypeVariableSignatureNode * TypeVariableSignatureNode::from(Utf8Buffer & buf)
{
    if (!buf.chars_left())
        return nullptr;
    jchar next = buf.peek();
    if (!(next == SIGN_TYPEVAR))
        return nullptr;
    u16 curs = buf.curs;
    buf.next(); /* consume type variable starting marker (SIGN_TYPEVAR) */

    IdentifierSignatureNode *identifier_node = IdentifierSignatureNode::from(buf);
    if (identifier_node)
        if (buf.chars_left())
            if (buf.next() == SIGN_CLASS_TERM)
                return new TypeVariableSignatureNode(identifier_node);

    delete identifier_node;
    buf.curs = curs; /* rewind */
    return nullptr;
}

TypeVariableSignatureNode::~TypeVariableSignatureNode()
{
    delete identifier_node;
}


BaseTypeSignatureNode::BaseTypeSignatureNode(jchar type_symbol) : SignatureNode()
{
    this->type_symbol = type_symbol;
}

BaseTypeSignatureNode * BaseTypeSignatureNode::from(Utf8Buffer & buf)
{
    BaseTypeSignatureNode * node = nullptr;

    if (buf.chars_left())
    {
        jchar next = buf.peek();
        if (is_base_type_char(next))
            node = new BaseTypeSignatureNode(next);
    }

    return node;
}

BaseTypeSignatureNode::~BaseTypeSignatureNode()
{
}


#endif
