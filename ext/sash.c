#include <ruby.h>
#include <ruby/encoding.h>

#define TO_S(v)    rb_funcall(v, rb_intern("to_s"), 0)
#define CSTRING(v) RSTRING_PTR(TO_S(v))

#undef SIZET2NUM
#undef NUM2SIZET

#ifdef HAVE_LONG_LONG
  #define SIZET2NUM(x) ULL2NUM(x)
  #define NUM2SIZET(x) NUM2ULL(x)
#else
  #define SIZET2NUM(x) ULONG2NUM(x)
  #define NUM2SIZET(x) NUM2ULONG(x)
#endif

static char *digestlookup = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-";

/* djb2 string hash function */
uint64_t djhash(void *string) {
    uint64_t result = 5381;
    unsigned char *p;

    p = (unsigned char *)string;

    while (*p) {
        result = ((result << 5) ^ result ) ^ (*p);
        ++p;
    }

    return result;
}

/* sdbm hash function */
uint64_t sdbm(void *string) {
    uint64_t result = 0;
    unsigned char *p;

    p = (unsigned char *)string;

    while (*p) {
        result = *p + (result << 6) + (result << 16) - result;
        ++p;
    }

    return result;
}

#define STRING_HASH sdbm

VALUE rb_digest(VALUE self, VALUE string) {
    return SIZET2NUM(STRING_HASH(CSTRING(string)));
}

VALUE rb_base64(VALUE self, VALUE string) {
    uint64_t idx, n, digest = STRING_HASH(CSTRING(string));
    char buffer[12];

    idx = 0;
    while (digest > 0) {
        n = digest >> 6;
        buffer[idx++] = digestlookup[digest - (n << 6)];
        digest = n;
    }

    return rb_str_new(buffer, idx);
}


void Init_sash() {
    VALUE mSash = rb_define_module("Sash");
    rb_define_singleton_method(mSash, "digest", RUBY_METHOD_FUNC(rb_digest), 1);
    rb_define_singleton_method(mSash, "base64", RUBY_METHOD_FUNC(rb_base64), 1);
}
