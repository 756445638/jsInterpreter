

var MKHuman = function(age,name){
	this.age = age;
	this.name = name;
	this.sayHai = function(aa,bb){
		console.log("I am " + this.name + ", I am " + this.age + " years old");
	}
	return this;
}

var lily = MKHuman(18,"lily");


lily.sayHai();

var yuyang = {name:"yuyang","age":22};















