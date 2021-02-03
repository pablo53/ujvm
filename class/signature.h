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
};


#endif
