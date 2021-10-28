#include <stddef.h>
#include <stdio.h>

struct Base {
    void *context;
    void (*doSomething)(void *context);
};

struct Impl {
    struct Base base;
    unsigned call_count;
};

static void impl_doSomething(struct Impl *impl)
{
  impl->call_count++;
}

static void base_to_impl_doSomething(void *context) {
  impl_doSomething((struct Impl*)context);
}

static struct Base implGetBase(struct Impl *impl)
{
  struct Base base;
  base.context = impl;
  base.doSomething = base_to_impl_doSomething;
  return base;
}

static struct Impl createImpl()
{
  struct Impl impl;
  impl.call_count = 0;
  return impl;
}


int testme()
{
  struct Impl impl = createImpl();

  struct Base base = implGetBase(&impl);
  for (int i = 0; i < 10; i++) {
    printf("impl.call_count = %u\n", impl.call_count);
    base.doSomething(&base);
  }
  return 0;
}
