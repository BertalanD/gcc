// { dg-do run { target c++11 } }
// { dg-options "-fassume-unique-vtables -fdump-tree-gimple" }
// { dg-final { scan-assembler-times "__dynamic_cast" 2 "gimple" } }

struct A {
  virtual void f () {}
};

struct B : A { };

bool test_ptr (A *a) {
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

int main() {
  B b;

  if (!test_ptr (&b))
    __builtin_abort ();

  if (!test_ref (b))
    __builtin_abort ();
}
