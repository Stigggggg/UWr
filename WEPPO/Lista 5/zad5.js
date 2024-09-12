//wersja bez promise
var http=require("https");

// http.get("https://www.google.com",function(resp){
//     var buf="";
//     resp.on("data",function(data){
//         buf+=data.toString();
//     });
//     resp.on("end",function(){
//         console.log(buf);
//     });
// });

//wersja z promise
function get_with_promise(url)
{
    return new Promise(function(resolve,reject){
        http.get(url,function(resp){
            var buf="";
            resp
                .on("data", function(data){
                    buf+=data.toString();
                })
                .on("end",function(){
                    resolve(buf);
                })
                .on("error",function(error){
                    reject(error);
                });
        });
    });
}

get_with_promise("https://www.google.com")
    .then(function(data){
        console.log(data);
    });