# 📘 Especificação da Linguagem Nucleo

## 1. Arquivos de Código
- Arquivos de implementação: **`.nu`**  
- Arquivos de cabeçalho: **`.nh`**

## 2. Estrutura de Programa

### 2.1. Entrada padrão
Um programa Nucleo possui um ponto de entrada implícito `main`, organizado em camadas hierárquicas:

```ebnf
Program  ::= MatrixLayer
MatrixLayer ::= "access" "matrix" "(" ParamList? ")" Block
RootLayer   ::= "access" "root" "(" ParamList? ")" Block
MainLayer   ::= "access" "main" "(" ParamList? ")" Block
Block       ::= "{" Statement* "}"
ParamList   ::= Identifier ("," Identifier)*
```

**Exemplo:**
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

---

## 3. Declaração de Variáveis

### 3.1. Inferência de tipo
```ebnf
VarDecl ::= Identifier "=" Expression ";"
```

**Exemplo:**
```csharp
age = 23            // int
balance = 1280.30   // float
name = "John"       // string
enabled = true      // bool
```

### 3.2. Constantes (CAIXA ALTA)
```ebnf
ConstDecl ::= UPPER_IDENTIFIER "=" Expression ";"
```

**Exemplo:**
```csharp
AGE = 23
NAME = "Pedro"
```

### 3.3. Tipagem explícita
```ebnf
TypedDecl ::= Type Identifier "=" Expression ";"
```

**Exemplo:**
```csharp
string name = "John"
int idade = 23
```

---

## 4. Estruturas de Dados

### 4.1. Arrays
```ebnf
ArrayDecl ::= "promote" Identifier "to" "[" Integer "]" "=" "[" ExpressionList "]"
```

**Exemplo:**
```csharp
promote ages to [5] = [18, 14, 16, 25, 20]
```

### 4.2. Vetores
```csharp
promote position to [2] int
position.push_back(2)
```

### 4.3. Matrizes
```csharp
promote transform to [3][3] = float
transform[2][0] = 11.0
```

### 4.4. Objetos
```csharp
data = { position: {x: 0, y: 2}, name: "Cursor" }
x = data.name
```

---

## 5. Operadores

### 5.1. Aritméticos
`+ - * / % ^ ++ -- += -=`

### 5.2. Booleanos
`== != > < >= <= ! && || /^`

### 5.3. Memória
`& # @% #%`

### 5.4. Pipes
`|< |>`

---

## 6. Modificadores

- `promote` → criação/elevação de variáveis, funções, classes, pipes.  
- `global` → escopo global.  
- `private`, `public`, `protected` → níveis de acesso.  

---

## 7. Funções

```ebnf
FuncDecl ::= "promote" Identifier "(" ParamList? ")" Block
```

**Exemplo:**
```csharp
promote foo(a, b){
    return a + b
}
```

Com cópia de variáveis:
```csharp
promote [a, b] foo(c, d){
    console out a + b + c + d
}
```

Com referência:
```csharp
promote bar(&x, &y){
    x = 10
    y = 20
}
```

---

## 8. Structs

```ebnf
StructDecl ::= "promote" Identifier "to" "struct" Block
Instance    ::= "promote" Identifier "of" Identifier
```

**Exemplo:**
```csharp
promote Vector2 to struct {
    x = 0
    y = 0
}
promote foo of Vector2
foo.x = 1
```

---

## 9. Classes

```ebnf
ClassDecl ::= "promote" Identifier "to" "class" Block
```

**Exemplo:**
```csharp
promote Person to class {
    public name {get, set}
    private age
    constructor(name, age){
        this.name = name
        this.age = age
    }
}
promote client of Person("Marcos", 27)
```

---

## 10. Pipes (Interprocess Communication)

```csharp
promote pipeName of pipe
process1 |< data
process2 |> result
```

---

## 11. Gerenciamento de Memória

```csharp
ptr = @% sizeof(int)   // aloca
#ptr = 42              // escreve
value = &ptr           // lê
#% ptr                 // libera
```
