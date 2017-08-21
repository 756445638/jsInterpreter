

var MKHuman = function(age,name){
	this.age = age;
	this.name = name;
	this.sayHai = function(){
		console.log("my name is " + this.name + ", I am " + this.age + " years old");
		return 123;
		for(var i in this.address){
			console.log("My " + (i + 1)+ "st address is " + this.address[i]);
		}
	}
	return this;
}

var lily = MKHuman(18,"lily");


lily.address = new Array("shanghai","log angels");

console.log(lily.sayHai());



var animal = {};
animal.howl = function(){
	console.log("Woo Woo!!");
}





lily.prototype = animal;


lily.howl();






var bubbleSort = function(arr){
	for(var i=0;i<arr.length-1;i++){
		for(var j=i+1;j<arr.length;j++){
			if(arr[i]>arr[j]){
				var temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	} 
	return arr;
}




var arr = bubbleSort(new Array(1,100,43,432,6,21,574,112));
console.log(arr);




























