# Introduction

Nucleo is a high-level language designed to run at the hardware level and implement direct access to memory and processing through clusters that send and receive data by separating the interface from data processing.

## Hello World

The program "Hello, World" and introduces the minimum code for the operation of the program this excerpt shows how to write in nucleo

```python
print("Hello World!")
```

nucleo source files use the extension `.nu` for the main files and `.nh` for the header files which extend the program and make it more organized.

```console
Hello World!
```

## Program structure

A core program has a hidden entry point which is the function `main` the execution of a core program is done through hidden layers they are matrix, root and main then a core program exposes all layers.

```csharp

access matrix(args, messages, register){
    
    access root(heep, stack){

        access main(){
            print("hello World!");
        }
    }
}
```

the `access` keyword allows the interpreter to change entry points within the program and call in the order of declaration.

```console
hello world!
```

### Memory

The core language is an unmanaged language so all memory management is up to the programmer, for that the core allows accessing the heep and stack through the root layer and controlling the memory management.

### Philosophy

Nucleo means inner/core and a language focused on processes and the transport of data between processes through pipes. in the cluster section we will show how to send and receive data across clusters and have several clusters processing different data.

## Variables and types

In nucleo variable declarations are by inference but it is possible to define a variable type to make visible in certain scopes and make private, restricted, global and permanent data.
Variable declaration with inference

```csharp
name = "Jonh"
age = 23
```

Typed variable declaration

```csharp
string name = "Jonh"
int idade = 23
```

in core the assignment is done using the `=` sign
it is not allowed to change the type of a variable using assignment, instead a `modifier` must be invoked on the `promote` to do the replacement.

```csharp
name = "Jonh"
name = 23
```

```console
type error when assigning an <int> value to <string>
```

Using the `promote` modifier

```csharp
name = "Jonh"
promote name to int(23)
print(name)
```

```console
23
```

### Modifiers, keywords, access levels

so that the core interpreter knows how to manage the data some words are used to allow the programmer to switch types create functions at runtime and define the range of variables between layers and the program as a whole.

### Modifier

modifiers are special structures that change runtime variables, functions and classes. the promote modifier promotes or alters a variable by creating one with the same name and assigning a new value once this data has been promoted all parts of the code using it will get the new value a runtime error will be created if any cause some unexpected error.
promote should be used when a variable is of type collected when a class is generated through several variables and functions following an example of promote using variables and functions and having the data collected next.

```csharp
private name = "Alice"
private age = 18
private phone = 12345
private creditcard = false

public getName(return Name)
public getAge(return age)

promote [name, age, phone, creditcard, getName, getAge] to class(Person)

Person client()

print(client.getName)
print(client.getAge)
```

```console
Alice
18
```
