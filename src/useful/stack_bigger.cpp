static void main2()
{
  // Code here
}

static void run_with_stack_size(void (*func)(), size_t stsize)
{
    char *stack, *send;
    stack=(char *)malloc(stsize);
    send=stack+stsize-16;
    send=(char *)((uintptr_t)send/16*16);
    asm volatile(
      "mov %%rsp, (%0)\n"
      "mov %0, %%rsp\n"
      :
      : "r" (send));
    func();
    asm volatile(
      "mov (%0), %%rsp\n"
      :
      : "r" (send));
    free(stack);
}

int main()
{
    run_with_stack_size(main2, 64*1024*1024);
}
