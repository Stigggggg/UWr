function createFs(n) 
{ 
    var fs=[]; 
    for(var i=0; i<n; i++) 
    {
        fs[i]=function(){
            return i;
        };
    }
    return fs;
}

function createFs_var(n)
{
    var fs=[];
    for(var i=0; i<n; i++)
    {
        fs[i]=function(j){
            return function(){
                return j;
            };
        }(i);
    }
    return fs;
}

var myfs=createFs(10);
console.log(myfs[0]()); 
console.log(myfs[2]());
console.log(myfs[7]());

var myfs2=createFs_var(10);
console.log(myfs2[0]()); 
console.log(myfs2[2]());
console.log(myfs2[7]());