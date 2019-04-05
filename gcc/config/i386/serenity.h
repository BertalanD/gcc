/* Ensure that we are using the SIZE_TYPE indicated by SysV */
#undef SIZE_TYPE
#define SIZE_TYPE    (TARGET_64BIT ? "long unsigned int" : "unsigned int")

/* Ensure that ptrdiff_t matches the actual pointer size */
#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE    (TARGET_64BIT ? "long int" : "int")
