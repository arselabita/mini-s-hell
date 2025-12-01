#### Level 1 — simple single commands

ls
pwd
whoami
date
echo hello
echo -n hello
echo "$USER"
echo '$USER'
cd ..
cd /tmp
env
export
unset
exit

#### Level 2 — tokens & arguments

ls -la
grep main minishell.c
cat Makefile
mkdir testdir
rm -f a.out
touch foo.txt

#### Level 3 — PATH resolution

/bin/ls
/usr/bin/env
./minishell
/bin/echo hello

#### Level 4 — redirections (<, >, >>)

ls > out.txt
echo hi > file.txt
cat < file.txt
echo append >> file.txt
grep hello < input.txt > output.txt
wc -l < file.txt >> stats.txt

#### Level 5 — heredoc (<<)

cat << EOF
grep hi << limiter
sort << END


#### Level 6 — pipes "|"

ls | wc
cat file.txt | grep hello
ls -l | grep minishell
env | sort
ps aux | grep bash | wc -l
cat < in | grep x | wc > out

### Level 7 — environment variable expansion

echo $HOME
echo $USER
echo "$HOME $USER"
echo $?
echo $PATH
echo "$NOTSET"

#### Level 8 — mixed complexity

echo $HOME | cat
cd /tmp | pwd
cat << EOF | grep hi
export FOO=bar
echo $FOO
unset FOO

#### Level 9 — quote handling

echo "hello world"
echo 'hello $USER'
echo "$USER'$USER'"
echo "'$PATH'"

#### Level 10 — realistic combinations

ls -la | grep "\.c" | wc -l
cat << END | sort
echo "$PWD" > test.txt
cd "$(dirname "$PWD")"
env | grep SHLVL
printf "hi\n\n"
