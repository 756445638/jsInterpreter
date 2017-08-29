

var animal = {};
animal.desp = "I am a animal";
animal.howl = function(){
	console.log("Woo Woo!!!!!!!!!!!!!!!!!");
}

function MKHuman(name,age){
	this.name= name;
	this.age = age;
	function xxx(){
		console.log("xxxxxxxxxxxxxx");
	}
	this.sayHai = function(){
		console.log("Mine name is " + this.name + ", I am " + this.age + " years old!!!!!!!!!!!!!!");
		for(var i = 0;i<this.address.length;i++){
			console.log("Mine " + (i + 1) + "st address is " + this.address[i]);
		}
		xxx();
	}
	this.prototype = animal;
	return this;
}



var lily = MKHuman("lily",18);

lily.address = ["shanghai","chengdu"];

lily.sayHai();

lily.howl();


for(i in (var arr = new Array(1,2,3)))
{
var a = 0;
console.log(arr[++a]);
}







