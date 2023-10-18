console.log((![]+[])[+[]]+(![]+[])[+!+[]]+([![]]+[][[]])[+!+[]+[+[]]]+(![]+[])[!+[]+!+[]]);
console.log((![]+[])[+[]]); //f
//[] dla typu Object ewaluuje sie do true, zatem ![] to false
//false+[], binarny operator + konwertuje oba wyrazenia na stringi, zatem mamy "false"
//+[], unarny + powoduje konwersje najpierw ToNumber, potem ToPrimitive, razem mamy [[DefaultValue]], czyli 0
//stad mamy "false"[0], czyli "f"
console.log((![]+[])[+!+[]]); //a
//pierwsza czesc ta sama, wychodzi "false"
//dalej juz ciezej, wiemy ze +[] to 0, !0 to !false czyli true, +true wymusza konwersje ToNumber, co daje 1
//stad mamy "false"[1]
console.log(([![]]+[][[]])[+!+[]+[+[]]]); //i
//po kolei:
//[![]] to !true, czyli [false]
//[][[]] to undefined, po dodaniu "falseundefined"
//[+[]] to [0], +[[0]] daje 0
//!+[] daje true, +!+[] konwertuje na liczbe, wiec mamy 1
//po dodaniu ["10"]
//mamy "falseundefined"[10], czyli i
console.log((![]+[])[!+[]+!+[]]); //l
//znowu !+[] to true, true+true to 1+1=2
//wiec false[2]