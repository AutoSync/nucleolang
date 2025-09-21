# Introduction

Nucleo is a high-level language designed to run at the hardware level and implement direct access to memory and processing through clusters that send and receive data by separating the interface from data processing.

## Hello World

The program "Hello, World" and introduces the minimum code for the operation of the program this excerpt shows how to write in nucleo

```csharp
console out "Hello World!"
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
            name = "Pedro"
            age = 18
            console out name + age >= 18 : " can drive" ? " can't drive";
        }
    }
}
```

the `access` keyword allows the interpreter to change entry points within the program and call in the order of declaration.

```console
Pedro can drive
```

### Memory

The core language is an unmanaged language so all memory management is up to the programmer, for that the core allows accessing the heep and stack through the root layer and controlling the memory management.

### Clusters and interop

Creating and grouping clusters and individual and multitasking processes, allowing interoperability between processes of different natures, allows the program to manage different isolated or shared contexts.

### Philosophy

Nucleo means inner/core and a language focused on processes and the transport of data between processes through pipes. in the cluster section we will show how to send and receive data across clusters and have several clusters processing different data.

## Variables, types, Constant

In nucleo variable declarations are by inference but it is possible to define a variable type to make visible in certain scopes and make private, restricted, global and permanent data.
Variable declaration with inference

```csharp
age = 23                                    // int or unsigned int
Balance = 1280.30                           // float or double
type = 'A'                                  // Char
name = "Jonh"                               // String
enabled = true                              // Boolean
io = 0b00001111                             // Byte

// Constants readonly

AGE = 23                                    // int or unsigned int
BALANCE = 1280.30                           // float or double
TYPE = 'A'                                  // Char
NAME = "Jonh"                               // String
ENABLED = true                              // Boolean
IO = 0b00001111                             // Byte

// Array, Vector, and Matrix

promote ages to [5] = [18, 14, 16, 25, 20]  // Array definition
ages[2] = 12                                // Array Assign
b = ages[0]                                 // Array Use value of 18
                                            
promote position to [2] int                 // Vector definition
position.push_back(2)                       // Vector add position [0, 1, *2*]
position[2] = 11                            // Vector index [2] value of 11

promote transform to [3][3] = float         // Matrix definition of float
transform[2][0] = 11.0                      //    0      0    *11.0* [2][0]
transform[2][0] = 21.5                      //    0    *21.5*   0    [1][1]
transform[2][0] = 13.1                      //  *13.1*   0      0    [0][2]

// Object

data = { position: {x: 0, y: 2},  name: "Cursor" }      // Object Definition
data.position.x = 2                                     // Object Assing
x = data.name                                           // Object use

```

### Arithmetic, Boolean and memory operators

| Symbol | Opeator  | Type  |
-------- | -------  |------ |
| +      | Add      | Math  |
| -      | Sub      | Math  |
| *      | Mul      | Math  |
| /      | Div      | Math  |
| %      | Mod      | Math  |
| ^      | Pow      | Math  |
| +=     | Increment      | Math  |
| -=     | Decrement      | Math  |
| ++     | Increment      | Math  |
| --     | Decrement      | Math  |
| ==     | Equal      | Boolean  |
| >      | Greater      | Boolean  |
| <      | Greater      | Boolean  |
| >=     | Greater than or equal to  | Boolean  |
| >=     | Less than or equal to  | Boolean  |
| !      | Not  | Boolean  |
| !=     | NotEqual  | Boolean  |
| &&     | And  | Boolean  |
| //     | Or  | Boolean  |
| /^     | Xor  | Boolean  |
| /<     | Pipe Out  | Pipe  |
| />     | Pipe In  | Pipe  |
| &      | Memory Reader     | Memory  |
| #      | Memory Writer     | Memory  |
| @%     | Malloc     | Memory  |
| #%     | Free     | Memory  |

Typed variable declaration

```csharp
string name = "Jonh"
int idade = 23
```

In the nucleo, assignment is done using the `=` sign.
It is not allowed to change the type of a variable using assignment. Instead, a `modifier` must be invoked in `promote` to perform the substitution, or `casting` to convert the value with lossy data changes.

```csharp
name = "Jonh"
name = 23
```
:computer: console output

```console
type error when assigning an <int> value to <string>
```

Using the `casting` modifier

```csharp
name = "Jonh"
name = string(23)    // Using Casting for convert int in string with loss
console out name     // Print in console output
```

> :warning: ***Changing the integer value 23 will convert it to a string "23"***

:computer: console output
```console
23
```

### Modifiers, keywords, access levels

So that the core interpreter knows how to manage the data some words are used to allow the programmer to switch types create functions at runtime and define the range of variables between layers and the program as a whole.

### Modifier

Modifiers are special structures that change runtime variables, functions and classes. the promote modifier promotes or alters a variable by creating one with the same name and assigning a new value once this data has been promoted all parts of the code using it will get the new value a runtime error will be created if any cause some unexpected error.
promote should be used when a variable is of type collected when a class is generated through several variables and functions following an example of promote using variables and functions and having the data collected next.

```csharp
private name = "Pedro"
private age = 18
private phone = 12345678
private creditcard = false

public getName(return Name)
public getAge(return age)

promote [name, age, phone, creditcard, getName, getAge] to class(Person)

Person client()

console out client.getName + bkln
console out client.getAge + bkln
```
:computer: console output

```console
Pedro
18
```

### Usage of operators
The use of operators is an essential part of language and numerical expressions as well, so nucleus addresses their use in a simple way.

```csharp
result = (((2+2) * (14/3) + 12) + 3) * PI           // Order of precedence result: ~105.713
max = 2^16                                          // 65.536

```
#### Global indicator
Variables are limited to the scope of the file; multiple files can have unique variables with the same names. The compiler generates a unique name according to the file, and the naming does not influence the memory allocation by the compiler. However, if the programmer needs a global scope variable that can persist throughout the application, a special `global` modifier is placed. It can call and assign values ​​depending on the management, but only a single assignment, and the name is reserved for it. A compilation error is generated if another variable with the same name exists.
```csharp
//Variable
name = "Jose"               //Access only in scope
global name = "Andre"       //Scope of all application
```

#### Pointers and memory management
The Nucleo addresses statistical data, copies, and references in order to organize the elements and data manipulation.
```csharp
//Class Example for Automatic Allocator
promote book of BookClass

//Memory manual Allocator
book @% BookClass
//Memory manual Free
#% book

// or
// Exemplo prático dos operadores de memória
ptr = @% sizeof(int)        // Malloc: aloca memória
#ptr = 42                  // MemoryWrite: escreve na memória
value = &ptr               // MemoryRead: lê da memória
#% ptr                     // Free: libera memória     
```

### Pipe operator
Pipe Operators allow communication between processes of the same application or through interoperability

#### Pipe usage
To allow communication between pipes, it is necessary to create a pipe in both processes using promote <pipe-name> of pipe and send or receive using the pipe operators `|> input` and `|< output`
````csharp
// Example of interprocess pipes     
process1 |> data           // PipeIn: recebe dados do processo
process2 |< result         // PipeOut: envia dados para o processo
````
***CPU Process***
````csharp
// process managed by the CPU
{...}
promote texturePipe of pipe                  //Enable Pipe
newTexture.setResolution(1024, 1024)
texturePipe |< newTexture                   //Pipe Output

````
***GPU Process***
````csharp
// GPU process
[GPU]
{...}
promote cpuTexture of pipe                  //Enable Pipe
texturePipe |> textureOutput                //Pipe Input   
````
>:question: [GPU] identifiers point to only the GPU managing the calculations and returning through the pipe, direct GPU management requires specific drivers

### Function
the promote keyword creates functions normally being promote <function> <()> to create a struct the usage changes because the representation changes classes use curly braces `{constructor, copy variables }` after the function name parentheses `( )` arrays square brackets `[10]` vectors and matrices two sets of square brackets `[6],[6]`

There are several ways to create functions with promote. One of them is the fastest way: promote foo() and then the code block isolated by curly braces.

#### Functions Definition

```csharp
// <modifier> <name-function> (arguments or void) { codeblock }
// or
// <modifier> [copy variables] <name-function> (arguments or void) { codeblock }
promote foo() {/* ... */}
promote foo(a, b) {/* ... */}
promote [a, b] foo(c, d) {/* ... */}
```

```csharp 
// Definition
promote foo(){
    console out 2+2
}

// Definition with Local variables
name = "George"                 //File scope
promote foo(){
    local name = "Lucas"        //Access only in scope
    console out name
}

// Definition with arguments and return 
promote foo(a, b){
    return a + b
}

//Definition with copy and arguments
a = 5
b = 10
name = "Nicolas"
alias = "Rivers"
```
the use of copies of variables copies the type and the assigned value and automatically imports them into the function, the use of copies of variables is followed by the name `promote [copy1, copy2, copy3] name( )`

```csharp
promote [a, b, name, alias] in foo(mul){
    console out "Multiply " + string((a + b) * mul) + " " + name + " known as " + alias
}

```
Modify the value of the variable using only the memory address value the `&` operator obtains the address and when edited changes the value directly of the variable

```csharp
//Definition with reference 
a = 2
b = 2
promote foo(&a, &b){
    a = 10, b = 10          // Set the value of the variable using the address as a reference
}

// Call
foo()          // 4
foo()          // Lucas
foo(5+5)       // 10
foo(2)         // Multiply Nicolas knows as Rivers 
foo(a, b)      // change value of 2 and 2 to 10 and 10

```
### Struct
The definition of a struct has a different approach in this case the use of the `to` indicator, the struct keyword followed by the code block, to create an instance instead of `to` using `of`.

#### Struct definition
```csharp
// <modifier> <class-name> <indicator> {codeblock}
//
promote foo to struct {/* ... */} 
promote obj of foo //Instance of foo

```

em C/C++
```cpp
struct Vector2
{
    x = 0;
    y = 0;
};
Vector2* foo = new Vector2();
foo.x = 1;
```

em Nucleo
```csharp
promote Vector2 to struct
{
    x = 0;
    y = 0;
}
promote foo of Vector2
foo.x = 1;
```
more uses
````csharp
promote foo to struct
{
    x = 1
    y = 2
    z = 3
    add(){
        x + 1
        y + 1
        z + 1
    }
}

foo.x = 2
foo.add()
````

### Class
The definition of a class can be done in several ways

#### Class definition
```csharp
// <modifier> <class-name> <indicator> {codeblock}
//
promote Object to class {/* ... */} 
promote obj to Object {/* ... */}   //Heritage
promote o of obj {/* ... */}        //Instance of obj
```
#### Class Usage

````csharp
promote Person to class
{
    public ID = UniqueUID()                     
    public name {get}                           
    public age {get, set}               
    public balance = {get, set}
    private international = false
    protected secureCode = 120
    constructor(name, age, balance){
        this.name = name
        this.age = age
        this.balance = balance
    }
    public checkAge()
    {
        if(age >= 18)
            return true 
        return false
    }
}

// Create instance of Object
promote client of Person("Marcos", 27, 150.00)
name = client.getName()     // Return Marcos
client.setName("Angelica")  // Error trying to assign read-only 

client.age = 18             // attribution allowed but not indicated
client.setAge(18)           // Correct Attribution
age = client.age            // allowed but not indicated
age = client.getAge()       // Correct obtaining

isPermited = client.checkAge()
````

#### Access Modifiers
Access modifiers limit access to members of a class to that class only, limited to inheritors, or global access
````csharp
// Clearer examples of public/private/protected
{...} // Class
public name = "John"                // Global access
private secret = 123                // Access only within scope
protected code = "abc"              // Access for inheritance
````
#### Get Setters

````csharp
public adress {get} = "Unknow"      // Global access reads only externally but allows internal modification
adress = client.getAdress()         // A member is automatically created when assigning get and set
public creditCard {get, set} = 1234 // Acesso global

````