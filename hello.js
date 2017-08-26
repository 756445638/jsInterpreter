

var animal = {};
animal.desp = "I am a animal";
animal.howl = function(){
	console.log("Woo Woo!!!!!!!!!!!!!!!!!");
}

function MKHuman(name,age){
	console.log(typeof age);
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
	console.log(typeof abc);
}

p(false);









function bubbleSort(arr) {
    var len = arr.length;
    for (var i = 0; i < len; i++) {
        for (var j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {        // 相邻元素两两对比
                var temp = arr[j+1];        // 元素交换
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return arr;
}

console.log(bubbleSort(new Array(15,152,45,78112,458,12,33,3231,3231,13354,122)));




for(var i = 0;i<10;i++){
	var vvv = 123;
	console.log(vvv);
}
