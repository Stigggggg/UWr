var readline=require("readline");
var rl=readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
rl.question("Jak masz na imię? ", (answer)=>{
    console.log(`Witaj ${answer}`);
    rl.close();
});