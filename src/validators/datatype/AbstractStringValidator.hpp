/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 2001, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id$
 * $Log$
 * Revision 1.2  2001/09/19 18:48:27  peiyongz
 * DTV reorganization:getLength() added, move inline to class declaration to avoid inline
 * function interdependency.
 *
 * Revision 1.1  2001/09/18 14:45:04  peiyongz
 * DTV reorganization
 *
 */

#if !defined(ABSTRACT_STRING_VALIDATOR_HPP)
#define ABSTRACT_STRING_VALIDATOR_HPP

#include <validators/datatype/DatatypeValidator.hpp>
#include <validators/datatype/InvalidDatatypeFacetException.hpp>

class VALIDATORS_EXPORT AbstractStringValidator : public DatatypeValidator
{
public:

    // -----------------------------------------------------------------------
    //  Public ctor/dtor
    // -----------------------------------------------------------------------
	/** @name Constructor. */
    //@{

    virtual ~AbstractStringValidator();

	//@}

    // -----------------------------------------------------------------------
    // Validation methods
    // -----------------------------------------------------------------------
    /** @name Validation Function */
    //@{

    /**
     * validate that a string matches the boolean datatype
     * @param content A string containing the content to be validated
     *
     * @exception throws InvalidDatatypeException if the content is
     * is not valid.
     */

	inline void validate(const XMLCh* const content);

    //@}

    // -----------------------------------------------------------------------
    // Compare methods
    // -----------------------------------------------------------------------
    /** @name Compare Function */
    //@{

    inline int compare(const XMLCh* const, const XMLCh* const);

    //@}

    /**
      * Returns an instance of the base datatype validator class
	  * Used by the DatatypeValidatorFactory.
      */
    DatatypeValidator* newInstance(RefHashTableOf<KVStringPair>* const facets
                                 , RefVectorOf<XMLCh>*           const enums
                                 , const int                           finalSet)
                                 = 0;

protected:

    AbstractStringValidator(DatatypeValidator*            const baseValidator
                          , RefHashTableOf<KVStringPair>* const facets
                          , RefVectorOf<XMLCh>*           const enums
                          , const int                           finalSet
                          , const ValidatorType                 type);

    // derived classes may have their own copy for any of the followings
    //
    inline virtual void assignAdditionalFacet(const XMLCh* const key
                                            , const XMLCh* const value);

    inline virtual void inheritAdditionalFacet();

    inline virtual void checkAdditionalFacetConstraints() const;

    inline virtual void checkAdditionalFacet(const XMLCh* const content) const;

    inline virtual void checkValueSpace(const XMLCh* const content);

    inline virtual int  getLength(const XMLCh* const content) const;

private:

    void checkContent(const XMLCh* const content, bool asBase);

    void init(DatatypeValidator*            const baseValidator
            , RefHashTableOf<KVStringPair>* const facets
            , RefVectorOf<XMLCh>*           const enums);

    inline void cleanUp();

// -----------------------------------------------------------------------
// Getter methods
// -----------------------------------------------------------------------

    inline unsigned int         getLength() const;

    inline unsigned int         getMaxLength() const;

    inline unsigned int         getMinLength() const;

    inline RefVectorOf<XMLCh>*  getEnumeration() const;

// -----------------------------------------------------------------------
// Setter methods
// -----------------------------------------------------------------------

    inline void                 setLength(unsigned int);

    inline void                 setMaxLength(unsigned int);

    inline void                 setMinLength(unsigned int);

    inline void                 setEnumeration(RefVectorOf<XMLCh>*, bool);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    // -----------------------------------------------------------------------
     unsigned int         fLength;
     unsigned int         fMaxLength;
     unsigned int         fMinLength;
     bool                 fEnumerationInherited;
     RefVectorOf<XMLCh>*  fEnumeration;
};

// -----------------------------------------------------------------------
// Compare methods
// -----------------------------------------------------------------------
int AbstractStringValidator::compare(const XMLCh* const lValue
                                          , const XMLCh* const rValue)
{
    return XMLString::compareString(lValue, rValue);
}

void AbstractStringValidator::validate( const XMLCh* const content)
{
    checkContent(content, false);
}

void AbstractStringValidator::cleanUp()
{
    //~RefVectorOf will delete all adopted elements
    if (fEnumeration && !fEnumerationInherited)
        delete fEnumeration;
}

// -----------------------------------------------------------------------
// Getter methods
// -----------------------------------------------------------------------

unsigned int AbstractStringValidator::getLength() const
{
    return fLength;
}

unsigned int AbstractStringValidator::getMaxLength() const
{
    return fMaxLength;
}

unsigned int AbstractStringValidator::getMinLength() const
{
    return fMinLength;
}

RefVectorOf<XMLCh>* AbstractStringValidator:: getEnumeration() const
{
    return fEnumeration;
}

// -----------------------------------------------------------------------
// Setter methods
// -----------------------------------------------------------------------

void AbstractStringValidator::setLength(unsigned int newLength)
{
    fLength = newLength;
}

void AbstractStringValidator::setMaxLength(unsigned int newMaxLength)
{
    fMaxLength = newMaxLength;
}

void AbstractStringValidator::setMinLength(unsigned int newMinLength)
{
    fMinLength = newMinLength;
}

void AbstractStringValidator::setEnumeration(RefVectorOf<XMLCh>* enums
                                           , bool                inherited)
{
    if (enums)
    {
        if (fEnumeration && !fEnumerationInherited)
            delete fEnumeration;

        fEnumeration = enums;
        fEnumerationInherited = inherited;
        setFacetsDefined(DatatypeValidator::FACET_ENUMERATION);
    }
}

// -----------------------------------------------------------------------
// Utility methods
// -----------------------------------------------------------------------
void AbstractStringValidator::assignAdditionalFacet( const XMLCh* const
                                                          , const XMLCh* const)
{
    ThrowXML(InvalidDatatypeFacetException, XMLExcepts::FACET_Invalid_Tag);
}

void AbstractStringValidator::inheritAdditionalFacet()
{}

void AbstractStringValidator::checkAdditionalFacetConstraints() const
{}

void AbstractStringValidator::checkAdditionalFacet(const XMLCh* const) const
{}

void AbstractStringValidator::checkValueSpace(const XMLCh* const)
{}

int AbstractStringValidator::getLength(const XMLCh* const content) const
{
    return XMLString::stringLen(content);
}

/**
  * End of file AbstractStringValidator.hpp
  */
#endif
