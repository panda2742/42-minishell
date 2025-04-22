# Details

Date : 2025-04-22 15:18:28

Directory /home/ehosta/Documents/42-minishell/src

Total : 52 files,  2471 codes, 587 comments, 342 blanks, all 3400 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [src/builtins/builtin\_cd.c](/src/builtins/builtin_cd.c) | C | 63 | 11 | 8 | 82 |
| [src/builtins/builtin\_echo.c](/src/builtins/builtin_echo.c) | C | 18 | 11 | 4 | 33 |
| [src/builtins/builtin\_env.c](/src/builtins/builtin_env.c) | C | 50 | 11 | 8 | 69 |
| [src/builtins/builtin\_exit.c](/src/builtins/builtin_exit.c) | C | 18 | 11 | 4 | 33 |
| [src/builtins/builtin\_export.c](/src/builtins/builtin_export.c) | C | 7 | 11 | 3 | 21 |
| [src/builtins/builtin\_pwd.c](/src/builtins/builtin_pwd.c) | C | 18 | 11 | 4 | 33 |
| [src/builtins/builtin\_unset.c](/src/builtins/builtin_unset.c) | C | 42 | 11 | 6 | 59 |
| [src/env\_manager/create\_env.c](/src/env_manager/create_env.c) | C | 90 | 11 | 10 | 111 |
| [src/env\_manager/env\_to\_strlst.c](/src/env_manager/env_to_strlst.c) | C | 41 | 11 | 7 | 59 |
| [src/env\_manager/get\_var.c](/src/env_manager/get_var.c) | C | 15 | 11 | 4 | 30 |
| [src/errors/puterr.c](/src/errors/puterr.c) | C | 21 | 11 | 3 | 35 |
| [src/exec/heredoc/heredoc.c](/src/exec/heredoc/heredoc.c) | C | 14 | 11 | 4 | 29 |
| [src/exec/init/create\_cmd.c](/src/exec/init/create_cmd.c) | C | 80 | 11 | 9 | 100 |
| [src/exec/init/create\_redirect.c](/src/exec/init/create_redirect.c) | C | 62 | 11 | 8 | 81 |
| [src/exec/init/redirect\_manager.c](/src/exec/init/redirect_manager.c) | C | 82 | 11 | 9 | 102 |
| [src/exec/process/exec.c](/src/exec/process/exec.c) | C | 73 | 11 | 6 | 90 |
| [src/exec/process/exec\_utils.c](/src/exec/process/exec_utils.c) | C | 46 | 11 | 7 | 64 |
| [src/exec/process/execute\_builtin.c](/src/exec/process/execute_builtin.c) | C | 13 | 0 | 2 | 15 |
| [src/exec/process/execute\_from\_path.c](/src/exec/process/execute_from_path.c) | C | 54 | 11 | 5 | 70 |
| [src/exec/timeline/create\_child.c](/src/exec/timeline/create_child.c) | C | 22 | 0 | 3 | 25 |
| [src/exec/timeline/create\_cmd\_pipe.c](/src/exec/timeline/create_cmd_pipe.c) | C | 73 | 0 | 6 | 79 |
| [src/exec/timeline/fd\_manager.c](/src/exec/timeline/fd_manager.c) | C | 85 | 0 | 7 | 92 |
| [src/exec/timeline/load\_pipeline\_params.c](/src/exec/timeline/load_pipeline_params.c) | C | 39 | 0 | 5 | 44 |
| [src/exec/timeline/restore\_std.c](/src/exec/timeline/restore_std.c) | C | 25 | 0 | 6 | 31 |
| [src/main.c](/src/main.c) | C | 175 | 22 | 16 | 213 |
| [src/memory/free\_cmds.c](/src/memory/free_cmds.c) | C | 57 | 11 | 8 | 76 |
| [src/memory/free\_env.c](/src/memory/free_env.c) | C | 24 | 11 | 4 | 39 |
| [src/misc/print\_cmds.c](/src/misc/print_cmds.c) | C | 144 | 11 | 6 | 161 |
| [src/misc/show\_prompt.c](/src/misc/show_prompt.c) | C | 62 | 11 | 11 | 84 |
| [src/misc/signals.c](/src/misc/signals.c) | C | 23 | 27 | 5 | 55 |
| [src/parsing/lexer/lexer.c](/src/parsing/lexer/lexer.c) | C | 164 | 23 | 19 | 206 |
| [src/parsing/lexer/lexer\_parse.c](/src/parsing/lexer/lexer_parse.c) | C | 62 | 11 | 9 | 82 |
| [src/parsing/lexer/lexer\_utils.c](/src/parsing/lexer/lexer_utils.c) | C | 23 | 12 | 5 | 40 |
| [src/parsing/tokenizer/expand\_tokens.c](/src/parsing/tokenizer/expand_tokens.c) | C | 219 | 37 | 31 | 287 |
| [src/parsing/tokenizer/fragments.c](/src/parsing/tokenizer/fragments.c) | C | 32 | 20 | 7 | 59 |
| [src/parsing/tokenizer/token\_lexer.c](/src/parsing/tokenizer/token_lexer.c) | C | 47 | 11 | 8 | 66 |
| [src/parsing/tokenizer/token\_list.c](/src/parsing/tokenizer/token_list.c) | C | 78 | 25 | 8 | 111 |
| [src/utils/empty\_tab.c](/src/utils/empty_tab.c) | C | 6 | 11 | 4 | 21 |
| [src/utils/ft\_sprintf.c](/src/utils/ft_sprintf.c) | C | 75 | 11 | 11 | 97 |
| [src/utils/parsing/count\_arg\_words.c](/src/utils/parsing/count_arg_words.c) | C | 17 | 11 | 4 | 32 |
| [src/utils/parsing/free\_str\_return\_null.c](/src/utils/parsing/free_str_return_null.c) | C | 6 | 11 | 3 | 20 |
| [src/utils/parsing/ft\_split\_parser.c](/src/utils/parsing/ft_split_parser.c) | C | 69 | 11 | 10 | 90 |
| [src/utils/parsing/ft\_str\_join\_free.c](/src/utils/parsing/ft_str_join_free.c) | C | 31 | 11 | 5 | 47 |
| [src/utils/parsing/ft\_strcmp.c](/src/utils/parsing/ft_strcmp.c) | C | 11 | 11 | 4 | 26 |
| [src/utils/parsing/get\_first\_word.c](/src/utils/parsing/get_first_word.c) | C | 16 | 11 | 4 | 31 |
| [src/utils/parsing/handle\_is\_redir\_token.c](/src/utils/parsing/handle_is_redir_token.c) | C | 15 | 11 | 3 | 29 |
| [src/utils/parsing/incr\_on\_alnum.c](/src/utils/parsing/incr_on_alnum.c) | C | 0 | 0 | 1 | 1 |
| [src/utils/parsing/is\_redir.c](/src/utils/parsing/is_redir.c) | C | 6 | 11 | 3 | 20 |
| [src/utils/parsing/join\_token\_to\_string.c](/src/utils/parsing/join_token_to_string.c) | C | 19 | 11 | 4 | 34 |
| [src/utils/parsing/print\_t\_token\_list.c](/src/utils/parsing/print_t_token_list.c) | C | 19 | 14 | 4 | 37 |
| [src/utils/parsing/skip\_spaces.c](/src/utils/parsing/skip_spaces.c) | C | 6 | 11 | 3 | 20 |
| [src/utils/parsing/token\_lstsize.c](/src/utils/parsing/token_lstsize.c) | C | 14 | 11 | 4 | 29 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)