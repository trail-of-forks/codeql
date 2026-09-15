#include "wrappers.h"
using namespace BloombergLP::bdlb;
int source(); void sink(int);
void nullableCopyResult() {
  NullableValue<int> src, dst; src.makeValue(source());
  sink((dst = static_cast<const NullableValue<int>&>(src)).value()); // $ ir
  sink(dst.value()); // $ ir
}
void nullableMoveResult() {
  NullableValue<int> src, dst; src.makeValue(source());
  sink((dst = static_cast<NullableValue<int>&&>(src)).value()); // $ ir
  sink(dst.value()); // $ ir
}
void variantCopyResult() {
  VariantImp<Types<int>> src, dst; src.assign(source());
  sink((dst = static_cast<const VariantImp<Types<int>>&>(src)).the<int>()); // $ ir
  sink(dst.the<int>()); // $ ir
}
void variantMoveResult() {
  VariantImp<Types<int>> src, dst; src.assign(source());
  sink((dst = static_cast<VariantImp<Types<int>>&&>(src)).the<int>()); // $ ir
  sink(dst.the<int>()); // $ ir
}
void makeReference() {
  NullableValue<int> n;
  n.makeValue(0) = source();
  sink(n.value()); // $ ir
}
void nullableEmplaceReference() {
  NullableValue<int> n;
  n.makeValueInplace(0) = source();
  sink(n.value()); // $ ir
}
void variantEmplaceReference() {
  VariantImp<Types<int>> v;
  v.createInPlace<int>(0) = source();
  sink(v.the<int>()); // $ ir
}
