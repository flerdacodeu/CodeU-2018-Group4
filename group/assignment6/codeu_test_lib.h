#ifndef TESTLIB_H
#define TESTLIB_H

#include <iostream>
#include <vector>

// Some convenient macros for simple testing.
// If expectation is fulfilled, prints nothing;
// If expectation is not fulfilled, prints what went wrong (expectation vs.
// actual value) with the filename and line number for convenience.

#define EXPECT_TRUE(statement)                                            \
  if (!(statement)) {                                                     \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" #statement << ") is false, expected true." \
              << std::endl;                                               \
  }

#define EXPECT_FALSE(statement)                                           \
  if (statement) {                                                        \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" #statement << ") is true, expected false." \
              << std::endl;                                               \
  }

#define EXPECT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "               \
              << "Statement (" << #actual << ") is " << actual            \
              << ", expected " << (expected) << " (" << #expected << ")." \
              << std::endl;                                               \
  }

#define EXPECT_NULL(statement)                                 \
  if (statement != nullptr) {                                  \
    std::cout << __FILE__ << ":" << __LINE__ << " Failed: "    \
              << "Statement (" << #statement                   \
              << ") is not null, expected null." << std::endl; \
  }

// Print operator for vectors..
template <class T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "{";
	for (int i = 0; i < v.size(); i++) {
		if (i > 0) {
			os << ", ";
		}
		os << v[i];
	}
	os << "}";
	
	return os;
}

#endif
