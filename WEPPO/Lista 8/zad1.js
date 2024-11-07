var http=require("http");
var express=require("express");
var app=express();
var multer=require("multer");
var path=require("path");
var storage=multer.diskStorage({
    destination: (req,file,cb)=>{
        cb(null,"Nowy folder");
    },
    filename: (req,file,cb)=>{
        console.log(file);
        cb(null,Date.now()+path.extname(file.originalname));
    }
});
var upload=multer({storage: storage});

app.set("view engine","ejs");
app.set("views","./views");
app.use(express.urlencoded({extended: true}));
app.get("/",(req,res)=>{
    res.render("upload");
});
app.post("/upload",upload.single("image"),(req,res)=>{
    res.send("Plik przesłany");
});

http.createServer(app).listen(3000);
console.log("started");