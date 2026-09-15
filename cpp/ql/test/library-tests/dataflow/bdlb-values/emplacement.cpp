#include "wrappers.h"
int source();
void sink(int);

// Reduced forwarding bodies. User-defined construction must remain visible.
namespace BloombergLP { namespace bdlb {
template<class TYPE>
template<class... ARGS>
TYPE& NullableValue<TYPE>::makeValueInplace(ARGS&&... args) {
  TYPE made(static_cast<ARGS&&>(args)...);
  return makeValue(made);
}
template<class TYPES>
template<class TYPE, class... ARGS>
TYPE& VariantImp<TYPES>::createInPlace(ARGS&&... args) {
  TYPE made(static_cast<ARGS&&>(args)...);
  assign(made);
  return the<TYPE>();
}
} }

struct Constructed {
  int value;
  Constructed(int ignored, int used) : value(used) {}
};

void multiArgumentNullable() {
  BloombergLP::bdlb::NullableValue<Constructed> n;
  n.makeValueInplace(0, source());
  sink(n.value().value); // $ ir
}
void ignoredArgumentNullable() {
  BloombergLP::bdlb::NullableValue<Constructed> n;
  n.makeValueInplace(source(), 0);
  sink(n.value().value);
}
void multiArgumentVariant() {
  BloombergLP::bdlb::Variant<Constructed> v;
  v.createInPlace<Constructed>(0, source());
  sink(v.the<Constructed>().value); // $ ir
}
void ignoredArgumentVariant() {
  BloombergLP::bdlb::Variant<Constructed> v;
  v.createInPlace<Constructed>(source(), 0);
  sink(v.the<Constructed>().value);
}
