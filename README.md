# :scroll: virtual-machine
A virtual machine I've been working on over the weekend, includes a lexer and a bytecode generator so that you can write code in a file which is then compiled into the VM's bytecode and ran.
Code could most likely be improved in some places, meaning pull requests are welcome as always.

### :exploding_head: Features
* Artihmetic instructions (addition, subtraction, multiplication, division)
* Stack value pushing/popping
* Several registers
* Large numeric value support
* Debug mode (more specified in the flags section)
* Interpreter supports running in both x64 and x86

### :bulb: Todo
* Add floating point value support
* Add strings, chars and printing
* Add comments

### :checkered_flag: Flags
* **'-b'** - **Build flag**, compiles the content in your inputted file and saves it to a file
* **'-d'** - **Debug flag**, skips code compilation and instead just converts it to bytecode then runs it through the VM
* **'-o'** - **Out flag**, lets you specify the binary's file name after the flag is pass

### Usage examples
##### Compiling code (-o flag is optional)
```bash
$ virtual-machine code.txt -b -o output.bin
```
##### Running code without compilation
```bash
$ virtual-machine code.txt -d
```

### :gear: Example code
```asm
add vax, 2
mul vax, 4
div vax, 2

mov vax, 0

push 9000
push 2000

pop vax
pop vbx
```
###### Example output
```bash
..
vax = 2
vax = 8
vax = 4
vax = 0
popped 2000 onto vax
popped 9000 onto vbx
```
