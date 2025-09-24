// Teste completo das estruturas de controle Nucleo Lang

// Variáveis básicas
local x = 10
global y = 20

// If-else statement
if (x > 5) {
    local result = "x é maior que 5"
} else {
    local result = "x é menor ou igual a 5"
}

// If sem else
if (y == 20) {
    local message = "y é igual a 20"
}

// While loop
local counter = 0
while (counter < 5) {
    counter = counter + 1
}

// Do-while loop
local doCounter = 0
do {
    doCounter = doCounter + 1
} while (doCounter < 3)

// Switch statement
local day = 3
switch (day) {
    case 1:
        local dayName = "Segunda"
    case 2:
        local dayName = "Terça" 
    case 3:
        local dayName = "Quarta"
    default:
        local dayName = "Dia inválido"
}

// Expressões aninhadas
if (x > 0 && y < 30) {
    local complex = (x + y) * 2
    if (complex > 50) {
        local nested = "complex é maior que 50"
    }
}

// Operadores diversos
local a = 10 + 5 * 2
local b = (10 + 5) * 2
local c = !true
local d = -x