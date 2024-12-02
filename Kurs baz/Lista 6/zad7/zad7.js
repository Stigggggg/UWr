const { MongoClient } = require("mongodb");

async function run() {
    const uri = "mongodb://localhost:27017";
    const client = new MongoClient(uri);
    try {
        await client.connect();
        console.log("Connected to MongoDB!");
        const db = client.db("sales");
        const items = db.collection("items");
        await items.insertMany([
            {
                item: "laptop",
                price: 3500,
                quantity: 5  
            },
            {
                item: "phone",
                price: 2000,
                quantity: 10
            },
            {
                item: "headphones",
                price: 500,
                quantity: 10
            }
        ]);
        console.log("Items inserted!");
        const aggregation = items.aggregate([
            {
                $group: {
                    _id: "$item",
                    total_quantity: { $sum: "$quantity" },
                    total_income: { $sum: { $multiply: ["$quantity", "$price"] } }
                }
            }
        ]);
        const results = await aggregation.toArray()
        console.log("Aggregation done!");
        console.log(JSON.stringify(results, null, 2));
    } catch (err) {
        console.error("An error occurred:", err.message);
    } finally {
        await client.close();
        console.log("Connection closed!");
    }
}

run().catch(console.error);
