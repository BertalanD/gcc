/* Useful if you wish to make target-specific GCC changes. */
#undef TARGET_SERENITY
#define TARGET_SERENITY 1

#if defined(HAVE_LD_EH_FRAME_HDR)
#define LINK_EH_SPEC "%{!static|static-pie:--eh-frame-hdr} "
#endif

/* Default arguments you want when running your
   x86_64-serenity-gcc toolchain */
#undef LIB_SPEC
#define LIB_SPEC "-lc" /* link against C standard library */

/* Files that are linked before user code.
   The %s tells GCC to look for these files in the library directory. */
#undef STARTFILE_SPEC
#define STARTFILE_SPEC "%{!shared:crt0.o%s} crti.o%s %{shared: %{!fbuilding-libgcc:crt0_shared.o%s}} %{shared|static-pie|!no-pie:crtbeginS.o%s; :crtbegin.o%s}"

/* Files that are linked after user code. */
#undef ENDFILE_SPEC
#define ENDFILE_SPEC "%{shared|static-pie|!no-pie:crtendS.o%s; :crtend.o%s} crtn.o%s"

#undef LINK_SPEC
#define LINK_SPEC "%{shared:-shared} %{static:-static} %{!static: %{rdynamic:-export-dynamic} -dynamic-linker /usr/lib/Loader.so}"

#undef CC1_SPEC
#define CC1_SPEC "-fno-semantic-interposition"

#undef CPP_SPEC
#define CPP_SPEC "%{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"

/* Use --as-needed -lgcc_s for eh support. */
#define USE_LD_AS_NEEDED 1

/* We don't have a separate math library, it's included within libc. While we do have compatibility
   linker scripts in place, just don't add it to the linker invocation to begin with. */
#define MATH_LIBRARY ""

/* Additional predefined macros. */
#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()      \
  do {                                \
    builtin_define ("__serenity__");      \
    builtin_define ("__unix__");      \
    builtin_assert ("system=serenity");   \
    builtin_assert ("system=unix");   \
    builtin_assert ("system=posix");   \
  } while(0);
