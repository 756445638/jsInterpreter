
function string(){
	arr = new Array();
	for(var i = 0;i<30000;i++){
		arr.push(i + "st");
	}
}
for(var i =0;i<1;i){
	string();
	for(var i in arr){
		console.log(arr[i]);
	}
}
	







