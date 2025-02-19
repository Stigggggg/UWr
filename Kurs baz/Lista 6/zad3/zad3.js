const { MongoClient } = require("mongodb");

async function run() {
    const uri = "mongodb://localhost:27017";
    const client = new MongoClient(uri);
    try {
        await client.connect();
        console.log("Connected to MongoDB!");
        const db = client.db("library");
        await db.createCollection("books", {
            validator: {
                $jsonSchema: {
                    bsonType: "object",
                    required: ["_id", "title", "author", "copies"],
                    properties: {
                        _id: { bsonType: "string", description: "Unique identifier for the book" },
                        title: { bsonType: "string", description: "Title of the book" },
                        author: { bsonType: "string", description: "Author of the book" },
                        copies: {
                            bsonType: "array",
                            items: {
                                bsonType: "object",
                                required: ["copy_id", "status"],
                                properties: {
                                    copy_id: { bsonType: "string", description: "Unique identifier for the copy" },
                                    status: { enum: ["available", "borrowed"], description: "Copy status" }
                                }
                            }
                        }
                    }
                }
            }
        });
        console.log("Books with validation created!");
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
                title: 10,
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
    } catch (err) {
        console.error("An error occurred:", err.message);
    } finally {
        await client.close();
        console.log("Connection closed!");
    }
}

run().catch(console.error);