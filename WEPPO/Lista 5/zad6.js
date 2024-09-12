var fs=require("fs");
var rl=require("readline");
var filePath="zad6.log";
var readStream=rl.createInterface({
    input: fs.createReadStream(filePath)
});

const ipCounts = new Map();

readStream.on('line',function(line){
    const parts=line.split(' ');
    const clientIP = parts[1];
    if(ipCounts.has(clientIP)) 
    {
        ipCounts.set(clientIP,ipCounts.get(clientIP)+1);
    } 
    else 
    {
        ipCounts.set(clientIP, 1);
    }
});

readStream.on('close', () => {
    const sortedIPs=Array.from(ipCounts.entries()).sort((a,b)=>b[1]-a[1]).slice(0,3);
    for(const [ip,count] of sortedIPs) 
    {
        console.log(`${ip} ${count}`);
    }
});