#include <stddef.h>
#include <stdio.h>

struct Base {
    void (*doSomething)(struct Base *base);
};

struct Impl {
    struct Base base;
    unsigned call_count;
};

static void impl_doSomething(struct Base *base)
{
  struct Impl *impl = (struct Impl*)(((size_t)base) + offsetof(struct Impl, base));
  impl->call_count++;
}
  
static struct Impl createImpl()
{
  struct Impl impl;
  impl.base.doSomething = impl_doSomething;
  impl.call_count = 0;
  return impl;
}


int testme()
{
  struct Impl impl = createImpl();

  struct Base *base = &impl.base;
  for (int i = 0; i < 10; i++) {
    printf("impl.call_count = %u\n", impl.call_count);
    base->doSomething(base);
  }
  return 0;
}
