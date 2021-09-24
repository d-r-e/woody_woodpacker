# woody_woodpacker [WIP]
“Packers” are tools that consist on compressing executable programs (.exe, .dll, .ocx ...) and encrypt them simultaneously. During execution, a program passing through a packer is loaded in memory, compressed and encrypted, then it will be decompressed (decrypted as well) and finally be executed. The creation of this kind of program is linked to the fact that antivirus programs generally analyse programs when they are loaded in memory, before they are executed. Thus, encryption and compression of a packer allow to bypass this behavior by obfuscating the content of an executable until it execution.


[ELF Binary Encryption](https://grugq.github.io/docs/phrack-58-05.txt)

[Elfcrypt](https://web.archive.org/web/20170501112909/http://www.pinkstyle.org/elfcrypt.html)


readelf -S bin
