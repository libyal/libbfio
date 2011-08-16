AC_PREREQ( 2.59 )

AC_INIT(
 [libbfio],
 [20110816],
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
COMMON_ARG_ENABLE(
 [wide-character-type],
 [wide_character_type],
 [enable wide character type support],
 [no])
COMMON_ARG_ENABLE(
 [winapi],
 [winapi],
 [enable WINAPI support for cross-compilation],
 [auto-detect])

COMMON_ARG_WITH(
 [libuna],
 [libuna],
 [search for libuna in includedir and libdir or in the specified DIR, or no if to use local version],
 [auto-detect],
 [DIR])

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
AC_CHECK_WINAPI

dnl Check for type definitions
AC_CHECK_LOCAL_TYPES

dnl Check for headers
dnl Headers included in libbfio/libbfio_file.c
AC_CHECK_HEADERS([errno.h fcntl.h sys/stat.h unistd.h])

dnl Check for functions
dnl File input/output functions used in libbfio/libbfio_file.h
AC_CHECK_FUNCS(
 [close],
 [],
 [AC_MSG_FAILURE(
  [Missing function: close],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [fstat],
 [],
 [AC_MSG_FAILURE(
  [Missing function: fstat],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [ftruncate],
 [],
 [AC_MSG_FAILURE(
  [Missing function: ftruncate],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [lseek],
 [],
 [AC_MSG_FAILURE(
  [Missing function: lseek],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [open],
 [],
 [AC_MSG_FAILURE(
  [Missing function: open],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [read],
 [],
 [AC_MSG_FAILURE(
  [Missing function: read],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [stat],
 [],
 [AC_MSG_FAILURE(
  [Missing function: stat],
  [1])
 ])
 
AC_CHECK_FUNCS(
 [write],
 [],
 [AC_MSG_FAILURE(
  [Missing function: write],
  [1])
 ])

dnl Check for error string functions used in libbfio/libbfio_error_string.c
AC_FUNC_STRERROR_R()

AS_IF(
 [test "x$ac_cv_have_decl_strerror_r" = xno],
 [AC_CHECK_FUNCS(
  [strerror],
  [],
  [AC_MSG_FAILURE(
   [Missing functions: strerror_r and strerror],
   [1])
  ])
 ])

dnl Check for printf conversion specifier support
AC_CHECK_FUNC_PRINTF_JD
AC_CHECK_FUNC_PRINTF_ZD

dnl Checks for libraries and library functions
dnl ac_libbfio_dummy is used to prevent AC_CHECK_LIB adding unnecessary -l<library> arguments
AC_CHECK_LOCAL_COMMON
AC_CHECK_LOCAL_LIBCSTRING
AC_CHECK_LOCAL_LIBERROR
AC_CHECK_LOCAL_LIBNOTIFY

dnl Check for enabling libuna for Unicode string support
AC_CHECK_LIBUNA

AS_IF(
 [test "x$ac_cv_libuna" = xyes],
 [AC_SUBST(
  [libewf_pc_libs_private_libuna],
  [-luna])
 ])

AS_IF(
 [test "x$ac_cv_libuna" = xyes],
 [AC_SUBST(
  [libewf_spec_requires_libuna],
  [libuna])
 AC_SUBST(
  [libewf_spec_build_requires_libuna],
  [libuna-devel])
 ])

AS_IF(
 [test "x$ac_cv_libuna" != xyes],
 [AC_DEFINE(
  [HAVE_LOCAL_LIBUNA],
  [1],
  [Define to 1 if the local version of libuna is used.])
 AC_SUBST(
  [HAVE_LOCAL_LIBUNA],
  [1])
 AC_SUBST(
  [LIBUNA_CPPFLAGS],
  [-I../libuna])
 AC_SUBST(
  [LIBUNA_LIBADD],
  [../libuna/libuna.la])
 ac_cv_libuna=local
 ])

AM_CONDITIONAL(
 [HAVE_LOCAL_LIBUNA],
 [test "x$ac_cv_libuna" = xlocal])

dnl Check if libbfio should be build with verbose output
AS_IF(
 [test "x$ac_cv_enable_verbose_output" != xno ],
 [AC_DEFINE(
 [HAVE_VERBOSE_OUTPUT],
 [1],
 [Define to 1 if verbose output should be used.])
 ac_cv_enable_verbose_output=yes])

dnl Check if libbfio should be build with debug output
AS_IF(
 [test "x$ac_cv_enable_debug_output" != xno ],
 [AC_DEFINE(
 [HAVE_DEBUG_OUTPUT],
 [1],
 [Define to 1 if debug output should be used.])
 ac_cv_enable_debug_output=yes])

dnl Check if requires and build requires should be set in spec file
AS_IF(
 [test "x$ac_cv_libuna" = xyes],
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
AC_CONFIG_FILES([examples/Makefile])
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
   libuna support:              $ac_cv_libuna

Features:
   Wide character type support: $ac_cv_enable_wide_character_type
]);

