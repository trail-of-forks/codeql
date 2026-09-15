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

// Scalar destinations can still require a user-defined input conversion.
struct ConvertedNumber {
  int payload;
  operator int() const { return payload; }
};
struct IgnoredNumber {
  int payload;
  operator int() const { return 0; }
};
void nullableScalarConversion() {
  ConvertedNumber input = {source()};
  sink(static_cast<int>(input)); // $ ir
  BloombergLP::bdlb::NullableValue<int> n;
  n.makeValueInplace(input);
  sink(n.value()); // $ ir
}
void variantScalarConversion() {
  ConvertedNumber input = {source()};
  sink(static_cast<int>(input)); // $ ir
  BloombergLP::bdlb::Variant<int> v;
  v.createInPlace<int>(input);
  sink(v.the<int>()); // $ ir
}
void ignoredScalarConversions() {
  IgnoredNumber input = {source()};
  BloombergLP::bdlb::NullableValue<int> n;
  n.makeValueInplace(input);
  sink(n.value());
  BloombergLP::bdlb::Variant<int> v;
  v.createInPlace<int>(input);
  sink(v.the<int>());
}
