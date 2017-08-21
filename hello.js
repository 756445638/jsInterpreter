

var MKHuman = function(age,name){
	this.age = age;
	this.name = name;
	this.sayHai = function(){
		console.log("my name is " + this.name + ", I am " + this.age + " years old");
		for(var i in this.address){
			console.log("My " + (i + 1)+ "st address is " + this.address[i]);
		}
	}
	return this;
}

var lily = MKHuman(18,"lily");


lily.address = ["shanghai","log angels"];

console.log(lily.address);

lily.sayHai();




var animal = {};
animal.howl = function(){
	console.log("Woo Woo!!");
}































