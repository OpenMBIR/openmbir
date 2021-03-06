/* ============================================================================
 * Copyright (c) 2011, Michael A. Jackson (BlueQuartz Software)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#ifndef _AbstractFilter_H_
#define _AbstractFilter_H_

#include <set>
#include <string>

#include "MXA/Common/MXASetGetMacros.h"


#include "MBIRLib/MBIRLib.h"

#include "MBIRLib/Common/Observable.h"




class MBIRLib_EXPORT AbstractFilter : public Observable
{
  public:
    MXA_SHARED_POINTERS(AbstractFilter)
    MXA_STATIC_NEW_MACRO(AbstractFilter)
    MXA_TYPE_MACRO_SUPER(AbstractFilter, Observable)

    virtual ~AbstractFilter();

    // These should be implemented by the subclass
    MXA_INSTANCE_STRING_PROPERTY(ErrorMessage);
    MXA_INSTANCE_PROPERTY(int, ErrorCondition);
    /**
     * @brief Cancel the operation
     */
    MXA_INSTANCE_PROPERTY(bool, Cancel);

    MXA_INSTANCE_PROPERTY(bool, Verbose);
    MXA_INSTANCE_PROPERTY(bool, VeryVerbose);

    virtual void printValues(std::ostream& out) {}


    /**
     * @brief This method should be fully implemented in subclasses.
     */
    virtual void execute();

  protected:
    AbstractFilter();



  private:
    AbstractFilter(const AbstractFilter&); // Copy Constructor Not Implemented
    void operator=(const AbstractFilter&); // Operator '=' Not Implemented
};




#endif /* _AbstractFilter_H_  */
