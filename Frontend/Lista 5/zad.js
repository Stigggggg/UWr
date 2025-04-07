/**
 * @typedef {Object} Product
 * @property {number} id - unikalny identyfikator produktu
 * @property {string} name - nazwa produktu
 * @property {number} quantity - liczba sztuk do zakupienia
 * @property {Date} purchaseBy - data, do której produkt powinien być zakupiony
 * @property {boolean} purchased - status informujący, czy produkt został zakupiony
 * @property {number} [pricePerUnit] - opcjonalna cena za sztukę (dotyczy tylko zakupionych produktów)
 */

/** @type {Product[]} */
let shoppingList = [];

/**
 * generuje unikalne ID
 * @returns {number} ID
 */
function generateId() {
    return Math.floor(Math.random() * 1e9);
}

/**
 * dodaje nowy produkt do listy zakupów
 * @param {string} name - nazwa produktu
 * @param {number} quantity - liczba sztuk
 * @param {string} dateString - data (YYYY-MM-DD)
 */
function addProduct(name, quantity, dateString) {
    const newProduct = {
        id: generateId(),
        name,
        quantity,
        purchaseBy: new Date(dateString),
        purchased: false,
    };
    shoppingList.push(newProduct);
}

/**
 * usuwa produkt z listy zakupów na podstawie ID
 * @param {number} id - ID produktu
 */
function removeProduct(id) {
    shoppingList = shoppingList.filter(product => product.id !== id);
}

/**
 * aktualizuje nazwę produktu
 * @param {number} id - ID produktu
 * @param {string} newName - nowa nazwa
 */
function updateProductName(id, newName) {
    const product = shoppingList.find(product => product.id === id);
    if (product) product.name = newName;
}

/**
 * aktualizuje status zakupu produktu
 * @param {number} id - ID produktu
 * @param {boolean} newStatus - nowy status
 */
function updateProductStatus(id, newStatus) {
    const product = shoppingList.find(product => product.id === id);
    if (product) product.purchased = newStatus;
}

/**
 * aktualizuje liczbę sztuk produktu
 * @param {number} id - ID produktu
 * @param {number} newQuantity - zmieniona liczba sztuk
 */
function updateProductQuantity(id, newQuantity) {
    const product = shoppingList.find(product => product.id === id);
    if (product) product.quantity = newQuantity;
}

/**
 * aktualizuje datę zakupu produktu
 * @param {number} id - ID produktu
 * @param {string} newDate - zmieniona data (YYYY-MM-DD)
 */
function updateProductDate(id, newDate) {
    const product = shoppingList.find(product => product.id === id);
    if (product) product.purchaseBy = new Date(newDate);
}

/**
 * zmienia kolejność produktów na liście
 * @param {number} id1 - ID pierwszego produktu
 * @param {number} id2 - ID drugiego produktu
 */
function swapProducts(id1, id2) {
    const index1 = shoppingList.findIndex(p => p.id === id1);
    const index2 = shoppingList.findIndex(p => p.id === id2);
    if (index1 !== -1 && index2 !== -1) {
        [shoppingList[index1], shoppingList[index2]] = [shoppingList[index2], shoppingList[index1]];
    }
}

/**
 * zwraca produkty do zakupienia dzisiaj
 * @returns {Product[]} lista produktów
 */
function getTodayPurchases() {
    const today = new Date().toDateString();
    return shoppingList.filter(product => !product.purchased && product.purchaseBy.toDateString() === today);
}

/**
 * dodaje cenę do zakupionego produktu
 * @param {number} id - ID produktu
 * @param {number} price - cena za sztukę
 */
function setProductPrice(id, price) {
    const product = shoppingList.find(product => product.id === id);
    if (product && product.purchased) {
        product.pricePerUnit = price;
    }
}

/**
 * oblicza koszt zakupów danego dnia
 * @param {string} dateString - data (YYYY-MM-DD)
 * @returns {number} całkowity koszt zakupów
 */
function calculateDailyCost(dateString) {
    const date = new Date(dateString).toDateString();
    return shoppingList.reduce((total, product) => {
        if (product.purchased && product.purchaseBy.toDateString() === date && product.pricePerUnit !== undefined) {
            return total + (product.pricePerUnit) * product.quantity;
        }
        return total;
    }, 0);
}

/**
 * masowo edytuje produkty na podstawie przekazanej funkcji
 * @param {number[]} ids - lista ID produktów do edycji
 * @param {(product: Product) => void} modifyFunction - funkcja modyfikująca produkt
 */
function bulkEditProducts(ids, modifyFunction) {
    shoppingList.forEach(product => {
        if (ids.includes(product.id)) {
            modifyFunction(product);
        }
    });
}

addProduct("Mleko", 2, "2025-04-01");
addProduct("Chleb", 1, "2025-04-01");
console.log(shoppingList, '\n');
const productId = shoppingList[0].id;
removeProduct(productId);
console.log(shoppingList, '\n');
updateProductName(shoppingList[0].id, "Bułka");
updateProductQuantity(shoppingList[0].id, 3);
updateProductDate(shoppingList[0].id, "2025-04-02");
console.log(shoppingList[0], '\n');
updateProductStatus(shoppingList[0].id, true);
console.log(shoppingList[0].purchased, '\n');
addProduct("Ser", 1, "2025-04-02");
swapProducts(shoppingList[0].id, shoppingList[1].id);
console.log(shoppingList.map(p => p.name), '\n');
console.log(getTodayPurchases(), '\n');
setProductPrice(shoppingList[1].id, 2.5);
console.log(shoppingList[1], '\n');
console.log(calculateDailyCost("2025-04-02"), '\n');
bulkEditProducts([shoppingList[1].id], product => {
    if (product.pricePerUnit) {
      product.pricePerUnit *= 4.3;
    }
  });
console.log(shoppingList[1].pricePerUnit, '\n');