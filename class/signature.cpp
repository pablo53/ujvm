#ifndef _CLASS_SIGNATURE_CPP
#define _CLASS_SIGNATURE_CPP


#include "signature.h"

#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../alg/buf.h"


#define CHAR_SEMICOLON ';'
#define CHAR_ARRAY '['
#define CHAR_SEP '/'
#define CHAR_BRA '<'
#define CHAR_KET '>'
#define CHAR_COLON ':'

inline bool is_identifier_char(jchar ch)
{
    return !(
        ch == CHAR_SEMICOLON ||
        ch == CHAR_ARRAY ||
        ch == CHAR_SEP ||
        ch == CHAR_BRA ||
        ch == CHAR_KET ||
        ch == CHAR_COLON
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


#endif
