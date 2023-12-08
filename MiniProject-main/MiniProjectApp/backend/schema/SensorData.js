import mongoose from 'mongoose';

const sensorSchema = new mongoose.Schema(
    {
        accStatus:{
            type: Boolean,
            required: true,
        },
        accX: {
            type: Number,
            required: true,
        },
        accY: {
            type: Number,
            required: true,
        },
        accZ: {
            type: Number,
            required: true,
        },
        danger:{
            type: Boolean,
            required: true,
        },
        gyX: {
            type: Number,
            required: true,
        },
        gyY: {
            type: Number,
            required: true,
        },
        gyZ: {
            type: Number,
            required: true,
        },
        
        gyroStatus:{
            type: Boolean,
            required: true,
        },
        
        
        // temp: {
        //     type: Number,
        //     required: true,
        // },
        // vib: {
        //     type: Number,
        //     required: true,
        // }

    },{timestamps:true}

)

const SensorData = mongoose.model("SensorData", sensorSchema);
export default SensorData;