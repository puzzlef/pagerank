#pragma once
#include <type_traits>
#include <iterator>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

using std::is_floating_point;
using std::forward_iterator_tag;
using std::random_access_iterator_tag;
using std::vector;
using std::ceil;
using std::max;
using std::find;
using std::count;
using std::count_if;
using std::chrono::microseconds;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;




// NONE
// ----
// Zero size type.

#ifndef NONE
struct None {
  friend bool operator==(None a, None b) noexcept { return true; }

  template <class T>
  friend bool operator==(None a, const T& b) noexcept { return false; }

  template <class T>
  friend bool operator==(const T& a, None b) noexcept { return false; }
};
#define NONE None
#endif




// ITERATOR-*
// ----------
// Helps create iterators.

#ifndef ITERATOR_USING
#define ITERATOR_USING(cat, dif, val, ref, ptr) \
  using iterator_category = cat; \
  using difference_type   = dif; \
  using value_type = val; \
  using reference  = ref; \
  using pointer    = ptr;

#define ITERATOR_USING_I(I) \
  using iterator_category = typename I::iterator_category; \
  using difference_type   = typename I::difference_type; \
  using value_type = typename I::value_type; \
  using reference  = typename I::reference; \
  using pointer    = typename I::pointer;

#define ITERATOR_USING_IVR(I, val, ref) \
  using iterator_category = typename I::iterator_category; \
  using difference_type   = typename I::difference_type; \
  using value_type = val; \
  using reference  = ref; \
  using pointer    = value_type*;
#endif


#ifndef ITERATOR_DEREF
#define ITERATOR_DEREF(I, se, be, ae) \
  reference operator*() { return se; } \
  reference operator[](difference_type i) { return be; } \
  pointer operator->() { return ae; }
#endif


#ifndef ITERATOR_NEXT
#define ITERATOR_NEXTP(I, ie)  \
  I& operator++() { ie; return *this; }  \
  I operator++(int) { I a = *this; ++(*this); return a; }

#define ITERATOR_NEXTN(I, de) \
  I& operator--() { de; return *this; }  \
  I operator--(int) { I a = *this; --(*this); return a; }

#define ITERATOR_NEXT(I, ie, de) \
  ITERATOR_NEXTP(I, ie) \
  ITERATOR_NEXTN(I, de)
#endif


#ifndef ITERATOR_ADVANCE
#define ITERATOR_ADVANCEP(I, i, fe) \
  I& operator+=(difference_type i) { fe; return *this; }

#define ITERATOR_ADVANCEN(I, i, be) \
  I& operator-=(difference_type i) { be; return *this; }

#define ITERATOR_ADVANCE(I, i, fe, be) \
  ITERATOR_ADVANCEP(I, i, fe) \
  ITERATOR_ADVANCEN(I, i, be)
#endif


#ifndef ITERATOR_ARITHMETICP
#define ITERATOR_ARITHMETICP(I, a, b, ...)  \
  friend I operator+(const I& a, difference_type b) { return I(__VA_ARGS__); } \
  friend I operator+(difference_type b, const I& a) { return I(__VA_ARGS__); }
#endif


#ifndef ITERATOR_ARITHMETICN
#define ITERATOR_ARITHMETICN(I, a, b, ...) \
  friend I operator-(const I& a, difference_type b) { return I(__VA_ARGS__); } \
  friend I operator-(difference_type b, const I& a) { return I(__VA_ARGS__); }
#endif


#ifndef ITERATOR_COMPARISION
#define ITERATOR_COMPARISION(I, a, b, ae, be)  \
  friend bool operator==(const I& a, const I& b) { return ae == be; } \
  friend bool operator!=(const I& a, const I& b) { return ae != be; } \
  friend bool operator>=(const I& a, const I& b) { return ae >= be; } \
  friend bool operator<=(const I& a, const I& b) { return ae <= be; } \
  friend bool operator>(const I& a, const I& b) { return ae > be; } \
  friend bool operator<(const I& a, const I& b) { return ae < be; }
#endif


#ifndef ITERABLE_SIZE
#define ITERABLE_SIZE(se) \
  size_t size() { return se; } \
  bool empty() { return size() == 0; }
#endif




// CEIL-DIV
// --------

template <class T>
T ceilDiv(T x, T y) {
  if (is_floating_point<T>()) return ceil(x/y);
  else return (x + y-1) / y;
}




// FIND
// ----

template <class J, class T>
auto find(const J& x, const T& v) {
  return find(x.begin(), x.end(), v);
}

template <class J, class T>
int findIndex(const J& x, const T& v) {
  auto i = find(x.begin(), x.end(), v);
  return i==x.end()? -1 : i-x.begin();
}




// COUNT-*
// -------

template <class J, class T>
int count(const J& x, const T& v) {
  return count(x.begin(), x.end(), v);
}


template <class I, class F>
int countIf(I ib, I ie, F fn) {
  return count_if(ib, ie, fn);
}

template <class J, class F>
int countIf(const J& x, F fn) {
  return count_if(x.begin(), x.end(), fn);
}




// ERASE
// -----

template <class T>
void eraseIndex(vector<T>& x, int i) {
  x.erase(x.begin()+i);
}

template <class T>
void eraseIndex(vector<T>& x, int i, int I) {
  x.erase(x.begin()+i, x.begin()+I);
}




// ITERABLE
// --------

template <class I>
class Iterable {
  const I ib, ie;

  public:
  Iterable(I ib, I ie) : ib(ib), ie(ie) {}
  auto begin() const { return ib; }
  auto end() const   { return ie; }
};


template <class I>
auto iterable(I ib, I ie) {
  return Iterable<I>(ib, ie);
}

template <class J>
auto iterable(const J& x) {
  using I = decltype(x.begin());
  return Iterable<I>(x.begin(), x.end());
}




// TRANSFORM
// ---------

template <class I, class F>
class TransformIterator {
  I it;
  const F fn;

  public:
  ITERATOR_USING_IVR(I, decltype(fn(*it)), value_type)
  TransformIterator(I it, F fn) : it(it), fn(fn) {}
  ITERATOR_DEREF(TransformIterator, fn(*it), fn(it[i]), NULL)
  ITERATOR_NEXT(TransformIterator, ++it, --it)
  ITERATOR_ADVANCE(TransformIterator, i, it += i, it -= i)
  ITERATOR_ARITHMETICP(TransformIterator, a, b, a.it+b)
  ITERATOR_ARITHMETICN(TransformIterator, a, b, a.it-b)
  ITERATOR_COMPARISION(TransformIterator, a, b, a.it, b.it)
};


template <class I, class F>
auto transform(I ib, I ie, F fn) {
  auto b = TransformIterator<I, F>(ib, fn);
  auto e = TransformIterator<I, F>(ie, fn);
  return iterable(b, e);
}

template <class J, class F>
auto transform(const J& x, F fn) {
  auto b = x.begin();
  auto e = x.end();
  return transform(b, e, fn);
}




// FILTER
// ------

template <class I, class F>
class FilterIterator {
  I it;
  const I ie;
  const F fn;

  public:
  ITERATOR_USING_I(I);
  FilterIterator(I ix, I ie, F fn) : it(ix), ie(ie), fn(fn) { while (it!=ie && !fn(*it)) ++it; }
  ITERATOR_DEREF(FilterIterator, *it, it[i], NULL)
  ITERATOR_NEXTP(FilterIterator, do { ++it; } while (it!=ie && !fn(*it)))
  ITERATOR_ADVANCEP(FilterIterator, i, for (; i>0; i--) ++it)
  ITERATOR_ARITHMETICP(FilterIterator, a, b, a.it+b)
  ITERATOR_COMPARISION(FilterIterator, a, b, a.it, b.it)
};


template <class I, class F>
auto filter(I ib, I ie, F fn) {
  auto b = FilterIterator<I, F>(ib, ie, fn);
  auto e = FilterIterator<I, F>(ie, ie, fn);
  return iterable(b, e);
}

template <class J, class F>
auto filter(const J& x, F fn) {
  return filter(x.begin(), x.end(), fn);
}




// RANGE
// -----

template <class T>
int rangeSize(T v, T V, T DV=1) {
  return max(0, (int) ceilDiv(V-v, DV));
}

template <class T>
int rangeLast(T v, T V, T DV=1) {
  return v + DV*(rangeSize(v, V, DV) - 1);
}


template <class T>
class RangeIterator {
  T n;

  public:
  ITERATOR_USING(random_access_iterator_tag, T, T, T, T*)
  RangeIterator(T n) : n(n) {}
  ITERATOR_DEREF(RangeIterator, n, n+i, this)
  ITERATOR_NEXT(RangeIterator, ++n, --n)
  ITERATOR_ADVANCE(RangeIterator, i, n += i, n -= i)
  ITERATOR_ARITHMETICP(RangeIterator, a, b, a.n+b)
  ITERATOR_ARITHMETICN(RangeIterator, a, b, a.n-b)
  ITERATOR_COMPARISION(RangeIterator, a, b, a.n, b.n)
};


template <class T>
auto range(T V) {
  auto b = RangeIterator<T>(0);
  auto e = RangeIterator<T>(V);
  return iterable(b, e);
}

template <class T>
auto range(T v, T V, T DV=1) {
  auto x = range(rangeSize(v, V, DV));
  return transform(x, [=](int n) { return v+DV*n; });
}




// MEASURE
// -------

template <class F>
float measureDuration(F fn, int N=1) {
  auto start = high_resolution_clock::now();
  for (int i=0; i<N; i++)
    fn();
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  return duration.count()/(N*1000.0f);
}
