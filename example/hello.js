

var animal = {};
animal.desp = "I am a animal";
animal.woo = function(){
	console.log("Woo Woo!!!!!!!!!!!!!!!!!");
}
function MKHuman(name,age){
	this.name= name;
	this.age = age;
	var that = this;
	function sayHai(){
		console.log("Hello world!!!! Mine name is " + that.name + ", I am " + that.age + " years old!!!!!!!!!!!!!!");
		for(var i = 0;i<that.address.length;i++){
			console.log("Mine " + (i + 1) + "st address is " + that.address[i]);
		}
	}
	this.sayHai = sayHai;
	this.prototype = animal;
	return this;
}


var lily = MKHuman("lily",18);

lily.address = ["shanghai","chengdu"];

lily.sayHai();

lily.woo();



