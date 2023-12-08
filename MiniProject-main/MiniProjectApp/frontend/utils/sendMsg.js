import * as SMS from 'expo-sms';
import { userInfo } from './userInfo';
import * as Location from 'expo-location';

export const sendMsg = async() => {
    const isAvailable = await SMS.isAvailableAsync();
    const {status} = await Location.requestForegroundPermissionsAsync();
    if(status !== 'granted'){
        console.error('permission denied');
        return;
    }

    const { coords } = await Location.getCurrentPositionAsync();
    console.log(coords);
    if(isAvailable){
        const { result } = await SMS.sendSMSAsync(userInfo.sosNos, `Accident detected at https://www.google.com/maps/search/?api=1&query=${coords.latitude}%2C${coords.longitude}`);
        if(result==='sent'){
            console.log('msg sent');

        }
        else{
            console.error('msg not sent', result);
        }
    }
}
export const sendEmergencyMsg = async() => {
    const isAvailable = await SMS.isAvailableAsync();
    const {status} = await Location.requestForegroundPermissionsAsync();
    if(status !== 'granted'){
        console.error('permission denied');
        return;
    }

    const { coords } = await Location.getCurrentPositionAsync();
    console.log(coords);
    if(isAvailable){
        const { result } = await SMS.sendSMSAsync(userInfo.sosNos, `Driver needs emergency medical assistance at https://www.google.com/maps/search/?api=1&query=${coords.latitude}%2C${coords.longitude}`);
        if(result==='sent'){
            console.log('msg sent');

        }
        else{
            console.error('msg not sent', result);
        }
    }
}