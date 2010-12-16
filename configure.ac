AC_PREREQ( 2.59 )

AC_INIT(
 [libbfio],
 [20101216],
 [jbmetz@users.sourceforge.net])

AC_CONFIG_SRCDIR(
 [include/libbfio.h.in])

AM_INIT_AUTOMAKE([gnu 1.6])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for configure arguments
LIBBFIO_TEST_ENABLE(
 [wide-character-type],
 [wide_character_type],
 [enable wide character type support],
 [no])
LIBBFIO_TEST_ENABLE(
 [winapi],
 [winapi],
 [enable WINAPI support for cross-compilation],
 [auto-detect])

dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])

dnl Check for compiler language support
AC_C_CONST
AC_C_VOLATILE

dnl Automatically enable winapi support for mingw
AS_IF(
 [test "x$ac_cv_libbfio_enable_winapi" = xauto-detect],
 [ac_libbfio_target_string="$target";

 AS_IF(
  [test "x$ac_libbfio_target_string" = x],
  [ac_libbfio_target_string="$build"])

 AS_CASE(
  [$ac_libbfio_target_string],
  [*mingw*],[AC_MSG_NOTICE(
             [Detected MinGW enabling WINAPI support for cross-compilation])
            ac_cv_libbfio_enable_winapi=yes],
  [*],[ac_cv_libbfio_enable_winapi=no])
 ])

dnl Check for headers
dnl Headers included in libbfio/types.h
AC_CHECK_HEADERS([sys/types.h inttypes.h stdint.h])

AS_IF(
 [test "x$ac_cv_header_sys_types_h" = xyes],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_SYS_TYPES_H],
  [0])])

AS_IF(
 [test "x$ac_cv_header_inttypes_h" = xyes],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [1])],
 [AC_SUBST(
  [HAVE_INTTYPES_H],
  [0])])

AS_IF(
 [test "x$ac_cv_header_stdint_h" = xyes],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [1])],
 [AC_SUBST(
  [HAVE_STDINT_H],
  [0])])

dnl Headers included in common/common.h
AS_IF(
 [test "x$ac_cv_libbfio_enable_winapi" = xyes],
 [AC_CHECK_HEADERS([windows.h])

 AS_IF(
  [test "x$ac_cv_header_windows_h" = xno],
  [AC_MSG_FAILURE(
   [Missing header: windows.h header is required to compile with winapi support],
   [1]) ])
 ])

dnl Headers included in common/types.h
AC_CHECK_HEADERS([limits.h])

dnl Headers included in common/memory.h and libcstring/libcstring_narrow_string.h
AC_CHECK_HEADERS([stdlib.h string.h])

dnl Headers included in libcstring/libcstring_locale.c
AC_CHECK_HEADERS([langinfo.h locale.h])

dnl Headers included in liberror/liberror_error.c and libnotify/libnotify_print.c
AC_CHECK_HEADERS([stdarg.h])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes],
 [AC_CHECK_HEADERS([varargs.h]) ])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
 [AC_MSG_FAILURE(
  [Missing headers: stdarg.h and varargs.h],
  [1]) ])

dnl Headers included in libnotify/libnotify_stream.c and libbfio/libbfio_file.c
AC_CHECK_HEADERS([errno.h])

dnl Headers included in libbfio/libbfio_file.c
AC_CHECK_HEADERS([fcntl.h sys/stat.h unistd.h])

dnl Check for declarations and type definitions
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

AC_CHECK_TYPE(
 [size32_t],
 [AC_SUBST(
  [HAVE_SIZE32_T],
  [1])],
 [AC_SUBST(
  [HAVE_SIZE32_T],
  [0])])

AC_CHECK_TYPE(
 [ssize32_t],
 [AC_SUBST(
  [HAVE_SSIZE32_T],
  [1])],
 [AC_SUBST(
  [HAVE_SSIZE32_T],
  [0])])

AC_CHECK_TYPE(
 [size64_t],
 [AC_SUBST(
  [HAVE_SIZE64_T],
  [1])],
 [AC_SUBST(
  [HAVE_SIZE64_T],
  [0])])

AC_CHECK_TYPE(
 [ssize64_t],
 [AC_SUBST(
  [HAVE_SSIZE64_T],
  [1])],
 [AC_SUBST(
  [HAVE_SSIZE64_T],
  [0])])

AC_CHECK_TYPE(
 [off64_t],
 [AC_SUBST(
  [HAVE_OFF64_T],
  [1])],
 [AC_SUBST(
  [HAVE_OFF64_T],
  [0])])

AC_CHECK_TYPE([ssize_t])

AC_CHECK_SIZEOF([off_t])
AC_CHECK_SIZEOF([size_t])

dnl Check for functions
dnl File stream functions used in common/file_stream.h
AC_CHECK_FUNCS(
 [fclose],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fclose],
  [1]) ])

AC_CHECK_FUNCS(
 [feof],
 [],
 [AC_MSG_FAILURE(
  [Missing function: feof],
  [1]) ])

AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [fopen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fopen],
  [1]) ])

AC_CHECK_FUNCS(
 [fread],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fread],
  [1]) ])

AC_CHECK_FUNCS(
 [fseeko],
 [],
 [AC_CHECK_FUNCS(
  [fseeko64],
  [],
  [AC_MSG_FAILURE(
   [Missing function: fseeko and fseeko64],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [fwrite],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fwrite],
  [1]) ])

AC_CHECK_FUNCS(
 [vfprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vfprintf],
  [1]) ])

dnl Memory functions used in common/memory.h
AC_CHECK_FUNCS(
 [free],
 [],
 [AC_MSG_FAILURE(
  [Missing function: free],
  [1]) ])

AC_CHECK_FUNCS(
 [malloc],
 [],
 [AC_MSG_FAILURE(
  [Missing function: malloc],
  [1]) ])

AC_CHECK_FUNCS(
 [memcmp],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memcmp],
  [1]) ])

AC_CHECK_FUNCS(
 [memcpy],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memcpy],
  [1]) ])

AC_CHECK_FUNCS(
 [memset],
 [],
 [AC_MSG_FAILURE(
  [Missing function: memset],
  [1]) ])

AC_CHECK_FUNCS(
 [realloc],
 [],
 [AC_MSG_FAILURE(
  [Missing function: realloc],
  [1]) ])

dnl Check for environment functions in libcstring/libcstring_locale.c
AC_CHECK_FUNCS(
 [getenv],
 [],
 [AC_MSG_FAILURE(
  [Missing function: getenv],
  [1]) ])

dnl Check for localization functions in libcstring/libcstring_locale.c
AC_CHECK_FUNCS(
 [setlocale],
 [],
 [AC_MSG_FAILURE(
  [Missing function: setlocale],
  [1]) ])

LIBBFIO_CHECK_FUNC_LANGINFO_CODESET

dnl Narrow character string functions used in libcstring/libcstring_narrow_string.h
AC_CHECK_FUNCS(
 [fgets],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fgets],
  [1]) ])

AC_CHECK_FUNCS(
 [memchr],
 [],
 [AC_CHECK_FUNCS(
  [strchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memchr and strchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memcmp],
 [],
 [AC_CHECK_FUNCS(
  [strncmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memcmp and strncmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memcpy],
 [],
 [AC_CHECK_FUNCS(
  [strncpy],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: memcpy and strncpy],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [memrchr],
 [AC_CHECK_DECLS(
  [memrchr],
  [ac_libbfio_have_memrchr=yes],
  [ac_libbfio_have_memrchr=no]) ],
 [ac_libbfio_have_memrchr=no])

AS_IF(
 [test "x$ac_libbfio_have_memrchr" = xno],
 [AC_CHECK_FUNCS(
  [strrchr],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strrchr and memrchr],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [snprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: snprintf],
  [1]) ])

AC_CHECK_FUNCS(
 [sscanf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: sscanf],
  [1]) ])

AC_CHECK_FUNCS(
 [strlen],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strlen],
  [1]) ])

AC_CHECK_FUNCS(
 [strncasecmp],
 [],
 [AC_CHECK_FUNCS(
  [strcasecmp],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strncasecmp and strcasecmp],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strstr],
 [],
 [AC_MSG_FAILURE(
  [Missing function: strstr],
  [1]) ])

AC_CHECK_FUNCS(
 [strtoll],
 [],
 [AC_CHECK_FUNCS(
  [atoll],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strtoll and atoll],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [strtoull],
 [],
 [AC_CHECK_FUNCS(
  [atoll],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strtoull and atoll],
   [1]) ]) ])

AC_CHECK_FUNCS(
 [vsnprintf],
 [],
 [AC_MSG_FAILURE(
  [Missing function: vsnprintf],
  [1]) ])

dnl File input/output functions used in libbfio/libbfio_file.h
AC_CHECK_FUNCS(
 [close],
 [],
 [AC_MSG_FAILURE(
  [Missing function: close],
  [1]) ])

AC_CHECK_FUNCS(
 [fstat],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fstat],
  [1]) ])

AC_CHECK_FUNCS(
 [lseek],
 [],
 [AC_MSG_FAILURE(
  [Missing function: lseek],
  [1]) ])

AC_CHECK_FUNCS(
 [open],
 [],
 [AC_MSG_FAILURE(
  [Missing function: open],
  [1]) ])

AC_CHECK_FUNCS(
 [read],
 [],
 [AC_MSG_FAILURE(
  [Missing function: read],
  [1]) ])

AC_CHECK_FUNCS(
 [stat],
 [],
 [AC_MSG_FAILURE(
  [Missing function: stat],
  [1]) ])

AC_CHECK_FUNCS(
 [write],
 [],
 [AC_MSG_FAILURE(
  [Missing function: write],
  [1]) ])

dnl Check for error string functions used in libbfio/libbfio_error_string.h
AC_FUNC_STRERROR_R()

AS_IF(
 [test "x$ac_cv_have_decl_strerror_r" = xno],
 [AC_CHECK_FUNCS(
  [strerror],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strerror_r and strerror],
   [1]) ]) ])

dnl Check for printf conversion specifier support
LIBBFIO_CHECK_FUNC_PRINTF_JD
LIBBFIO_CHECK_FUNC_PRINTF_ZD

dnl Checks for libraries and library functions
dnl ac_libbfio_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments

dnl Check for enabling libuna for Unicode string support
LIBBFIO_CHECK_LIBUNA

AS_IF(
 [test "x$ac_libbfio_have_libuna" = xyes],
 [dnl libuna is available
 AC_SUBST(
  [libbfio_pc_libs_private_libuna],
  [-luna])
 AC_SUBST(
  [libbfio_spec_requires_libuna],
  [libuna])
 AC_SUBST(
  [libbfio_spec_build_requires_libuna],
  [libuna-devel])
 AC_SUBST(
  [LIBUNA_CPPFLAGS],
  [])
 AC_SUBST(
  [LIBUNA_LIBADD],
  []) ],
 [dnl libuna is not available, using the (local) version that came with the source package
 AC_DEFINE(
  [HAVE_LOCAL_LIBUNA],
  [1],
  [Define to 1 if the local version of libuna is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBUNA],
  [1])
 AC_SUBST(
  [libbfio_pc_libs_private_libuna],
  [])
 AC_SUBST(
  [libbfio_spec_requires_libuna],
  [])
 AC_SUBST(
  [libbfio_spec_build_requires_libuna],
  [])
 AC_SUBST(
  [LIBUNA_CPPFLAGS],
  [-I../libuna])
 AC_SUBST(
  [LIBUNA_LIBADD],
  [../libuna/libuna.la])
 ac_libbfio_have_libuna=local])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBUNA],
 [test "x$ac_libbfio_have_libuna" = xlocal])

dnl Check if libbfio should be build with wide character type support
AS_IF(
 [test "x$ac_cv_header_windows_h" = xyes],
 [ac_cv_libbfio_enable_wide_character_type=yes])

AS_IF(
 [test "x$ac_cv_libbfio_enable_wide_character_type" != xno ],
 [dnl Check for the wide character header
 AC_CHECK_HEADERS(
  [wchar.h],
  [AC_DEFINE(
   [HAVE_WCHAR_H],
   [1],
   [Define to 1 if you have the <wchar.h> header file.])
  AC_SUBST(
   [HAVE_WCHAR_H],
   [1]) ],
  [AC_MSG_FAILURE(
   [Missing header: wchar.h],
   [1]) ])

 dnl Determine wide character byte size
 AC_CHECK_SIZEOF([wchar_t])

 dnl Check for wide character string functions

 dnl Wide character string functions used in common/file_stream.h
 AC_CHECK_FUNCS(
  [fgetws],
  [],
  [AC_MSG_FAILURE(
   [Missing function: fgetws],
   [1]) ])

 dnl Wide character string functions used in libcstring/libcstring_wide_string.h
 AC_CHECK_FUNCS(
  [swprintf],
  [],
  [AC_MSG_FAILURE(
   [Missing function: swprintf],
   [1]) ])

 AC_CHECK_FUNCS(
  [wmemchr],
  [],
  [AC_CHECK_FUNCS(
   [wcschr],
   [],
   [AC_MSG_FAILURE(
    [Missing functions: wmemchr and wcschr],
    [1]) ]) ])

 AC_CHECK_FUNCS(
  [wmemcmp],
  [],
  [AC_CHECK_FUNCS(
   [wcsncmp],
   [],
   [AC_MSG_FAILURE(
    [Missing functions: wmemcmp and wcsncmp],
    [1]) ]) ])

 AC_CHECK_FUNCS(
  [wmemcpy],
  [],
  [AC_CHECK_FUNCS(
   [wcsncpy],
   [],
   [AC_MSG_FAILURE(
    [Missing functions: wmemcpy and wcsncpy],
    [1]) ]) ])

 AC_CHECK_FUNCS(
  [wmemrchr],
  [],
  [AC_CHECK_FUNCS(
   [wcsrchr],
   [],
   [AC_MSG_FAILURE(
    [Missing functions: wmemrchr and wcsrchr],
    [1]) ]) ])

 AC_CHECK_FUNCS(
  [wcslen],
  [],
  [AC_MSG_FAILURE(
   [Missing function: wcslen],
   [1]) ])

 AC_CHECK_FUNCS(
  [wcsncasecmp],
  [],
  [AC_CHECK_FUNCS(
   [wcscasecmp],
   [],
   [AC_CHECK_FUNCS(
    [towlower],
    [],
    [AC_MSG_FAILURE(
     [Missing functions: wcsncasecmp, wcscasecmp and towlower],
     [1]) ]) ]) ])

 AC_CHECK_FUNCS(
  [wcsstr],
  [],
  [AC_MSG_FAILURE(
   [Missing function: wcsstr],
   [1]) ])

 AC_CHECK_FUNCS(
  [wcstoll],
  [],
  [AC_MSG_FAILURE(
   [Missing function: wcstoll],
   [1]) ])

 AC_CHECK_FUNCS(
  [wcstoull],
  [],
  [AC_MSG_FAILURE(
   [Missing function: wcstoull],
   [1]) ])

 dnl Wide character string functions used in liberror/liberror_error.h
 AC_CHECK_FUNCS(
  [wcstombs],
  [],
  [AC_MSG_FAILURE(
   [Missing function: wcstombs],
   [1]) ])

 dnl Make the necessary definitions
 AC_DEFINE(
  [HAVE_WIDE_CHARACTER_TYPE],
  [1],
  [Define to 1 if wide character type should be used.])
 AC_SUBST(
  [HAVE_WIDE_CHARACTER_TYPE],
  [1])
 ac_cv_libbfio_enable_wide_character_type=yes],

 [AC_SUBST(
  [HAVE_WIDE_CHARACTER_TYPE],
  [0])
 AC_SUBST(
  [HAVE_WCHAR_H],
  [0]) ])

dnl Check if libbfio should be build with verbose output
AS_IF(
 [test "x$ac_cv_libbfio_enable_verbose_output" != xno ],
 [AC_DEFINE(
 [HAVE_VERBOSE_OUTPUT],
 [1],
 [Define to 1 if verbose output should be used.])
 ac_cv_libbfio_enable_verbose_output=yes])

dnl Check if libbfio should be build with debug output
AS_IF(
 [test "x$ac_cv_libbfio_enable_debug_output" != xno ],
 [AC_DEFINE(
 [HAVE_DEBUG_OUTPUT],
 [1],
 [Define to 1 if debug output should be used.])
 ac_cv_libbfio_enable_debug_output=yes])

dnl Check if requires and build requires should be set in spec file
AS_IF(
 [test "x$ac_libbfio_have_libuna" = xyes],
 [AC_SUBST(
 [libbfio_spec_requires],
 [Requires:])
 AC_SUBST(
 [libbfio_spec_build_requires],
 [BuildRequires:]) ],
 [AC_SUBST(
 [libbfio_spec_requires],
 [])
 AC_SUBST(
 [libbfio_spec_build_requires],
 [])
 ac_libbfio_dummy=yes])

dnl Set memwatch support
ac_libbfio_have_memwatch=no

AS_IF(
 [test "x$ac_libbfio_have_memwatch" != xno ],
 [AC_SUBST(
 [MEMWATCH_CPPFLAGS],
 ["-DMEMWATCH -DMEMWATCH_STDIO"])
 AC_SUBST(
 [MEMWATCH_LIBADD],
 [../common/libmemwatch.la]) ])

AM_CONDITIONAL(
 [HAVE_MEMWATCH],
 [test "x$ac_libbfio_have_memwatch" != xno])

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcstring/Makefile])
AC_CONFIG_FILES([liberror/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libbfio/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([po/Makevars])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([macosx/Makefile])
AC_CONFIG_FILES([borlandc/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libbfio.h])
AC_CONFIG_FILES([include/libbfio/definitions.h])
AC_CONFIG_FILES([include/libbfio/features.h])
AC_CONFIG_FILES([include/libbfio/types.h])
AC_CONFIG_FILES([libbfio/libbfio_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([libbfio/libbfio.rc])
AC_CONFIG_FILES([macosx/Introduction.rtf])
AC_CONFIG_FILES([libbfio.pc])
AC_CONFIG_FILES([libbfio.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Building:
   libuna support:              $ac_libbfio_have_libuna

Features:
   Wide character type support: $ac_cv_libbfio_enable_wide_character_type
]);

