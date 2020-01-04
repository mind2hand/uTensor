#ifndef UTENSOR_TENSOR_H
#define UTENSOR_TENSOR_H

#include "memoryManagementInterface.hpp"
#include "tensorBase.hpp"
#include "utensor_string.hpp"

namespace uTensor {
// Tensors also appear on the same heap as the Tensor metadata. This way we can
// move tensors around and delete them without affecting user code
// template <typename Allocator=utensor::DefaultTensorMetaDataAllocator>
class Tensor : public Handle {
  // private:
  //    // Cannot copy Tensors, must pass by reference
  //    Tensor(const Tensor& that);
  // enum Type : uint8_t { TENSOR_IFC_PTR, TENSOR_HANDLE_PTR } type;

 public:
  TensorInterface* operator->();
  // As long as operating on instantiations of this class and not pointers this function will work
  TensorInterface* operator*();
  Tensor(TensorInterface* ptr);
  Tensor& operator=(TensorInterface* ptr);
  Tensor(Tensor&& that);
  Tensor& operator=(Tensor&& that);
  // Add some bits to make the interface nicer to the user

  // Force everything to be on the utensor allocator
  void* operator new(size_t sz);
  void operator delete(void* p);

  // KEY BIT
  friend class AllocatorInterface;
};

class TensorReference : public HandleReference {
  public:
    TensorInterface* operator*();
};

// Same as Named Tensor but not registered in the context class
struct SimpleNamedTensor {
 public:
  const uTensor::string& name;  // Fixed
  Tensor& tensor;               // Modifiable

  //SimpleNamedTensor();
  SimpleNamedTensor(const uTensor::string& name, Tensor& tensor);
};
}  // namespace uTensor
#endif
