
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



lily = MKHuman("lily",18);

lily.address = ["shanghai","chengdu"];


lily.sayHai();

lily.howl();

var push = function(arr){
	for(var i = 0;i<10;i++){
		arr.push(i);
	}
	return  arr;
}

var arr = push(new Array());
arr.push(lily);

arr[arr.length-1].address.pop();
arr[arr.length-1].sayHai();

/*

	cccccccccccccccccccc


*/



console.log(!0);


