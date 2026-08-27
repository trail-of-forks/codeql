
// --- stub library headers ---

// BDE's `bsl` standard-library layer is a top-level namespace (matched as `bsl` by the
// existing bsl.*/StdString models), while package groups sit under `BloombergLP`.
namespace bsl {
	typedef unsigned long size_t;
	template <class T> class allocator {};
	template<class charT> struct char_traits {};

	template<class charT, class traits = char_traits<charT>, class Allocator = allocator<charT> >
	class basic_string {
	public:
		basic_string();
		const charT* data() const;
	};
	typedef basic_string<char> string;

	class string_view {
	public:
		string_view(const char *);
	};

	template <class T, class Allocator = allocator<T> >
	class vector {
	public:
		vector();
		const T& operator[](size_t) const;
		const T* data() const;
	};
}

namespace BloombergLP {
namespace bdlbb {
	class Blob {};
}

namespace bmqa {
	class Message {
	public:
		int getData(bdlbb::Blob *blob) const;
	};

	class MessageProperties {
	public:
		bool getPropertyAsBool(bsl::string_view name) const;
		char getPropertyAsChar(bsl::string_view name) const;
		short getPropertyAsShort(bsl::string_view name) const;
		int getPropertyAsInt32(bsl::string_view name) const;
		long long getPropertyAsInt64(bsl::string_view name) const;
		const bsl::string &getPropertyAsString(bsl::string_view name) const;
		const bsl::vector<char> &getPropertyAsBinary(bsl::string_view name) const;
	};
}
}

// --- test code ---

void sink(int);
void sink(char);

// A property value read from a consumed message is remote input.
void test_getPropertyAsInt32(BloombergLP::bmqa::MessageProperties &props) {
	int x = props.getPropertyAsInt32("size");
	sink(x); // $ ir
}

void test_getPropertyAsString(BloombergLP::bmqa::MessageProperties &props) {
	const bsl::string &s = props.getPropertyAsString("name");
	sink(*s.data()); // $ ir
}

void test_getPropertyAsBinary(BloombergLP::bmqa::MessageProperties &props) {
	const bsl::vector<char> &b = props.getPropertyAsBinary("blob");
	sink(b[0]); // $ ir
}

// Coverage: exercise every modeled source so sources.ql lists each row. `getData` fills a
// bdlbb::Blob whose segmented buffers are not yet modeled, so its payload is not flow-tested
// here (bdlbb::Blob modeling is a follow-up).
void coverage(BloombergLP::bmqa::Message &msg, BloombergLP::bmqa::MessageProperties &props,
              BloombergLP::bdlbb::Blob *blob) {
	msg.getData(blob);
	props.getPropertyAsBool("k");
	props.getPropertyAsChar("k");
	props.getPropertyAsShort("k");
	props.getPropertyAsInt32("k");
	props.getPropertyAsInt64("k");
	props.getPropertyAsString("k");
	props.getPropertyAsBinary("k");
}
