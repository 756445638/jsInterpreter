

var MKHuman = function(age,name){
console.log(name);
	this.age = age;
	this.name = name;
	console.log(this.name);
	this.sayHai = function(){
		console.log("my name is " + this.name + ", I am " + this.age + " years old");
		console.log(this.address);
	}
	
	return this;
}

var lily = MKHuman(18,"lily");


lily.address = ["shanghai","log angels"];


lily.sayHai();




var animal = {};
animal.howl = function(){
	console.log("Woo Woo!!");
}































