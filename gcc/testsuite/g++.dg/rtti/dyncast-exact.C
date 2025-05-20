// { dg-do run { target c++11 } }
// { dg-options "-fassume-unique-vtables -fdump-tree-original" }
// { dg-final { scan-tree-dump-not "__dynamic_cast" "original" } }

struct A {
  virtual void f () {}
};

struct B final : A { };

bool test_single (A *a) {
  return dynamic_cast<B *>(a) != nullptr;
}

bool test_ref (A &a) {
  try {
    B &b = dynamic_cast<B &>(a);
    return true;
  } catch (...) {
    return false;
  }
}

struct C {
  virtual void g () {}
};

struct D final : A, C { };

bool test_multi (C *c) {
  return dynamic_cast<D *>(c) != nullptr;
}

struct E : A { };

struct F final : E { };

bool test_chain (E *e) {
  return dynamic_cast<F *>(e) != nullptr;
}

int main() {
  A a;
  B b;

  if (test_single (&a))
    __builtin_abort ();

  if (test_ref (a))
    __builtin_abort ();

  if (!test_single (&b))
    __builtin_abort ();

  if (!test_ref (b))
    __builtin_abort ();

  C c;
  D d;

  if (test_multi (&c))
    __builtin_abort ();

  if (!test_multi (&d))
    __builtin_abort ();

  E e;
  F f;

  if (test_chain (&e))
    __builtin_abort ();

  if (!test_chain (&f))
    __builtin_abort ();
}
