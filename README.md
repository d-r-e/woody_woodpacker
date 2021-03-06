# woody_woodpacker
“Packers” are tools that consist on compressing executable programs and encrypt them simultaneously. During execution, a program passing through a packer is loaded in memory, compressed and encrypted, then it will be decompressed (decrypted as well) and finally be executed. The creation of this kind of program is linked to the fact that antivirus programs generally analyse programs when they are loaded in memory, before they are executed. Thus, encryption and compression of a packer allow to bypass this behavior by obfuscating the content of an executable until it execution.

## ELF Packer: Obfuscation

Woody_woodpacker encrypts an ELF binary passed as parameter and injects a decriptor on the executable, so its execution remains intact in memory.
It injects the code finding an empty "code cave" in any PT_LOAD segment.

![](https://upload.wikimedia.org/wikipedia/commons/e/e4/ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png)

[To begin](https://gist.github.com/CMCDragonkai/10ab53654b2aa6ce55c11cfc5b2432a4)

[ELF Binary Encryption](https://grugq.github.io/docs/phrack-58-05.txt)

[Elfcrypt](https://web.archive.org/web/20170501112909/http://www.pinkstyle.org/elfcrypt.html)

[Unix viruses](https://www.win.tue.nl/~aeb/linux/hh/virus/unix-viruses.txt)

[Elf Infection (in french)](https://www.root-me.org/fr/Documentation/Applicatif/ELF-Injection?q=%2Fen%2FDocumentation%2FApplicatif%2FELF-Injection) 

[Elf injector step by step](https://0x00sec.org/t/elfun-file-injector/410)

[PIE Elf injector code example](https://github.com/mfaerevaag/elfinjector)

[Some curiosities](http://phrack.org/issues/61/8.html#article)

```readelf -S bin```

```binwalk -W bin1 bin2 (-o 0x0ffset) | less```
