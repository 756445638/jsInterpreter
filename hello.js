

var MKHuman = function(age,name){
	this.age = age;
	this.name = name;
	this.sayHai = function(){
		console.log("I am " + this.name + ", I am " + this.age + " years old");
	}
	return this;
}

var lily = MKHuman(18,"lily");


lily.sayHai();

for(var i = 0;i<10;i++){
	console.log("hello world");
}

console.log(i);














