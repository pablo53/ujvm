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

IdentifierSignatureNode * IdentifierSignatureNode::from(Utf8Buffer & buf, bool allow_sep)
{
    JavaUtf8 * identifier =
        buf.take_until(
            allow_sep
                ? [](jchar ch, void * ctx) -> bool { return is_identifier_char(ch) || (ch == SIGN_SEPARATOR); }
                : [](jchar ch, void * ctx) -> bool { return is_identifier_char(ch); },
            nullptr
        );
    if (identifier)
    {
        if (identifier->get_length() > 0)
            if ((identifier->get_jchar(0) != SIGN_SEPARATOR) && (identifier->get_jchar(identifier->get_length() - 1) != SIGN_SEPARATOR))
                return new IdentifierSignatureNode(identifier);
        delete identifier;
    }

    return nullptr;
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


ClassTypeSignatureNode::ClassTypeSignatureNode(u8 no_id_nodes, IdentifierSignatureNode ** identifier_nodes, TypeArgumentsSignatureNode ** type_arguments_nodes) : SignatureNode()
{
    this->no_id_nodes = no_id_nodes;
    this->identifier_nodes = identifier_nodes;
    this->type_arguments_nodes = type_arguments_nodes;
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
    TypeArgumentsSignatureNode* type_arguments_nodes[255];
    bool fail = false;
    u16 curs2;
    while (no_id_nodes < 255)
    {
        identifier_nodes[no_id_nodes] = IdentifierSignatureNode::from(buf, !no_id_nodes);
        if (!identifier_nodes[no_id_nodes])
        {
            fail = true;
            break;
        }
        curs2 = buf.curs;
        type_arguments_nodes[no_id_nodes] = TypeArgumentsSignatureNode::from(buf);
        if (!type_arguments_nodes[no_id_nodes])
            buf.curs = curs2;
        no_id_nodes++;
        if (buf.chars_left())
        {
            next = buf.next();
            if (next == SIGN_CLASS_TERM)
                break;
            else if (next != SIGN_NEST_SEP)
                fail = true;
        }
        else
            fail = true;
        if (fail)
            break;
    }
    if (fail)
    {
        for (int i = 0; i < no_id_nodes; i++)
        {
            delete identifier_nodes[i];
            delete type_arguments_nodes[i];
        }
        buf.curs = curs;
        return nullptr;
    }
    IdentifierSignatureNode ** identifier_nodes_dynamic = new IdentifierSignatureNode*[no_id_nodes]; // TODO: check if not nullptr
    TypeArgumentsSignatureNode ** type_arguments_nodes_dynamic = new TypeArgumentsSignatureNode*[no_id_nodes]; // TODO: check if not nullptr
    for (int i = 0; i < no_id_nodes; i++)
    {
        identifier_nodes_dynamic[i] = identifier_nodes[i];
        type_arguments_nodes_dynamic[i] = type_arguments_nodes[i];
    }
    
    return new ClassTypeSignatureNode(no_id_nodes, identifier_nodes_dynamic, type_arguments_nodes_dynamic);
}

ClassTypeSignatureNode::~ClassTypeSignatureNode()
{
    if (identifier_nodes)
        for (int i = 0; i < no_id_nodes; i++)
        {
            delete identifier_nodes[i];
            delete type_arguments_nodes[i];
        }
    delete[] identifier_nodes;
    delete[] type_arguments_nodes;
}


RefTypeSignature::RefTypeSignature(ClassTypeSignatureNode * class_type_node, TypeVariableSignatureNode * type_variable_node, ArrayTypeSignatureNode * array_type_node)
        : class_type_node(class_type_node), type_variable_node(type_variable_node), array_type_node(array_type_node)
{
}

RefTypeSignature * RefTypeSignature::from(Utf8Buffer & buf)
{
    u16 curs = buf.curs;
    ClassTypeSignatureNode * class_type_node = ClassTypeSignatureNode::from(buf);
    if (!class_type_node)
        return new RefTypeSignature(class_type_node, nullptr, nullptr);
    else
        buf.curs = curs;
    TypeVariableSignatureNode * type_variable_node = TypeVariableSignatureNode::from(buf);
    if (!type_variable_node)
        return new RefTypeSignature(nullptr, type_variable_node, nullptr);
    else
        buf.curs = curs;
    ArrayTypeSignatureNode * array_type_node = ArrayTypeSignatureNode::from(buf);
    if (!array_type_node)
        return new RefTypeSignature(nullptr, nullptr, array_type_node);
    else
    {
        buf.curs = curs;
        return nullptr;
    }
}

RefTypeSignature::~RefTypeSignature()
{
    delete class_type_node;
    delete type_variable_node;
    delete array_type_node;
}


ArrayTypeSignatureNode::ArrayTypeSignatureNode(RefTypeSignature * ref_type_node, BaseTypeSignatureNode * base_type_node)
        : ref_type_node(ref_type_node), base_type_node(base_type_node)
{
}

ArrayTypeSignatureNode * ArrayTypeSignatureNode::from(Utf8Buffer & buf)
{
    if (!buf.chars_left())
        return nullptr;
    jchar next = buf.peek();
    if (!(next == SIGN_ARRAY))
        return nullptr;
    u16 curs = buf.curs;
    buf.next(); /* consume type variable starting marker (SIGN_ARRAY) */
    u16 curs2 = buf.curs;
    RefTypeSignature * ref_type_node = RefTypeSignature::from(buf);
    if (!ref_type_node)
        return new ArrayTypeSignatureNode(ref_type_node, nullptr);
    else
        buf.curs = curs2;
    BaseTypeSignatureNode * base_type_node = BaseTypeSignatureNode::from(buf);
    if (!base_type_node)
        return new ArrayTypeSignatureNode(nullptr, base_type_node);
    else
    {
        buf.curs = curs;
        return nullptr;
    }
}

ArrayTypeSignatureNode::~ArrayTypeSignatureNode()
{
    delete ref_type_node;
    delete base_type_node;
}


TypeArgumentSignatureNode::TypeArgumentSignatureNode(jchar vartype, RefTypeSignature * ref_type_node)
        : vartype(vartype), ref_type_node(ref_type_node)
{
}

TypeArgumentSignatureNode * TypeArgumentSignatureNode::from(Utf8Buffer & buf)
{
    if (!buf.chars_left())
        return nullptr;
    jchar next = buf.peek();
    if ((next != SIGN_COVAR) && (next != SIGN_CONTRAVAR) && (next != SIGN_ANY))
        return nullptr;
    u16 curs = buf.curs;
    buf.next(); /* consume variance type marker */
    if (next == SIGN_ANY)
        return new TypeArgumentSignatureNode(next, nullptr);
    RefTypeSignature * ref_type_node = RefTypeSignature::from(buf);
    if (ref_type_node)
        return new TypeArgumentSignatureNode(next, ref_type_node);
    else
    {
        buf.curs = curs;
        return nullptr;
    }
}

TypeArgumentSignatureNode::~TypeArgumentSignatureNode()
{
    delete ref_type_node;
}


TypeArgumentsSignatureNode::TypeArgumentsSignatureNode(u8 no_typ_args, TypeArgumentSignatureNode ** type_arguments)
        : no_typ_args(no_typ_args), type_arguments(type_arguments)
{
}

TypeArgumentsSignatureNode * TypeArgumentsSignatureNode::from(Utf8Buffer & buf)
{
    if (!buf.chars_left())
        return nullptr;
    jchar next = buf.peek();
    if (next != SIGN_TYPE_BEGIN)
        return nullptr;
    u16 curs = buf.curs;
    buf.next(); /* consume opening char */
    u8 no_typ_args = 0;
    TypeArgumentSignatureNode * type_arguments[255];
    bool test = true;
    u16 curs2;
    while (no_typ_args < 255)
    {
        curs2 = buf.curs;
        type_arguments[no_typ_args] = TypeArgumentSignatureNode::from(buf);
        if (!type_arguments[no_typ_args])
        {
            buf.curs = curs2; /* rewind after last unsuccessful read */
            break;
        }
        no_typ_args++;
    }
    if (no_typ_args && buf.chars_left())
        if (buf.next() == SIGN_TYPE_END)
        {
            TypeArgumentSignatureNode ** type_arguments = new TypeArgumentSignatureNode *[no_typ_args]; // TODO: check if not nullptr
            return new TypeArgumentsSignatureNode(no_typ_args, type_arguments);
        }

    for (int i = 0; i < no_typ_args; i++)
        delete type_arguments[i];
    buf.curs = curs;

    return nullptr;
}

TypeArgumentsSignatureNode::~TypeArgumentsSignatureNode()
{
    for (int i = 0; i < no_typ_args; i++)
        delete type_arguments[i];
    delete[] type_arguments;
}


TypeParameterSignatureNode::TypeParameterSignatureNode(IdentifierSignatureNode * identifier_node, u8 no_iface_bounds, RefTypeSignature * class_bound_node, RefTypeSignature ** iface_bound_nodes)
        : identifier_node(identifier_node), no_iface_bounds(no_iface_bounds), class_bound_node(class_bound_node), iface_bound_nodes(iface_bound_nodes)
{
}

TypeParameterSignatureNode * TypeParameterSignatureNode::from(Utf8Buffer & buf)
{
    // TODO
}

TypeParameterSignatureNode::~TypeParameterSignatureNode()
{
    delete identifier_node;
    delete class_bound_node;
    for (int i = 0; i < no_iface_bounds; i++)
        delete iface_bound_nodes[i];
    delete[] iface_bound_nodes;
}


TypeParametersSignatureNode::TypeParametersSignatureNode(u8 no_typ_params, TypeParameterSignatureNode ** type_parameters)
        : no_typ_params(no_typ_params), type_parameters(type_parameters)
{
}

TypeParametersSignatureNode * TypeParametersSignatureNode::from(Utf8Buffer & buf)
{
    // TODO
}

TypeParametersSignatureNode::~TypeParametersSignatureNode()
{
    for (int i = 0; i < no_typ_params; i++)
        delete type_parameters[i];
    delete[] type_parameters;
}


#endif
