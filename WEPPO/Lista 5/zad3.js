var readline=require("readline");
var rl=readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

var liczba=Math.floor(Math.random()*101);

function zgadnij()
{
    rl.question("Wybierz liczbę od 0 do 100 ",(answer)=>{
        var x=parseInt(answer);
        if(x==liczba)
        {
            console.log("Zgadłeś");
            rl.close();
        }
        else if(x<liczba)
        {
            console.log("Twoja liczba jest za mała.");
            zgadnij();
        }
        else
        {
            console.log("Twoja liczba jest za duża");
            zgadnij();
        }
    });
}

zgadnij();