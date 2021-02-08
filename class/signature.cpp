#ifndef _CLASS_SIGNATURE_CPP
#define _CLASS_SIGNATURE_CPP


#include "signature.h"

#include "const.h"
#include "../defs/types.h"
#include "../defs/utf8.h"
#include "../alg/buf.h"
#include "../alg/list.h"


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


ClassTypeSignatureNode::ClassTypeSignatureNode(u8 no_id_nodes, IdentifierSignatureNode ** identifier_nodes, TypeArgumentsSignatureNode * type_arguments_node) : SignatureNode()
{
    this->no_id_nodes = no_id_nodes;
    this->identifier_nodes = identifier_nodes;
    this->type_arguments_node = type_arguments_node;
}

ClassTypeSignatureNode * ClassTypeSignatureNode::from(Utf8Buffer & buf)
{
    if (!buf.chars_left())
        return nullptr;
    jchar next = buf.peek();
    if (!(next == SIGN_CLASS))
        return nullptr;
    u16 curs = buf.curs;
    buf.next(); /* consume type variable starting marker (SIGN_CLASS) */
    u8 no_id_nodes = 0;
    IdentifierSignatureNode* identifier_nodes[255];
    IdentifierSignatureNode* identifier_node = nullptr;
    TypeArgumentsSignatureNode* type_arguments_node = nullptr;
    bool test;
    bool check_more;
    do
    {
        identifier_node = IdentifierSignatureNode::from(buf);
        test = identifier_node && (no_id_nodes < 255) && buf.chars_left();
        if (test)
        {
            next = buf.peek();
            check_more = (next == SIGN_SEPARATOR);
            if ((next == SIGN_SEPARATOR) || (next == SIGN_CLASS_TERM))
                buf.next(); /* consume peeked char */
            else
            {
                test = (type_arguments_node = TypeArgumentsSignatureNode::from(buf));
                test = test && buf.chars_left();
                if (test)
                    test = (buf.next() == SIGN_CLASS_TERM);
            }
        }
        if (!test)
        {
            buf.curs = curs; /* Rewind the buffer */
            delete type_arguments_node;
            delete identifier_node;
            for (int i = 0; i < no_id_nodes; i++)
                delete identifier_nodes[i];
            return nullptr;
        }
        identifier_nodes[no_id_nodes++] = identifier_node;
    } while (check_more);
    IdentifierSignatureNode ** identifier_nodes_dynamic = new IdentifierSignatureNode*[no_id_nodes]; // TODO: check if not nullptr
    for (int i = 0; i < no_id_nodes; i++)
        identifier_nodes_dynamic[i] = identifier_nodes[i];
    
    return new ClassTypeSignatureNode(no_id_nodes, identifier_nodes_dynamic, type_arguments_node);
}

ClassTypeSignatureNode::~ClassTypeSignatureNode()
{
    if (identifier_nodes)
        for (int i = 0; i < no_id_nodes; i++)
            delete identifier_nodes[i];
    delete[] identifier_nodes;
    delete type_arguments_node;
}


TypeArgumentsSignatureNode::TypeArgumentsSignatureNode()
{
    // TODO
}

TypeArgumentsSignatureNode * TypeArgumentsSignatureNode::from(Utf8Buffer & buf)
{
    return nullptr; // TODO
}

TypeArgumentsSignatureNode::~TypeArgumentsSignatureNode()
{
    // TODO
}


#endif
