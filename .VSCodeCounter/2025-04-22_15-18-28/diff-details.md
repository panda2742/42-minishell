# Diff Details

Date : 2025-04-22 15:18:28

Directory /home/ehosta/Documents/42-minishell/src

Total : 107 files,  -2205 codes, -1243 comments, -518 blanks, all -3966 lines

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [CONTRIBUTING.md](/CONTRIBUTING.md) | Markdown | -67 | 0 | -28 | -95 |
| [Makefile](/Makefile) | Makefile | -93 | -18 | -41 | -152 |
| [README.md](/README.md) | Markdown | -14 | 0 | -6 | -20 |
| [include/minishell.h](/include/minishell.h) | C | -261 | -157 | -43 | -461 |
| [lib/Makefile](/lib/Makefile) | Makefile | -38 | -11 | -11 | -60 |
| [lib/README.md](/lib/README.md) | Markdown | -4 | 0 | -2 | -6 |
| [lib/include/ft\_array.h](/lib/include/ft_array.h) | C++ | -37 | -11 | -6 | -54 |
| [lib/include/ft\_base.h](/lib/include/ft_base.h) | C++ | -33 | -11 | -6 | -50 |
| [lib/include/ft\_fd.h](/lib/include/ft_fd.h) | C++ | -11 | -61 | -10 | -82 |
| [lib/include/ft\_free.h](/lib/include/ft_free.h) | C++ | -7 | -11 | -4 | -22 |
| [lib/include/ft\_is.h](/lib/include/ft_is.h) | C++ | -12 | -38 | -12 | -62 |
| [lib/include/ft\_lst.h](/lib/include/ft_lst.h) | C++ | -19 | -11 | -6 | -36 |
| [lib/include/ft\_math.h](/lib/include/ft_math.h) | C++ | -6 | -11 | -3 | -20 |
| [lib/include/ft\_mem.h](/lib/include/ft_mem.h) | C | -12 | -15 | -5 | -32 |
| [lib/include/ft\_misc.h](/lib/include/ft_misc.h) | C++ | -4 | -11 | -3 | -18 |
| [lib/include/ft\_printf.h](/lib/include/ft_printf.h) | C++ | -10 | -11 | -6 | -27 |
| [lib/include/ft\_str.h](/lib/include/ft_str.h) | C++ | -21 | -11 | -5 | -37 |
| [lib/include/ft\_to.h](/lib/include/ft_to.h) | C++ | -11 | -11 | -5 | -27 |
| [lib/include/get\_next\_line.h](/lib/include/get_next_line.h) | C++ | -12 | -19 | -5 | -36 |
| [lib/include/libft.h](/lib/include/libft.h) | C | -16 | -11 | -4 | -31 |
| [lib/src/array/ft\_array\_clear.c](/lib/src/array/ft_array_clear.c) | C | -14 | -11 | -3 | -28 |
| [lib/src/array/ft\_array\_cpy.c](/lib/src/array/ft_array_cpy.c) | C | -49 | -11 | -9 | -69 |
| [lib/src/array/ft\_array\_fill.c](/lib/src/array/ft_array_fill.c) | C | -21 | -11 | -7 | -39 |
| [lib/src/array/ft\_array\_getmax.c](/lib/src/array/ft_array_getmax.c) | C | -16 | -11 | -4 | -31 |
| [lib/src/array/ft\_array\_getmin.c](/lib/src/array/ft_array_getmin.c) | C | -16 | -11 | -4 | -31 |
| [lib/src/array/ft\_array\_getpos.c](/lib/src/array/ft_array_getpos.c) | C | -14 | -11 | -4 | -29 |
| [lib/src/array/ft\_array\_getsorted.c](/lib/src/array/ft_array_getsorted.c) | C | -27 | -11 | -4 | -42 |
| [lib/src/array/ft\_array\_getval.c](/lib/src/array/ft_array_getval.c) | C | -20 | -11 | -4 | -35 |
| [lib/src/array/ft\_array\_issorted.c](/lib/src/array/ft_array_issorted.c) | C | -13 | -11 | -4 | -28 |
| [lib/src/array/ft\_array\_new.c](/lib/src/array/ft_array_new.c) | C | -22 | -11 | -4 | -37 |
| [lib/src/array/ft\_array\_popint.c](/lib/src/array/ft_array_popint.c) | C | -23 | -11 | -4 | -38 |
| [lib/src/array/ft\_array\_posdist.c](/lib/src/array/ft_array_posdist.c) | C | -21 | -11 | -4 | -36 |
| [lib/src/array/ft\_array\_prints.c](/lib/src/array/ft_array_prints.c) | C | -51 | -11 | -8 | -70 |
| [lib/src/array/ft\_array\_pushint.c](/lib/src/array/ft_array_pushint.c) | C | -18 | -11 | -4 | -33 |
| [lib/src/fd/ft\_putchar\_fd.c](/lib/src/fd/ft_putchar_fd.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/fd/ft\_putendl\_fd.c](/lib/src/fd/ft_putendl_fd.c) | C | -13 | -11 | -4 | -28 |
| [lib/src/fd/ft\_putnbr\_base\_fd.c](/lib/src/fd/ft_putnbr_base_fd.c) | C | -24 | -11 | -4 | -39 |
| [lib/src/fd/ft\_putnbr\_fd.c](/lib/src/fd/ft_putnbr_fd.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/fd/ft\_putptr\_fd.c](/lib/src/fd/ft_putptr_fd.c) | C | -17 | -11 | -4 | -32 |
| [lib/src/fd/ft\_putstr\_fd.c](/lib/src/fd/ft_putstr_fd.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/free/ft\_free\_inttab.c](/lib/src/free/ft_free_inttab.c) | C | -6 | -11 | -3 | -20 |
| [lib/src/free/ft\_free\_str.c](/lib/src/free/ft_free_str.c) | C | -6 | -11 | -3 | -20 |
| [lib/src/free/ft\_free\_strtab.c](/lib/src/free/ft_free_strtab.c) | C | -10 | -11 | -4 | -25 |
| [lib/src/get\_next\_line/get\_next\_line.c](/lib/src/get_next_line/get_next_line.c) | C | -87 | -11 | -11 | -109 |
| [lib/src/is/ft\_isalnum.c](/lib/src/is/ft_isalnum.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/is/ft\_isalpha.c](/lib/src/is/ft_isalpha.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/is/ft\_isascii.c](/lib/src/is/ft_isascii.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/is/ft\_isdigit.c](/lib/src/is/ft_isdigit.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/is/ft\_isincharset.c](/lib/src/is/ft_isincharset.c) | C | -11 | -11 | -3 | -25 |
| [lib/src/is/ft\_isprint.c](/lib/src/is/ft_isprint.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/is/ft\_issorted.c](/lib/src/is/ft_issorted.c) | C | -9 | -11 | -4 | -24 |
| [lib/src/is/ft\_isspace.c](/lib/src/is/ft_isspace.c) | C | -8 | -11 | -3 | -22 |
| [lib/src/lst/ft\_lstadd\_back.c](/lib/src/lst/ft_lstadd_back.c) | C | -8 | -11 | -3 | -22 |
| [lib/src/lst/ft\_lstadd\_front.c](/lib/src/lst/ft_lstadd_front.c) | C | -8 | -11 | -3 | -22 |
| [lib/src/lst/ft\_lstclear.c](/lib/src/lst/ft_lstclear.c) | C | -14 | -11 | -4 | -29 |
| [lib/src/lst/ft\_lstdelone.c](/lib/src/lst/ft_lstdelone.c) | C | -9 | -11 | -3 | -23 |
| [lib/src/lst/ft\_lstiter.c](/lib/src/lst/ft_lstiter.c) | C | -11 | -11 | -3 | -25 |
| [lib/src/lst/ft\_lstlast.c](/lib/src/lst/ft_lstlast.c) | C | -9 | -11 | -3 | -23 |
| [lib/src/lst/ft\_lstmap.c](/lib/src/lst/ft_lstmap.c) | C | -24 | -11 | -4 | -39 |
| [lib/src/lst/ft\_lstnew.c](/lib/src/lst/ft_lstnew.c) | C | -11 | -11 | -4 | -26 |
| [lib/src/lst/ft\_lstsize.c](/lib/src/lst/ft_lstsize.c) | C | -19 | -11 | -4 | -34 |
| [lib/src/math/ft\_abs.c](/lib/src/math/ft_abs.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/math/ft\_sign.c](/lib/src/math/ft_sign.c) | C | -5 | -11 | -3 | -19 |
| [lib/src/math/ft\_sqrt.c](/lib/src/math/ft_sqrt.c) | C | -8 | -11 | -3 | -22 |
| [lib/src/mem/ft\_bzero.c](/lib/src/mem/ft_bzero.c) | C | -11 | -11 | -4 | -26 |
| [lib/src/mem/ft\_calloc.c](/lib/src/mem/ft_calloc.c) | C | -14 | -11 | -4 | -29 |
| [lib/src/mem/ft\_memalloc.c](/lib/src/mem/ft_memalloc.c) | C | -10 | -11 | -5 | -26 |
| [lib/src/mem/ft\_memchr.c](/lib/src/mem/ft_memchr.c) | C | -13 | -11 | -4 | -28 |
| [lib/src/mem/ft\_memcmp.c](/lib/src/mem/ft_memcmp.c) | C | -15 | -11 | -4 | -30 |
| [lib/src/mem/ft\_memcpy.c](/lib/src/mem/ft_memcpy.c) | C | -18 | -11 | -4 | -33 |
| [lib/src/mem/ft\_memmove.c](/lib/src/mem/ft_memmove.c) | C | -19 | -11 | -4 | -34 |
| [lib/src/mem/ft\_memset.c](/lib/src/mem/ft_memset.c) | C | -12 | -11 | -4 | -27 |
| [lib/src/misc/ft\_selection\_sort.c](/lib/src/misc/ft_selection_sort.c) | C | -25 | -11 | -4 | -40 |
| [lib/src/printf/ft\_printf.c](/lib/src/printf/ft_printf.c) | C | -92 | -11 | -12 | -115 |
| [lib/src/str/ft\_split.c](/lib/src/str/ft_split.c) | C | -85 | -11 | -10 | -106 |
| [lib/src/str/ft\_strchr.c](/lib/src/str/ft_strchr.c) | C | -15 | -11 | -4 | -30 |
| [lib/src/str/ft\_strdup.c](/lib/src/str/ft_strdup.c) | C | -19 | -11 | -4 | -34 |
| [lib/src/str/ft\_striteri.c](/lib/src/str/ft_striteri.c) | C | -13 | -11 | -4 | -28 |
| [lib/src/str/ft\_strjoin.c](/lib/src/str/ft_strjoin.c) | C | -24 | -11 | -4 | -39 |
| [lib/src/str/ft\_strlcat.c](/lib/src/str/ft_strlcat.c) | C | -21 | -11 | -4 | -36 |
| [lib/src/str/ft\_strlcpy.c](/lib/src/str/ft_strlcpy.c) | C | -20 | -11 | -4 | -35 |
| [lib/src/str/ft\_strlen.c](/lib/src/str/ft_strlen.c) | C | -11 | -11 | -4 | -26 |
| [lib/src/str/ft\_strlenc.c](/lib/src/str/ft_strlenc.c) | C | -11 | -11 | -4 | -26 |
| [lib/src/str/ft\_strmapi.c](/lib/src/str/ft_strmapi.c) | C | -19 | -11 | -4 | -34 |
| [lib/src/str/ft\_strncmp.c](/lib/src/str/ft_strncmp.c) | C | -23 | -11 | -3 | -37 |
| [lib/src/str/ft\_strnstr.c](/lib/src/str/ft_strnstr.c) | C | -26 | -11 | -4 | -41 |
| [lib/src/str/ft\_strrchr.c](/lib/src/str/ft_strrchr.c) | C | -12 | -11 | -4 | -27 |
| [lib/src/str/ft\_strtrim.c](/lib/src/str/ft_strtrim.c) | C | -35 | -11 | -7 | -53 |
| [lib/src/str/ft\_substr.c](/lib/src/str/ft_substr.c) | C | -34 | -11 | -7 | -52 |
| [lib/src/to/ft\_atoi.c](/lib/src/to/ft_atoi.c) | C | -26 | -11 | -4 | -41 |
| [lib/src/to/ft\_itoa.c](/lib/src/to/ft_itoa.c) | C | -63 | -11 | -9 | -83 |
| [lib/src/to/ft\_tolower.c](/lib/src/to/ft_tolower.c) | C | -7 | -11 | -3 | -21 |
| [lib/src/to/ft\_toupper.c](/lib/src/to/ft_toupper.c) | C | -7 | -11 | -3 | -21 |
| [lib/variables.mk](/lib/variables.mk) | Makefile | -127 | -11 | -4 | -142 |
| [src/builtins/builtin\_env.c](/src/builtins/builtin_env.c) | C | -3 | 0 | 0 | -3 |
| [src/builtins/builtin\_exit.c](/src/builtins/builtin_exit.c) | C | -1 | 0 | 0 | -1 |
| [src/builtins/builtin\_pwd.c](/src/builtins/builtin_pwd.c) | C | -3 | 0 | 0 | -3 |
| [src/builtins/builtin\_unset.c](/src/builtins/builtin_unset.c) | C | -2 | 0 | 0 | -2 |
| [src/errors/error\_handler.c](/src/errors/error_handler.c) | C | -7 | -11 | -3 | -21 |
| [src/exec/init/create\_cmd.c](/src/exec/init/create_cmd.c) | C | -1 | 0 | 0 | -1 |
| [src/exec/process/exec.c](/src/exec/process/exec.c) | C | -25 | 0 | 0 | -25 |
| [src/exec/process/execute\_builtin.c](/src/exec/process/execute_builtin.c) | C | 4 | 0 | -2 | 2 |
| [src/exec/timeline/create\_cmd\_pipe.c](/src/exec/timeline/create_cmd_pipe.c) | C | 2 | 0 | 0 | 2 |
| [src/exec/timeline/restore\_std.c](/src/exec/timeline/restore_std.c) | C | 24 | 0 | 3 | 27 |
| [src/main.c](/src/main.c) | C | 1 | 0 | 0 | 1 |
| [src/misc/print\_cmds.c](/src/misc/print_cmds.c) | C | -1 | 0 | 0 | -1 |
| [src/parsing/tokenizer/expand\_tokens.c](/src/parsing/tokenizer/expand_tokens.c) | C | 9 | 11 | 12 | 32 |

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details