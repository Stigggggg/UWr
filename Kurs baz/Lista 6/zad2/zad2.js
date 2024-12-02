const { MongoClient } = require("mongodb");

async function run() {
    const uri = "mongodb://localhost:27017";
    const client = new MongoClient(uri);
    try {
        await client.connect();
        console.log("Connected to MongoDB!");
        const db = client.db("library");
        const books = db.collection("books");
        await books.insertMany([
            {
                _id: "book1",
                title: "Pan Tadeusz",
                author: "Adam Mickiewicz",
                copies: [
                    { 
                        copy_id: "copy1", 
                        status: "available" 
                    },
                    { 
                        copy_id: "copy2", 
                        status: "borrowed" 
                    }
                ]
            },
            {
                _id: "book2",
                title: "Kordian",
                author: "Juliusz Słowacki",
                copies: [
                    { 
                        copy_id: "copy3",
                        status: "available" 
                    }
                ]
            }
        ]);
        console.log("Inserted books!");
        const readers = db.collection("readers");
        await readers.insertMany([
            { 
                _id: "reader1", 
                name: "Jan Kowalski", 
                contact: {email: "jankowalski@gmail.com", phone: "000000001"}
            },
            { 
                _id: "reader2", 
                name: "Andrzej Nowak",
                contact: {email: "andrzejnowak@gmail.com", phone: "123456789"}
            }
        ]);
        console.log("Inserted readers!");
        const borrowings = db.collection("borrowings");
        await borrowings.insertMany([
            { 
                _id: "borrow1", 
                book_id: "book1", 
                copy_id: "copy2", 
                reader_id: "reader1", 
                borrow_date: "2024-11-01" 
            },
            { 
                _id: "borrow2", 
                book_id: "book1",
                copy_id: "copy1", 
                reader_id: "reader2", 
                borrow_date: "2024-11-02" 
            },
            { 
                _id: "borrow3", 
                book_id: "book2", 
                copy_id: "copy3", 
                reader_id: "reader1", 
                borrow_date: "2024-11-03" 
            },
            { 
                _id: "borrow4",
                book_id: "book1", 
                copy_id: "copy1", 
                reader_id: "reader2", 
                return_date: "2024-11-10" 
            }
        ]);
        console.log("Inserted borrowings!");
    } catch (err) {
        console.error("An error occurred:", err.message);
    } finally {
        await client.close();
        console.log("Connection closed!");
    }
}

run().catch(console.error);

//do zad4
//db.borrowings.find().sort({_id: 1}).skip(1).limit(2)
//db.readers.find({"contact.email": "jankowalski@gmail.com"})