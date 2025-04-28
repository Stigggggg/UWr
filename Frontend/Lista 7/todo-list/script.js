//wyciągamy formularz todo z HTML
const form = document.getElementById("add-todo-form");
//to samo z polem input
const input = form.querySelector("input[name='todo-name']");
//to samo z todo listą
const list = document.getElementById("todo-list");
//to samo z licznikiem zadań todo
const countSpan = document.getElementById("count");
//i z guzikiem do clearowania
const clearButton = document.getElementById("todos-clear");

//lista zadań jako obiektów
const todos = [];
document.querySelectorAll("#todo-list li").forEach((li) => {
  const name = li.querySelector(".todo-name").innerText.trim();
  const done = li.classList.contains("todo__container--completed");
  todos.push({ name, done });
})

function render() {
  list.innerHTML = ""; //czyścimy listę
  todos.forEach((todo, index) => {
    const li = document.createElement("li"); //dodawany element to li
    li.className = "todo__container" + (todo.done ? " todo__container--completed" : ""); //default klasa to todo__container, jeśli zadanie wykonane to jeszcze jedna
    const nameDiv = document.createElement("div"); //element div z nazwą
    nameDiv.className = "todo-element todo-name";
    nameDiv.textContent = todo.name;
    //tworzymy potrzebne przyciski
    const upBtn = createButton("↑", "move-up", () => moveItem(index, -1));
    const downBtn = createButton("↓", "move-down", () => moveItem(index, 1));
    const toggleBtn = createButton(todo.done ? "Revert" : "Done", "", () => toggleDone(index));
    const removeBtn = createButton("Remove", "", () => removeItem(index));
    li.append(nameDiv, upBtn, downBtn); //na pewno dodajemy nazwę, górę i dół
    if (!todo.done) {
      li.append(toggleBtn);  //jeśli niezrobione zadanie, to toggle będzie miał opcję Done
    } 
    else {
      li.append(toggleBtn); //wpp opcja Revert
    }
    li.append(removeBtn); //na koniec appendujemy guzik Remove
    [upBtn, downBtn, toggleBtn, removeBtn].forEach(btn => {
      btn.classList.add("todo-element", "todo-button"); //każdy guzik musi mieć klasę element i button zgodnie z poleceniem
    });
    list.appendChild(li); //gotowy element li appendujemy do listy
  });
  updateCount();
}

//tworzenie przycisku z razem z jego klasami
function createButton(text, extraClass, onClick) {
  const btn = document.createElement("button");
  btn.textContent = text;
  if (extraClass) {
    btn.classList.add(extraClass);
  } 
  btn.addEventListener("click", onClick); //dodajemy responsywność na kliknięcie
  return btn;
}

//update countera
function updateCount() {
  const remaining = todos.filter(todo => !todo.done).length; //filtrujemy niezrobione zadania, ich liczba się wyświetla
  countSpan.textContent = remaining;
}

//przesuwanie elementu w górę i w dół
function moveItem(index, direction) {
  const newIndex = index + direction;
  if (newIndex >= 0 && newIndex < todos.length) {
    [todos[index], todos[newIndex]] = [todos[newIndex], todos[index]]; //zamiana miejscami zadań
    render();
  }
}

//zmiana stanu wykonania, żeby wyświetlało się odpowiednio done/revert
function toggleDone(index) {
  todos[index].done = !todos[index].done;
  render();
}

//usunięcie z listy
function removeItem(index) {
  todos.splice(index, 1);
  render();
}

//submit dodania elementu do listy
form.addEventListener("submit", (e) => {
  e.preventDefault(); //zapobiegamy odświeżeniu strony
  const value = input.value.trim();
  if (value) {
    todos.push({ name: value, done: false });
    input.value = "";
    render();
  }
});

//obsługa clear all
clearButton.addEventListener("click", () => {
  todos.length = 0; //czyscimy liste todo
  render();
});

render();
