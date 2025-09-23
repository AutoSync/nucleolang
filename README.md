# Nucleo Programming Language

![version](https://img.shields.io/badge/version-V.010.0%2F2025-blue)

Nucleo é uma linguagem de alto nível projetada para operar próximo ao nível de hardware, permitindo acesso direto à memória e ao processamento através de **clusters** que enviam e recebem dados.  
Seu design separa a interface do processamento de dados, oferecendo flexibilidade para aplicações de baixo e alto nível.

---

## ✨ Características principais
- Sintaxe simples, inspirada em **C#** e **C++**
- Entrada padrão implícita em camadas (`matrix`, `root`, `main`)
- **Inferência de tipos** com suporte a declaração explícita
- Gerenciamento de memória **manual** e **automático**
- Suporte a **Arrays, Vetores, Matrizes e Objetos**
- Sistema de **Classes** e **Structs**
- Comunicação entre processos via **Pipes**
- Controle de acesso com `public`, `private`, `protected`
- Extensão de arquivos:
  - `.nu` → código principal
  - `.nh` → cabeçalhos

---

## 🚀 Exemplo: Hello World

```csharp
console out "Hello World!"
```

Saída:
```console
Hello World!
```

---

## 📂 Estrutura de Programa

Um programa em Nucleo é composto por três camadas principais:

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

Saída:
```console
Pedro can drive
```

---

## 🔣 Tipos e Variáveis

### Inferência de tipos
```csharp
age = 23            // int
balance = 1280.30   // float
name = "John"       // string
enabled = true      // boolean
```

### Constantes (somente leitura)
```csharp
AGE = 23
NAME = "Pedro"
```

### Tipagem explícita
```csharp
string name = "John"
int idade = 23
```

---

## 📊 Estruturas de Dados

### Arrays
```csharp
promote ages to [5] = [18, 14, 16, 25, 20]
```

### Vetores
```csharp
promote position to [2] int
position.push_back(2)
```

### Matrizes
```csharp
promote transform to [3][3] = float
transform[2][0] = 11.0
```

### Objetos
```csharp
data = { position: {x: 0, y: 2}, name: "Cursor" }
name = data.name
posX = data.position.x
posX = data.position.y
```

---

## 🧮 Operadores

- **Aritméticos:** `+ - * / % ^ ++ -- += -=`  
- **Booleanos:** `== != > < >= <= ! && || /^`  
- **Memória:** `& # @% #%`  
- **Pipes:** `|< |>`  

---

## 🛠️ Funções

```csharp
promote foo(a, b){
    return a + b
}
```

Com cópia de variáveis:
```csharp
a = 2, b = 5
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

## 🏗️ Structs

```csharp
promote Vector2 to struct {
    x = 0
    y = 0
}
promote foo of Vector2
foo.x = 1
```

---

## 🧑‍💻 Classes

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

## 🔄 Pipes (Interprocess Communication)

```csharp
promote pipeName of pipe
process1 |< data
process2 |> result
```

---

## 💾 Gerenciamento de Memória

```csharp
ptr = @% sizeof(int)   // aloca memória
#ptr = 42              // escreve na memória
value = &ptr           // lê da memória
#% ptr                 // libera memória
```

---

## 📜 Filosofia

O nome **Nucleo** representa o "núcleo" da computação: foco em **processos** e no **transporte de dados entre processos** através de pipes.  
Com suporte a **clusters independentes** [`WIP`], a linguagem possibilita execução paralela e modular de diferentes contextos.

---

## 📌 Status

⚠️ **Nucleo está em fase experimental**.  
Mudanças de sintaxe e recursos podem ocorrer.

---

## 📖 Contribuindo

Contribuições são bem-vindas!  
Siga os passos:
1. Faça um fork do repositório
2. Crie uma branch (`git checkout -b feature/minha-feature`)
3. Commit suas mudanças (`git commit -m 'Adiciona minha feature'`)
4. Faça um push (`git push origin feature/minha-feature`)
5. Abra um Pull Request 🚀

---

## 📄 Licença

Distribuído sob a licença **EULA - Nucleo Compiler**.  
Consulte o arquivo `LICENSE` para mais detalhes.
