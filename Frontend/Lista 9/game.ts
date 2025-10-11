//bez zmian
const Endpoints = {
    ELIXIRS: "Elixirs",
    SPELLS: "Spells",
} as const;

//wprowadzenie EndpointType reprezentującego dane
//czemu to dobre? bo się automatycznie aktualizuje jak zmienimy Endpoints (np. dopiszemy coś)
type EndpointType = typeof Endpoints[keyof typeof Endpoints];

//otypowanie eliksirów i zaklęć zgodnie z API
type Elixir = {
    id: string;
    name: string;
    effect: string;
    sideEffects: string;
    characteristics: string;
    time: string;
    difficulty: string;
    ingredients: { id: string; name: string }[];
    inventors: { id: string; firstName: string; lastName: string }[];
    manufacturer: string;
  };
  
  type Spell = {
    id: string;
    name: string;
    incantation: string;
    effect: string;
    canBeVerbal: boolean;
    type: string;
    light: string;
    creator: string;
  };

//typy dla tablic elixirs i spells
let elixirs: Elixir[] = [];
let spells: Spell[] = [];

//otypowanie valid option
let validOption: string;

//bez zmian
const gameContainer = document.getElementById("game")!;

//dodajemy typ do zmiennej endpoint, zwracamy tablicę zgodnie z typem
async function fetchData<T>(endpoint: EndpointType): Promise<T[]> {
    const response = await fetch(`https://wizard-world-api.herokuapp.com/${endpoint}`);
    if (!response.ok) {
        throw new Error("Fetching error");
    }
    const data = await response.json();
    return data as T[];
}

//sprawdzamy, czy działa
//const e = fetchData<Elixir>(Endpoints.ELIXIRS);
//console.log(e);

//fetchAllData za pomocą fetchData
//czemu dobre? bo zamiast wielu fetch mamy jeden promise
//ponadto znamy strukturę pobieranych danych i mamy większą kontrolę nad typami
async function fetchAllData(): Promise<void> {
    const [e, s] = await Promise.all([
        fetchData<Elixir>(Endpoints.ELIXIRS),
        fetchData<Spell>(Endpoints.SPELLS),
    ]);
    //type guard, jeśli funkcja zwróci true to elixir jest zmienną typu Elixir
    elixirs = e.filter((elixir): elixir is Elixir => Boolean(elixir.effect));
    //type guard, analogicznie z typem Spell
    spells = s.filter((spell): spell is Spell => Boolean(spell.incantation));
}

//otypowanie getRandomElements, generyczna tablica i indexes jako set numberów
function getRandomElements<T>(array: T[], count: number): T[] {
    const indexes: Set<number> = new Set();
    while (indexes.size < count) {
        indexes.add(Math.floor(Math.random() * array.length));
    }
    return [...indexes].map(i => array[i]);
}

//analogicznie typujemy generateOptions
function generateOptions<T>(randomElements: T[]) {
    const [rightOption, ...rest] = randomElements;
    const options = [rightOption, ...rest].sort(() =>
        Math.random() > 0.5 ? 1 : -1
    );
    return {
        rightOption,
        options,
    };
}

function elixirGame(): void {
    const { options, rightOption } = generateOptions(getRandomElements(elixirs, 3));
    validOption = rightOption.name;
    console.log(`Cheat Mode: Right answer is ${validOption}`);
    renderOptions(`Which elixir effect is: "${rightOption.effect}"?`, options.map((elixir) => elixir.name));
}

function spellGame(): void {
    const { options, rightOption } = generateOptions(
        getRandomElements(spells, 3)
    );
    validOption = rightOption.name;
    console.log(`Cheat Mode: Right answer is ${validOption}`);
    renderOptions(`Which spell incantation is: "${rightOption.incantation}"?`, options.map((spell) => spell.name));
}

function renderOptions(question: string, answers: string[]): void {
    const questionElement = document.getElementById("question")!;
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
gameContainer.addEventListener("click", (event: MouseEvent): void => {
        if (event.target instanceof HTMLButtonElement) {
            const selectedOption = event.target.textContent!;
            if (selectedOption === validOption) {
                round();
            } else {
                alert("Wrong answer!");
            }
        }
    }
);

function round(): void {
    const randomGame = Math.random() > 0.5 ? elixirGame : spellGame;
    randomGame();
}

async function startGame(): Promise<void> {
    await fetchAllData();
    round();
}

startGame();