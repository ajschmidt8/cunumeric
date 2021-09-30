/* Copyright 2021 NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "numpy/matrix/contract.h"
#include "numpy/matrix/contract_template.inl"
#include "numpy/matrix/util.h"

#include <tblis/tblis.h>

namespace legate {
namespace numpy {

using namespace Legion;
using namespace tblis;

// NOTE: The TBLIS tensor constructor requires all arguments to be passed as non-const pointers,
// so we treat certain arguments as mutable, even though we don't intent to mutate them.

template <>
struct ContractImplBody<VariantKind::CPU, LegateTypeCode::FLOAT_LT> {
  void operator()(float* lhs_data,
                  size_t lhs_ndim,
                  int64_t* lhs_shape,
                  int64_t* lhs_strides,
                  int32_t* lhs_modes,
                  const float* rhs1_data,
                  size_t rhs1_ndim,
                  int64_t* rhs1_shape,
                  int64_t* rhs1_strides,
                  int32_t* rhs1_modes,
                  const float* rhs2_data,
                  size_t rhs2_ndim,
                  int64_t* rhs2_shape,
                  int64_t* rhs2_strides,
                  int32_t* rhs2_modes)
  {
    tblis_tensor lhs;
    tblis_init_tensor_s(&lhs, lhs_ndim, lhs_shape, lhs_data, lhs_strides);

    tblis_tensor rhs1;
    tblis_init_tensor_s(&rhs1, rhs1_ndim, rhs1_shape, const_cast<float*>(rhs1_data), rhs1_strides);

    tblis_tensor rhs2;
    tblis_init_tensor_s(&rhs2, rhs2_ndim, rhs2_shape, const_cast<float*>(rhs2_data), rhs2_strides);

    tblis_tensor_mult(tblis_single, NULL, &lhs, lhs_modes, &rhs1, rhs1_modes, &rhs2, rhs2_modes);
  }
};

template <>
struct ContractImplBody<VariantKind::CPU, LegateTypeCode::DOUBLE_LT> {
  void operator()(double* lhs_data,
                  size_t lhs_ndim,
                  int64_t* lhs_shape,
                  int64_t* lhs_strides,
                  int32_t* lhs_modes,
                  const double* rhs1_data,
                  size_t rhs1_ndim,
                  int64_t* rhs1_shape,
                  int64_t* rhs1_strides,
                  int32_t* rhs1_modes,
                  const double* rhs2_data,
                  size_t rhs2_ndim,
                  int64_t* rhs2_shape,
                  int64_t* rhs2_strides,
                  int32_t* rhs2_modes)
  {
    tblis_tensor lhs;
    tblis_init_tensor_d(&lhs, lhs_ndim, lhs_shape, lhs_data, lhs_strides);

    tblis_tensor rhs1;
    tblis_init_tensor_d(&rhs1, rhs1_ndim, rhs1_shape, const_cast<double*>(rhs1_data), rhs1_strides);

    tblis_tensor rhs2;
    tblis_init_tensor_d(&rhs2, rhs2_ndim, rhs2_shape, const_cast<double*>(rhs2_data), rhs2_strides);

    tblis_tensor_mult(tblis_single, NULL, &lhs, lhs_modes, &rhs1, rhs1_modes, &rhs2, rhs2_modes);
  }
};

template <>
struct ContractImplBody<VariantKind::CPU, LegateTypeCode::COMPLEX64_LT> {
  void operator()(complex<float>* lhs_data,
                  size_t lhs_ndim,
                  int64_t* lhs_shape,
                  int64_t* lhs_strides,
                  int32_t* lhs_modes,
                  const complex<float>* rhs1_data,
                  size_t rhs1_ndim,
                  int64_t* rhs1_shape,
                  int64_t* rhs1_strides,
                  int32_t* rhs1_modes,
                  const complex<float>* rhs2_data,
                  size_t rhs2_ndim,
                  int64_t* rhs2_shape,
                  int64_t* rhs2_strides,
                  int32_t* rhs2_modes)
  {
    tblis_tensor lhs;
    tblis_init_tensor_c(&lhs, lhs_ndim, lhs_shape, lhs_data, lhs_strides);

    tblis_tensor rhs1;
    tblis_init_tensor_c(
      &rhs1, rhs1_ndim, rhs1_shape, const_cast<complex<float>*>(rhs1_data), rhs1_strides);

    tblis_tensor rhs2;
    tblis_init_tensor_c(
      &rhs2, rhs2_ndim, rhs2_shape, const_cast<complex<float>*>(rhs2_data), rhs2_strides);

    tblis_tensor_mult(tblis_single, NULL, &lhs, lhs_modes, &rhs1, rhs1_modes, &rhs2, rhs2_modes);
  }
};

template <>
struct ContractImplBody<VariantKind::CPU, LegateTypeCode::COMPLEX128_LT> {
  void operator()(complex<double>* lhs_data,
                  size_t lhs_ndim,
                  int64_t* lhs_shape,
                  int64_t* lhs_strides,
                  int32_t* lhs_modes,
                  const complex<double>* rhs1_data,
                  size_t rhs1_ndim,
                  int64_t* rhs1_shape,
                  int64_t* rhs1_strides,
                  int32_t* rhs1_modes,
                  const complex<double>* rhs2_data,
                  size_t rhs2_ndim,
                  int64_t* rhs2_shape,
                  int64_t* rhs2_strides,
                  int32_t* rhs2_modes)
  {
    tblis_tensor lhs;
    tblis_init_tensor_z(&lhs, lhs_ndim, lhs_shape, lhs_data, lhs_strides);

    tblis_tensor rhs1;
    tblis_init_tensor_z(
      &rhs1, rhs1_ndim, rhs1_shape, const_cast<complex<double>*>(rhs1_data), rhs1_strides);

    tblis_tensor rhs2;
    tblis_init_tensor_z(
      &rhs2, rhs2_ndim, rhs2_shape, const_cast<complex<double>*>(rhs2_data), rhs2_strides);

    tblis_tensor_mult(tblis_single, NULL, &lhs, lhs_modes, &rhs1, rhs1_modes, &rhs2, rhs2_modes);
  }
};

/*static*/ void ContractTask::cpu_variant(TaskContext& context)
{
  contract_template<VariantKind::CPU>(context);
}

namespace  // unnamed
{
static void __attribute__((constructor)) register_tasks(void) { ContractTask::register_variants(); }
}  // namespace

}  // namespace numpy
}  // namespace legate
