# Minishell

This is a project from 42 Network Cursus.
<br/>
The objective is to create a simple bash-like shell.
This is a good approach to learn more about processes, signals, file descriptors.. and much more.

## Usage:

```sh
$ make run
```

### Allowed functions:

```
malloc() free()
write() open() read()
fork() wait() waitpid() wait3() wait4()
getcwd() chdir() opendir() readdir() closedir()
stat() lstat() fstat()
execve() pipe() dup() dup2()
signal() kill() close() exit()
strerror() errno()
```

### Resources

- https://brennan.io/2015/01/16/write-a-shell-in-c/
- https://harm-smits.github.io/42docs/projects/minishell
- https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- [Exit codes](https://tldp.org/LDP/abs/html/exitcodes.html)
- [Single/Double Quotes differences](https://stackoverflow.com/questions/6697753/difference-between-single-and-double-quotes-in-bash/6697781#6697781)
- [Chapter 5. Writing Your Own Shell](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/9b69dc6c-240b-412c-a7f0-5af9ff068317/Chapter5-WritingYourOwnShell.pdf?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAT73L2G45O3KS52Y5%2F20210924%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20210924T105534Z&X-Amz-Expires=86400&X-Amz-Signature=7608d68b64d10a16e90518bdab8238ff4aadf821a6b4de9e76cbf7916e904b4f&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22Chapter5-WritingYourOwnShell.pdf%22) (PDF)
