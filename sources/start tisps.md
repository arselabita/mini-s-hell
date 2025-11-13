
#### start with good signal handler( ctrl + D, ctrl +C, etc....), readline tc...

#### implment quting check valid
### --> iterate string and find " (quote symbol)
###			-> check is there \ one index before??
#### -> if not quote index is startindex then iterate through to find second " quote symbol and set bool flag to false


## filter the string input if its noquote, single, quote or double quote and also the type (command, string, args, flag, in_fd, out_fd)


struct cmds{
char *word;
int quote -> 1 = No_QUOTE, 2 = SINGLE_QUOTE, 3 = DOUBLE_QUOTE
}
