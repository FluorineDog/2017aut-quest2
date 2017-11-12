#ifndef LAB_AFX_HPP_
#define LAB_AFX_HPP_

#include <cstddef>
#include <nmmintrin.h>
// typedef struct lab__pair_st Pair;
namespace Lab {

////////////////////////////////////////////////
///////// SECTION TO IGNORE BEGINS /////////////
////////////////////////////////////////////////
constexpr unsigned INIT_HASH_VALUE = 0x01234567;
unsigned int naive_hash(const void *data, int size) {
  // work only for Plain Old Data (POD)
  // stupid but efficient for random data
  // unsafe for attack, but security is NOT required
  auto crc = INIT_HASH_VALUE;
  unsigned char *data_ = (unsigned char *)data;
  for (int i = 0; i < size; ++i) {
    crc = _mm_crc32_u8(crc, data_[i]);
  }
  return crc;
}

template <typename T> unsigned int hash_f(const T &s) {
  // optimised for base type
  // faster than pure naive_hash
  return naive_hash(&s, sizeof(s));
}

// the following is for speedups
template <> unsigned int hash_f(const unsigned long long &s) {
  return _mm_crc32_u64(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const long long &s) {
  return _mm_crc32_u64(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const double &s) {
  union {
    double f;
    unsigned long long i;
  } u;
  u.f = s;
  return _mm_crc32_u64(INIT_HASH_VALUE, u.i);
}

template <> unsigned int hash_f(const float &s) {
  union {
    float f;
    unsigned int i;
  } u;
  u.f = s;
  return _mm_crc32_u32(INIT_HASH_VALUE, u.i);
}

template <> unsigned int hash_f(const unsigned &s) {
  return _mm_crc32_u32(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const int &s) {
  return _mm_crc32_u32(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const unsigned short &s) {
  return _mm_crc32_u16(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const short &s) {
  return _mm_crc32_u16(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const signed char &s) {
  return _mm_crc32_u8(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const unsigned char &s) {
  return _mm_crc32_u8(INIT_HASH_VALUE, s);
}

template <> unsigned int hash_f(const char &s) {
  return _mm_crc32_u8(INIT_HASH_VALUE, s);
}
////////////////////////////////////////////////
////////// SECTION TO IGNORE ENDS //////////////
////////////////////////////////////////////////

// work only for Plain Old Data (POD)
// otherwise correctness is not guaranteed
// stupid but efficient for random data
// unsafe for attack, since security is NOT required
unsigned int naive_hash(const void *data, int size);

// Lab::hash<T> simulates std::hash<T>
// usage: hash_result = hash<T>()(item_to_hash);
template <typename T> class hash {
public:
  unsigned int operator()(const T &s) { return hash_f(s); }
};

template <typename T1, typename T2> struct pair {
  T1 first;
  T2 second;
};

// USE Lab::make_pair LIKE std::make_pair
template <typename T1, typename T2>
pair<T1, T1> make_pair(const T1 &first, const T2 &second) {
  return pair<T1, T2>{first, second};
};

// usage:
// auto comp = less<T>();
// comp(a, b) == a < b;
// OR
// less<T>()(a, b) == a < b;
template <typename T> class less {
public:
  bool operator()(const T &a, const T &b) { return a < b; }
};
}
#endif