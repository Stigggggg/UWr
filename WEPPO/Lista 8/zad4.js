var http=require("http");
var express=require("express");
var app=express();
var cookieParser=require("cookie-parser")

app.set("view engine","ejs");
app.set("views","./views");
app.use(express.urlencoded({extended: true}));
app.use(cookieParser());
app.use("/",(req,res)=>{
    var cookieValue="12";
    if(!req.cookies.cookie)
    {
        cookieValue="1233";
        res.cookie("cookie",cookieValue);
    }
    else
    {
        cookieValue=req.cookies.cookie;
        res.cookie("cookie",cookieValue,{maxAge: -1});
    }
    res.render("index",{cookieValue: cookieValue});
});

http.createServer(app).listen(3000);
console.log("started");