var http=require("http");
var express=require("express");
var app=express();
var session=require("express-session")
var filestore=require("session-file-store")(session);

app.use(session({
    store: new filestore(),
    secret: "key",
    resave: false,
    saveUninitialized: false,
    cookie: {maxAge: 3600000, secure: false, httpOnly: true}
}));

app.get("/",(req,res)=>{
    req.session.username="MD";
    var username=req.session.username;
    res.send(`Witaj ${username}`);
    // delete req.session.username;
    // res.send(`Witaj ${username}`);
});

http.createServer(app).listen(3000);
console.log("started");