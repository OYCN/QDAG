#ifndef MACRO_H
#define MACRO_H

#define CLASS_VAL_NAME(name) m##name
#define CLASS_VAL_GET(name) get##name();
#define CLASS_VAL_SET(name, value) set##name(value);

#define DEF_VAL_GET(type, name) \
    type get##name() const { return CLASS_VAL_NAME(name); }

#define DEF_VAL_GET_REF(type, name) \
    type& get##name() { return CLASS_VAL_NAME(name); }

#define DEF_VAL_GET_REF_CONST(type, name) \
    const type& get##name() const { return CLASS_VAL_NAME(name); }

#define DEF_VAL_SET(type, name) \
    void set##name(type v) { CLASS_VAL_NAME(name) = v; }

#define DEF_VAL_SET_REF(type, name) \
    void set##name(const type& v) { CLASS_VAL_NAME(name) = v; }

#define DEF_VAL_VAL(type, name) type CLASS_VAL_NAME(name);

#define DEF_VAL_ALL(type, name) \
 public:                        \
    DEF_VAL_GET(type, name)     \
    DEF_VAL_SET(type, name)     \
 private:                       \
    DEF_VAL_VAL(type, name)

#define DEF_VAL_ALL_REF(type, name) \
 public:                            \
    DEF_VAL_GET_REF(type, name)     \
    DEF_VAL_SET_REF(type, name)     \
 private:                           \
    DEF_VAL_VAL(type, name)

#define DEF_VAL_ALL_REF_CONST(type, name) \
 public:                                  \
    DEF_VAL_GET_REF_CONST(type, name)     \
    DEF_VAL_SET_REF(type, name)           \
 private:                                 \
    DEF_VAL_VAL(type, name)

#endif  // MACRO_H