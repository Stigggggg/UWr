const pokemonListElement = document.getElementById("pokemonList");
const pokemonDetails = document.getElementById("pokemonDetails");
const pokemonName = document.getElementById("pokemonName");
const pokemonImg = document.getElementById("pokemonImg");
const pokemonTypes = document.getElementById("pokemonTypes");
const pokemonStats = document.getElementById("pokemonStats");
const pokemonFlavorText = document.getElementById("pokemonFlavorText");
const loading = document.getElementById("loading");
const errorText = document.getElementById("errorText");

async function preloadImage(src) { //funkcja do ładowania obrazka
    const img = new Image();
    img.src = src;
    await img.decode();
    return img;
}

function showLoading() { //ładowanie
    loading.style.display = "block";
    errorText.style.display = "none";
    pokemonDetails.style.display = "none";
}

function hideLoading() {
    loading.style.display = "none";
}

function showError() { //error
    hideLoading();
    errorText.style.display = "block";
    pokemonDetails.style.display = "none";
}

function clearPokemonList() {
    pokemonListElement.innerHTML = "";
}

async function fetchPokemonList() {
    showLoading();
    try {
      const response = await fetch("https://pokeapi.co/api/v2/pokemon-species?limit=151"); //pobieramy listę 151 pierwszych z API
      const data = await response.json();
      clearPokemonList();
      data.results.forEach(pokemon => {
        const li = document.createElement("li"); //tworzymy element li 
        li.textContent = capitalize(pokemon.name);
        li.addEventListener("click", () => loadPokemonData(pokemon.name));
        pokemonListElement.appendChild(li);
      });
      hideLoading();
    } catch {
      showError();
    }
}

async function loadPokemonData(name) {
    showLoading();
    try {
      const speciesRes = await fetch(`https://pokeapi.co/api/v2/pokemon-species/${name}`); //pobranie danych o pokemonach z endpointu pokemon species
      const speciesData = await speciesRes.json();
      const variety = speciesData.varieties.find(v => v.is_default);
      const pokemonRes = await fetch(variety.pokemon.url); //i z endpointu pokemon
      const pokemonData = await pokemonRes.json();
      const englishEntry = speciesData.flavor_text_entries.find( //opis
        entry => entry.language.name === "en"
      );
      const flavorText = englishEntry ? englishEntry.flavor_text.replace(/[\n\f]/g, " ") : "No description available.";
      const spriteUrl = pokemonData.sprites.front_default;
      const image = await preloadImage(spriteUrl); //pobranie zdjęcia z funkcją z polecenia
      pokemonName.textContent = capitalize(name); //pokename to h2
      pokemonImg.src = image.src;
      pokemonTypes.innerHTML = "";
      pokemonData.types.forEach(type => { //typy
        const span = document.createElement("span");
        span.className = "type";
        span.textContent = capitalize(type.type.name);
        pokemonTypes.appendChild(span);
      });
      pokemonStats.innerHTML = "";
      pokemonData.stats.forEach(stat => { //staty
        const statDiv = document.createElement("div");
        statDiv.className = "stat";
        const nameSpan = document.createElement("span");
        nameSpan.textContent = formatStatName(stat.stat.name);
        const valueSpan = document.createElement("span");
        valueSpan.textContent = stat.base_stat;
        statDiv.appendChild(nameSpan);
        statDiv.appendChild(valueSpan);
        pokemonStats.appendChild(statDiv);
      });
      pokemonFlavorText.textContent = flavorText;
      errorText.style.display = "none";
      pokemonDetails.style.display = "flex";
    } catch (e) {
      showError();
    } finally {
      hideLoading();
    }
}

function capitalize(str) {
    return str.charAt(0).toUpperCase() + str.slice(1);
}

function formatStatName(name) {
    return name.replace("-", " ").replace(/\b\w/g, c => c.toUpperCase());
}

fetchPokemonList();

