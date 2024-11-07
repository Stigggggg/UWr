var http=require("http");
var express=require("express");
var app=express();

app.set("view engine","ejs");
app.set("views","./views");
app.get("/download",(req,res)=>{
    var dane="123";
    res.setHeader("Content-disposition","attachment; filename=plik.txt");
    res.end(dane);
});

http.createServer(app).listen(3000);
console.log("started");