

var animal = {};
animal.desp = "I am a animal";
animal.howl = function(){
	console.log("Woo Woo!!!!!!!!!!!!!!!!!");
}

function MKHuman(name,age){
	this.name= name;
	this.age = age;
	this.sayHai = function(){
		console.log("Mine name is " + this.name + ", I am " + this.age + " years old!!!!!!!!!!!!!!");
		for(var i = 0;i<this.address.length;i++){
			console.log("Mine " + (i + 1) + "st address is " + this.address[i]);
		}
	}
	this.prototype = animal;
	return this;
}



var lily = MKHuman("lily",18);

lily.address = ["shanghai","chengdu"];

lily.sayHai();

lily.howl();
