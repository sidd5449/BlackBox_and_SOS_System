import { BleManager } from 'react-native-ble-plx';
import { Stitch, RemoteMongoClient } from 'mongodb-stitch-react-native-sdk';

const manager = new BleManager();

// initialize the Stitch app
const stitchApp = Stitch.initializeDefaultAppClient('<Your-Stitch-App-ID>');

// get a client of the remote MongoDB service
const mongoClient = stitchApp.getServiceClient(
    RemoteMongoClient.factory,
    '<Your-MongoDB-Service-Name>'
);

// get a reference to the collection
const collection = mongoClient.db('<Your-Database-Name>').collection('<Your-Collection-Name>');

// scan for devices
manager.startDeviceScan(null, null, (error, device) => {
    if (error) {
        // handle error
        return;
    }

    // check if this is the device we want to connect to
    if (device.name === 'Nano33IoT') {
        // stop scanning
        manager.stopDeviceScan();

        // connect to the device
        device.connect()
            .then((device) => {
                // discover services and characteristics
                return device.discoverAllServicesAndCharacteristics();
            })
            .then((device) => {
                // get the characteristic that we want to read data from
                return device.readCharacteristicForService(
                    "19B10000-E8F2-537E-4F6C-D104768A1214",
                    "19B10001-E8F2-537E-4F6C-D104768A1214"
                );
            })
            .then((characteristic) => {
                // successfully read data from the characteristic
                // get the data as a string
                let data = characteristic.value;

                // do something with the data

                // insert the data into the MongoDB Atlas collection
                return collection.insertOne({ data: data });
            })
            .then((result) => {
                // successfully inserted the data into the MongoDB Atlas collection
            })
            .catch((error) => {
                // handle error
            });
    }
});