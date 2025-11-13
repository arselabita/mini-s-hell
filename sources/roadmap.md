Minishell Roadmap & Task Plan (Two-Partner Setup)
Phase 0 – Repository & Standards

Owner: Both

Goals:

Shared Git repository created.

main branch protected.

CI or simple script checks Norm + build.

Makefile with required rules (NAME, all, clean, fclean, re).

Definition of Done (DoD):

Running make && ./minishell starts the program (even if it’s just an empty loop).

Notes:

Make sure the Makefile doesn’t relink unnecessarily.

Always use -Wall -Wextra -Werror.

Phase 1 – Basic REPL (Read–Eval–Print–Loop)

Owner: Partner A

Goals:

Prompt is displayed.

readline() works with history.

Empty input just prints a new prompt.

DoD:

Typing echo hi → not executed yet, but history works (↑ key).

Notes:

readline may leak, but your own code must not leak.

Phase 2 – Lexer / Tokenizer

Owner: Partner A

Goals:

Input split into tokens: words and operators (<, >, <<, >>, |).

Quotes (' and ") correctly group tokens.

Unclosed quotes rejected.

DoD:

echo "a b" → one argument a b.

echo 'x$y' → literal string x$y.

Phase 3 – Parser (Command Structures)

Owner: Partner A

Goals:

Convert tokens into structured commands (AST or table).

Each command has argv, redirections, etc.

Detect syntax errors.

DoD:

Input: cat < in | grep x > out → produces two commands with correct in/out.

Phase 4 – Path Search + execve

Owner: Partner B

Goals:

Executables found via PATH or absolute/relative path.

Proper error messages and exit codes.

DoD:

Run:

ls

/bin/echo ok

./a.out

Compare errors with Bash:

127 for “command not found”

126 for permission denied.

Phase 5 – Simple Builtins

Owner: Partner B

Goals:

Implement: echo -n, pwd, env (no args).

Create builtin dispatch mechanism.

DoD:

echo -n hi → no newline.

pwd → shows current directory.

env → lists environment variables.

Phase 6 – Environment Expansion

Owner: Partner A

Goals:

$VAR expands to env value.

$? expands to last exit code.

No expansion inside single quotes.

Expansion inside double quotes allowed.

DoD:

export X=42; echo "$X" → prints 42.

echo '$X' → prints $X.

After failed command, echo $? prints error code.

Notes:

Unset vars expand to empty string.

$ alone should stay $.

Phase 7 – Redirections

Owner: Partner B

Goals:

Implement <, >, >>.

Proper FD duplication and closing.

Error handling with perror.

DoD:

echo hi > f && cat < f.

echo x >> f.

Phase 8 – Heredoc (<<)

Owner: Partner A

Goals:

Read input until delimiter.

Feed heredoc input into stdin.

No history updates during heredoc.

Signals (Ctrl-C) cancel heredoc.

DoD:

cat <<EOF → type lines until EOF.

Notes:

Check if environment variable expansion inside heredoc is required (subject-specific).

Phase 9 – Pipes

Owner: Partner B

Goals:

Support multiple pipes.

Output of one command → input of next.

Proper closing of unused FDs.

DoD:

printf "a\nb\n" | grep b | wc -l → prints 1.

Phase 10 – Stateful Builtins

Owner: Partner B

Goals:

Implement: cd, export, unset, exit.

Update PWD and OLDPWD.

exit closes shell with correct exit code.

DoD:

cd /; pwd → changes dir.

export A=1; echo $A → prints 1.

unset A; echo $A → empty.

exit 42 → shell exits with code 42.

Phase 11 – Signals & TTY Behavior

Owner: Partner A

Goals:

Ctrl-C → new line + prompt.

Ctrl-D → exit shell.

Ctrl-\ → does nothing.

Only one global variable (int) for signals.

DoD:

Run cat, press Ctrl-C → interrupted.

At prompt, press Ctrl-D → exits.

Phase 12 – Errors & Exit Codes

Owner: Both

Goals:

Consistent error handling with perror/strerror.

Exit codes match Bash behavior.

DoD:

Invalid command → exit code 127.

No permission → exit code 126.

$? always shows last exit code.

Phase 13 – Memory & Resource Cleanup

Owner: Both

Goals:

No memory leaks (except readline).

All FDs closed properly.

Free all allocated memory.

DoD:

Run valgrind ./minishell → no leaks except readline’s known leak.

Phase 14 – Bonus (only if mandatory is perfect)

Owner: —

Goals:

Implement && and ||.

Support parentheses for precedence.

Implement wildcard expansion (*).

DoD:

false && echo x → no output.

true || echo x → no output.

echo a* → expands to files in current directory.

Notes:

Bonus is evaluated only if mandatory is 100% correct.