# Level01 Documentation

## Objective
Gain access to the `flag01` account and retrieve the token for the next level (`level02`).

---

## Approach & Tools
- **Technique**: Password hash cracking using John the Ripper.
- **Commands**: `cat`, `echo`, `su`, `getflag`.
- **Tools**: [John the Ripper](https://www.openwall.com/john/) (external tool on a separate OS).

---

## Step-by-Step Solution

### 1. Locate the Encrypted Password in `/etc/passwd`
Inspect the `/etc/passwd` file to find the `flag01` entry:
```bash
cat /etc/passwd | grep flag01
```
#### Output:
```bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

### 2. Extract the Hash

The encrypted password is 42hDRfypTqqnw. Save it to a file:
bash
```bash
echo "42hDRfypTqqnw" > hash
```

### 3. Crack the Hash with John the Ripper

John the Ripper is required but not available on the Snow Crash ISO. Use it on another OS:
```bash
john hash --show
```
#### Output:
```
?:abcdefg

1 password hash cracked, 0 left
```

### 4. Access flag01 and Retrieve the Token

Switch to the flag01 account and run getflag:
```bash

su flag01
Password: abcdefg
getflag
```

#### Output:
```bash
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
```

### Key Takeaways

* Check /etc/passwd: Look for user entries with encrypted passwords.

* John the Ripper: A powerful tool for cracking password hashes.

* Environment Constraints: Adapt to tool limitations by using external systems when necessar