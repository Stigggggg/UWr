var fs=require("fs");

fs.readFile("zad4.txt","utf8",function(err,plik){
    if(err)
    {
        console.error(err);
        return;
    }
    console.log(plik);
});