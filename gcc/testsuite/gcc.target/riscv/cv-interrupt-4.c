/* Verify t0 is not saved before use.  */
/* { dg-do compile } */
/* { dg-options "-fomit-frame-pointer" } */
/* { dg-skip-if "" { *-*-* } { "*" } { "-O0" } } */
void __attribute__ ((interrupt ("corev-fast")))
foo2 (void)
{
  char array[4096];
  extern volatile int INTERRUPT_FLAG;
  INTERRUPT_FLAG = 0;

  extern volatile int COUNTER;
#ifdef __riscv_atomic
  __atomic_fetch_add (&COUNTER, 1, __ATOMIC_RELAXED);
#else
  COUNTER++;
#endif
}
/* { dg-final { scan-assembler-not "s\[wd\]\t t0" } } */
