"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
//bez zmian
const Endpoints = {
    ELIXIRS: "Elixirs",
    SPELLS: "Spells",
};
//typy dla tablic elixirs i spells
let elixirs = [];
let spells = [];
//otypowanie valid option
let validOption;
//bez zmian
const gameContainer = document.getElementById("game");
//dodajemy typ do zmiennej endpoint, zwracamy tablicę zgodnie z typem
function fetchData(endpoint) {
    return __awaiter(this, void 0, void 0, function* () {
        const response = yield fetch(`https://wizard-world-api.herokuapp.com/${endpoint}`);
        if (!response.ok) {
            throw new Error("Fetching error");
        }
        const data = yield response.json();
        return data;
    });
}
//sprawdzamy, czy działa
//const e = fetchData<Elixir>(Endpoints.ELIXIRS);
//console.log(e);
//fetchAllData za pomocą fetchData
//czemu dobre? bo zamiast wielu fetch mamy jeden promise
//ponadto znamy strukturę pobieranych danych i mamy większą kontrolę nad typami
function fetchAllData() {
    return __awaiter(this, void 0, void 0, function* () {
        const [e, s] = yield Promise.all([
            fetchData(Endpoints.ELIXIRS),
            fetchData(Endpoints.SPELLS),
        ]);
        //type guard, jeśli funkcja zwróci true to elixir jest zmienną typu Elixir
        elixirs = e.filter((elixir) => Boolean(elixir.effect));
        //type guard, analogicznie z typem Spell
        spells = s.filter((spell) => Boolean(spell.incantation));
    });
}
//otypowanie getRandomElements, generyczna tablica i indexes jako set numberów
function getRandomElements(array, count) {
    const indexes = new Set();
    while (indexes.size < count) {
        indexes.add(Math.floor(Math.random() * array.length));
    }
    return [...indexes].map(i => array[i]);
}
//analogicznie typujemy generateOptions
function generateOptions(randomElements) {
    const [rightOption, ...rest] = randomElements;
    const options = [rightOption, ...rest].sort(() => Math.random() > 0.5 ? 1 : -1);
    return {
        rightOption,
        options,
    };
}
function elixirGame() {
    const { options, rightOption } = generateOptions(getRandomElements(elixirs, 3));
    validOption = rightOption.name;
    console.log(`Cheat Mode: Right answer is ${validOption}`);
    renderOptions(`Which elixir effect is: "${rightOption.effect}"?`, options.map((elixir) => elixir.name));
}
function spellGame() {
    const { options, rightOption } = generateOptions(getRandomElements(spells, 3));
    validOption = rightOption.name;
    console.log(`Cheat Mode: Right answer is ${validOption}`);
    renderOptions(`Which spell incantation is: "${rightOption.incantation}"?`, options.map((spell) => spell.name));
}
function renderOptions(question, answers) {
    const questionElement = document.getElementById("question");
    gameContainer.innerHTML = "";
    questionElement.textContent = question;
    answers.forEach((answer) => {
        const option = document.createElement("button");
        option.textContent = answer;
        gameContainer.appendChild(option);
    });
}
//problemy:
//gamecontainter zakładamy że istnieje
//event.target musi mieć sprawdzony typ
//w fetchData<T> T wymusza zgodność z API
gameContainer.addEventListener("click", (event) => {
    if (event.target instanceof HTMLButtonElement) {
        const selectedOption = event.target.textContent;
        if (selectedOption === validOption) {
            round();
        }
        else {
            alert("Wrong answer!");
        }
    }
});
function round() {
    const randomGame = Math.random() > 0.5 ? elixirGame : spellGame;
    randomGame();
}
function startGame() {
    return __awaiter(this, void 0, void 0, function* () {
        yield fetchAllData();
        round();
    });
}
startGame();
