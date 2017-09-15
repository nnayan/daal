/* file: service_rng.h */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Template wrappers for RNG functions.
//--
*/


#ifndef __SERVICE_RNG_H__
#define __SERVICE_RNG_H__

#include "daal_defines.h"
#include "service_memory.h"
#include "service_rng_mkl.h"

using namespace daal::services;

namespace daal
{
namespace internal
{

template<CpuType cpu, typename _BaseGenerators = mkl::BaseRNG<cpu> >
class BaseRNGs : public BaseRNGIface<cpu>
{
public:
    BaseRNGs(const unsigned int _seed = 777, const int _brngId = __DAAL_BRNG_MT19937) : _baseRNG(_seed, _brngId) {}
    ~BaseRNGs() {}

    int getStateSize()
    {
        return _baseRNG.getStateSize();
    }

    int saveState(void* dest)
    {
        return _baseRNG.saveState(dest);
    }

    int loadState(const void* src)
    {
        return _baseRNG.loadState(src);
    }

    void* getState()
    {
        return _baseRNG.getState();
    }

    _BaseGenerators &getBrng()
    {
        return _baseRNG;
    }

private:
    _BaseGenerators _baseRNG;
};

template<typename Type, CpuType cpu, typename _RNGs = mkl::RNGs<Type, cpu> >
class RNGs
{
public:
    typedef typename _RNGs::SizeType SizeType;
    typedef typename _RNGs::BaseType BaseType;

    RNGs() {}
    ~RNGs() {}

    /* Generates random numbers uniformly distributed on the interval [a, b) */
    int uniform(const SizeType n, Type* r, BaseRNGs<cpu, BaseType> &brng, const Type a, const Type b, const int method = __DAAL_RNG_METHOD_UNIFORM_STD)
    {
        return _generators.uniform(n, r, brng.getBrng(), a, b, method);
    }

    int uniform(const SizeType n, Type* r, void *state, const Type a, const Type b, const int method = __DAAL_RNG_METHOD_UNIFORM_STD)
    {
        return _generators.uniform(n, r, state, a, b, method);
    }

    int bernoulli(const SizeType n, Type* r, BaseRNGs<cpu, BaseType> &brng, const double p, const int method = __DAAL_RNG_METHOD_BERNOULLI_ICDF)
    {
        return _generators.bernoulli(n, r, brng.getBrng(), p, method);
    }

    int bernoulli(const SizeType n, Type* r, void *state, const double p, const int method = __DAAL_RNG_METHOD_BERNOULLI_ICDF)
    {
        return _generators.bernoulli(n, r, state, p, method);
    }

    int gaussian(const SizeType n, Type* r, BaseRNGs<cpu, BaseType> &brng, const Type a, const Type sigma, const int method = __DAAL_RNG_METHOD_GAUSSIAN_ICDF)
    {
        return _generators.gaussian(n, r, brng.getBrng(), a, sigma, method);
    }

    int gaussian(const SizeType n, Type* r, void *state, const Type a, const Type sigma, const int method = __DAAL_RNG_METHOD_GAUSSIAN_ICDF)
    {
        return _generators.gaussian(n, r, state, a, sigma, method);
    }

    int uniformWithoutReplacement(const SizeType n, Type* r, BaseRNGs<cpu, BaseType> &brng, const Type a, const Type b, const int method = __DAAL_RNG_METHOD_UNIFORM_STD)
    {
        int errorcode = 0;
        for (SizeType i = 0; i < n; i++)
        {
            errorcode = uniform(1, r + i, brng, a + i, b, method);
        }
        for (SizeType i = 0; i < n; i++)
        {
            int shift = 0;
            for (SizeType j = 0; j < i; j++)
            {
                shift += (r[i] <= r[j]);
            }
            r[i] -= shift;
        }
        return errorcode;
    }

private:
    _RNGs _generators;
};

} // namespace internal
} // namespace daal

#endif
