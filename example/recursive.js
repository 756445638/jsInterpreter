
var arr = [1,2,3,4,5];
var m = arr.length;
var n = 2;

var deepCopyArr = function(arr){
	var res = [];
	for(var i = 0;i < arr.length;i++){
		res.push(arr[i]);
	}
	return res;
}


var selectMFromN = function(arr,history,index,m,n,res){
	if(n == 0){
		res.push(history);
		return ;
	}
	if(index >= m){
		return ;
	}
	var h1 = deepCopyArr(history);
	h1.push(arr[index]);
	selectMFromN(arr,h1,index + 1,m,n-1,res);
	var h2 = deepCopyArr(history);
	selectMFromN(arr,h2,index + 1,m,n,res);
}

var result = new Array();
selectMFromN(arr,[],0,m,n,result);

console.log("select " + n +" from "+m+" have " + result.length + " possibilities,which are:");

for(var i in result){
	console.log(result[i]);
}
	










