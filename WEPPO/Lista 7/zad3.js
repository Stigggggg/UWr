var http=require("http");
var express=require("express");
const session = require("express-session");
var app=express();

app.set("view engine","ejs");
app.set("views","./views");
app.use(express.urlencoded({extended: true}));
app.use(session({
    secret: "abc",
    resave: false,
    saveUninitialized: true
}));

app.get("/",(req,res)=>{
    res.render("form");
});
app.post("/submit",(req,res)=>{
    const {imie,nazwisko,przedmiot,tasks}=req.body;
    if(!imie || !nazwisko || !przedmiot)
    {
        res.render("form",{error: "Należy podać imię, nazwisko i przedmiot"});
        return;
    }
    else
    {
        req.session.dane={imie,nazwisko,przedmiot,tasks};
        res.redirect("/print");
    }
});
app.get("/print",(req,res)=>{
    const dane=req.session.dane;
    if(!dane)
    {
        res.redirect("/");
        return;
    }
    res.render("print",{dane});
});

http.createServer(app).listen(3000);
console.log("started");