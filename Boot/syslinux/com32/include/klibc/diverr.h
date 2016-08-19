static inline void __divide_error(void)
{
    asm volatile ("int $0");	/* Divide by zero */
}
