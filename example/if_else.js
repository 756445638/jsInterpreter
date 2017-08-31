
var grades = new Array();

grades.push(
{
	name:"john",
	"course":"cs",
	eval:99
}
);

grades.push(
{
	name:"john",
	"course":"math",
	eval:50
}
);



grades.push(
{
	name:"lily",
	"course":"cs",
	eval:80
}
);

grades.push(
{
	name:"lily",
	"course":"math",
	eval:95
}
);


grades.push({
	name:"jack",
	"course":"cs",
	eval:40
});


function eval_grade(grades){
	for(var i = 0;i<grades.length;i++){
		var c = grades[i];
		if(c.eval > 80){
			console.log(c.name + " got A at " + c.course);
		}else if(c.eval > 60){
			console.log(c.name + " got B at " + c.course);
		}else{
			console.log(c.name + " fail at " + c.course);
		}
	}
}


eval_grade(grades);





for(;arr[i];){

	
}