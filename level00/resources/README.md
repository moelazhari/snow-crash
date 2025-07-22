# Level00 Documentation

## Objective
Gain access to the `flag00` account and retrieve the token for the next level (`level01`).

---

## Approach & Tools
- **Technique**: File system enumeration, Caesar cipher decryption.
- **Commands**: `find`, `cat`, `su`, `getflag`.
- **Tools**: [dcode](https://www.dcode.fr/rot-cipher) Caesar Cipher Decoder.

---

## Step-by-Step Solution

### 1. Locate Files Owned by `flag00
Run the `find` command to identify files accessible only to the `flag00` 
```bash
find / -user flag00 2>/dev/null
```
#### Output:
```bash
/usr/sbin/john
/rofs/usr/sbin/john
```
### 2. Inspect the Files

Both files contain the same encrypted string:

```bash
cat /usr/sbin/john
```
#### Output:
```bash
cdiiddwpgswtgt
```

### 3. Decrypt the String

The string cdiiddwpgswtgt is encrypted with ROT15 (shift of 15).
Using Cryptii, decrypt it to:
```bash
nottoohardhere
```

### 4. Access flag00 and Retrieve the Token

Switch to the flag00 account and run getflag:
```bash

su flag00
Password: nottoohardhere
getflag
```

#### Output:
```bash
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```

### Key Takeaways

* Use find -user to identify files owned by specific users.

* Always test multiple cipher shifts if decryption is unclear.