var fs=require("fs");

//wersja z callbackiem
fs.readFile("zad7.txt","utf8",function(err,data){
    if(err)
    {
        console.error(err);
        return;
    }
    console.log(data);
});

//wersja z Promise
function fs_with_promise()
{
    return new Promise(function(resolve,reject){
        fs.readFile("zad7.txt","utf8",function(err,data){
            if(err)
            {
                reject(err);
            }
            resolve(data);
        });
    });
}

fs_with_promise()
    .then(function(data){
        console.log(data);
    })
    .catch(function(err){
        console.error(err);
    });

//wersja util.promisify
var util=require("util");
var utilReader=util.promisify(fs.readFile)

utilReader("zad7.txt","utf8")
    .then(function(data){
        console.log(data);
    })
    .catch(function(err){
        console.error(err);
    });

//wersja fs.promises
async function fs_promises()
{
    try
    {
        var data=await fs.promises.readFile("zad7.txt","utf8")
        console.log(data);
    }
    catch(err)
    {
        console.log(err);
    }
}

fs_promises();

