import express from 'express';
import bodyParser from 'body-parser';
import mongoose, { mongo } from 'mongoose';
import cors from 'cors';
import dotenv from 'dotenv';
import { createPost } from './controllers/post.js';
// import postRoutes from './routes/post.js'
import SensorData from './schema/SensorData.js';

// CONFIGURATION

dotenv.config();
const app = express();
app.use(express.json());
app.use(bodyParser.json({limit: "30mb", extended:true}))
app.use(bodyParser.urlencoded({ limit: "30mb", extended: true }))
app.use(cors());



// ROUTES WITH FILES
app.post("/post", createPost)

// ROUTES 
// app.use("/posts", postRoutes);


// MONGOOSE CONGIF
const PORT = process.env.PORT || 6001;
mongoose.connect(process.env.MONGO_URI, {
    useNewUrlParser:true,
    useUnifiedTopology: true,

}).then(() => {
    app.listen(PORT, () => console.log(`SERVER PORT ${PORT}`));
}).catch((error) => console.log(`${error} did not connect`))
