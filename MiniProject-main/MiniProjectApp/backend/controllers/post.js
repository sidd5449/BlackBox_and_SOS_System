import SensorData from "../schema/SensorData.js";

// CREATE
export const createPost = async (req, res) => {
    try {
        console.log(req);
        const {data} = req.body;
        const newPost = new SensorData(data)

        await newPost.save();

        res.status(201).json(data);
    } catch (err) {
        res.status(409).json({message:err.message})
    }
}

