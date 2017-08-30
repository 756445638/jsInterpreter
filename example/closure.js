

var make = function(a){
	switch(a){
		case 1:
			var v = "case number 1";
			return function(){
				console.log(v);
			}
		case 2:
			var v = "case number 2";
			return function(){
				console.log(v);
			}
		case "hello world":
			return function(){
				console.log("case hello world");
			}
	default:
		return function(){
				console.log("no case match");
			}
	}
}

var m = make(1);
m();

m = make(2);
m();

m = make("hello world");
m();
m = make(123);

m();