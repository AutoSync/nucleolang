// Variable
name = "Ana" 	
age = 30


// Pipers
// B is a variable from another process
a |> b
		
// Class Creation
promote foo in Class{
a = 5
b = 5
c = foo.a + foo.b
}


//Function Creation
promote muu in function (a, b){
return a + b
}

//Imprime na tela o resultado 10
console out muu(5+5)

//Envia para fora do processo o valor 10
pipe out muu(5+5)
