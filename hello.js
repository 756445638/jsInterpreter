
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

var push = function(arr){
	for(var i = 0;i<10;i++){
		arr.push(i);
	}
	return  arr;
}

var arr = push(new Array());

arr.push(lily);

console.log(arr);

arr[arr.length-1].address.pop();
arr[arr.length-1].sayHai();

/*

	cccccccccccccccccccc


*/



console.log(!0);

lily =123;

if(var a = 1){
	console.log(typeof a);
}


var p = function(abc){
	switch(abc){
		case 0:
		console.log("case 0");
		//break;
		case 1:
		console.log("case 1");
		break;
		default:
			console.log("no 0 no 1");
	}
}

p(0);




