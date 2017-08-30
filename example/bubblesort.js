
var sort = function(arr){
	for(var i = 0;i<arr.length-1;i++){
		for(var j=0;j<arr.length-1 -i;j++){
		if(arr[j] > arr[j+1]){
				var tmp = arr[j];
				arr[j] =  arr[j+1];
				arr[j+1] = tmp;
			}	
		}
	}
	return arr;
}
var arr = new Array();
var total = 100;
for(var i = 0;i<100;i++){
	arr.push(100-i);
}

console.log("before sort:");
console.log(arr);
sort(arr);
console.log("after sort:");
console.log(arr);
