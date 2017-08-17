

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


lily.age += 10;

lily.sayHai();
lily.age -= 10;


lily.sayHai();


console.log(typeof lily);













