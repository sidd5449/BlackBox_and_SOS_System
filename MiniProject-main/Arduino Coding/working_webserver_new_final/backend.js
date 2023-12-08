const { MongoClient } = require('mongodb');

// create a new MongoClient instance
const client = new MongoClient(
    'mongodb+srv://dummy:dummy123@cluster0.i47wzbt.mongodb.net/?retryWrites=true&w=majority'
);

// connect to the MongoDB Atlas database
client.connect()
    .then(() => {
        // successfully connected to the database
        // get a reference to the collection
        const collection = client.db('Arduino_database_1').collection('mongoDB_colletion_for_arduino');

        // insert a document into the collection
        // here data is the json object received from arduino through app
        return collection.insertOne(data);
    })
    .then((result) => {
        // successfully inserted the document
    })
    .catch((error) => {
        // handle error
    });