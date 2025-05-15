# Level02 Documentation

## Objective
Retrieve the password for the `flag02` account by analyzing a network packet capture (PCAP) file.

---

## Approach & Tools
- **Technique**: Network traffic analysis, ASCII/hex decoding.
- **Commands**: `scp`, `su`, `getflag`.
- **Tools**: [Wireshark](https://www.wireshark.org/) (external tool for PCAP analysis).

---

## Step-by-Step Solution

once we log into level02 account we find a [.pcap](https://fileinfo.com/extension/pcap) file named ```level02.pcap```.
```bash
ls -la /home/user/level02/
```
#### Output:
```bash
-r-------- 1 level02 level02 1234 Jan 1 12:34 level02.pcap
```
### 1. Transfer the PCAP File to Your Local Machine

Use scp to copy the file (replace 192.168.1.92 with your VM’s IP):
bash
```bash
scp -P 4242 level02@192.168.1.92:/home/user/level02/level02.pcap .
```

### 2. Analyze the PCAP in Wireshark

* Open level02.pcap in Wireshark.

* Search for packets containing the keyword "Password".

* Follow the TCP stream of the relevant packet (Right-click → Follow → TCP Stream).

### 3. Decode the Password

In the TCP stream, you’ll see:

    Password: ft_wandr...NDRel.L0L

Non-printable characters (dots) indicate hidden data. Switch the display format to "Hex Dump" to view hex values:
```bash
000000B9  66                                                 f
000000BA  74                                                 t
000000BB  5f                                                 _
000000BC  77                                                 w
000000BD  61                                                 a
000000BE  6e                                                 n
000000BF  64                                                 d
000000C0  72                                                 r
000000C1  7f                                                 .
000000C2  7f                                                 .
000000C3  7f                                                 .
000000C4  4e                                                 N
000000C5  44                                                 D
000000C6  52                                                 R
000000C7  65                                                 e
000000C8  6c                                                 l
000000C9  7f                                                 .
000000CA  4c                                                 L
000000CB  30                                                 0
000000CC  4c                                                 L
000000CD  0d                                                 .
```

### Reconstructing the Password:

1. The user typed ```ft_wandr```.

2. Pressed Delete 3 times (hex ```0x7f``` is Delete), erasing ```ndr```.

3. Continued with ```NDRel```.

4. Pressed Delete once (erasing ```l```).

5. Finished with ```L0L```.

#### Final Password: ```ft_waNDReL0L```

### 4. Access flag01 and Retrieve the Token

Switch to the flag02 account and run getflag:
```bash
su flag02
Password: ft_waNDReL0L
getflag
```

#### Output:
```bash
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
```

### Key Takeaways

* PCAP Analysis: Use Wireshark to inspect network traffic for sensitive data.

*  Hex Decoding: Non-printable characters can be decoded by switching display formats (e.g., hex dump).

* Backspace Handling: Account for 0x7f (Delete) when reconstructing user input.