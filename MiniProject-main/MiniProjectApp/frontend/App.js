import { createStackNavigator } from '@react-navigation/stack';
import { NavigationContainer, DefaultTheme, useNavigation } from '@react-navigation/native';
import { useFonts } from 'expo-font';
import { Home, User, Login } from './screens';
import axios from 'axios';
import { useEffect, useState } from 'react';
import AsyncStorage from '@react-native-async-storage/async-storage';
import { sendMsg } from './utils/sendMsg';
import FindLocalDevices from 'react-native-find-local-devices';
import { DeviceEventEmitter } from 'react-native';



const Stack = createStackNavigator();

export default function App() {

  const [loaded] = useFonts({
    PoppinsLight: require("./fonts/Poppins-Light.ttf"),
    PoppinsBold: require("./fonts/Poppins-Bold.ttf"),
    PoppinsExtraBold: require("./fonts/Poppins-ExtraBold.ttf"),
    PoppinsMedium: require("./fonts/Poppins-Medium.ttf"),
    PoppinsSemiBold: require("./fonts/Poppins-SemiBold.ttf"),
    PoppinsRegular: require("./fonts/Poppins-Regular.ttf"),
    Nebula: require("./fonts/Nebula-Regular.otf"),
  })
  // if(!loaded) return null;
  const [sensData, setsensData] = useState([]);
// axios.get('http://192.168.47.18').then((data) => {setsensData(data)});
setInterval(() => {
  axios.get('http://192.168.4.1').then((data) => {
    axios.post('https://blackbox-api.onrender.com/post', data);
    console.log(data);
    // console.log(data.danger);
    setsensData(data);
    const jsonString = JSON.stringify(data);
    
    const timestamp = new Date().getTime();
    const key = `data_${timestamp}`;
    if(data.data.danger){
      sendMsg();
    }
   })
    
    // console.log(sensData);
    // const jsonString = JSON.stringify(data);
    
    // const timestamp = new Date().getTime();
    // const key = `data_${timestamp}`;
    // AsyncStorage.setItem(key, jsonString).then(() => {
    //   console.log('stored');
    // })
    // .catch((Err) => {
    //   console.error(Err);
    // })
    // console.log(data.danger);
  //   if(data.danger){
  //     sendMsg();
  //   }
  //  })
}, 10000);
// getIp;

// READ LOCAL DATA
// AsyncStorage.getItem('myKey')
//   .then((jsonString) => {
//     // Convert the JSON string back to an object
//     const jsonData = JSON.parse(jsonString);
//     console.log('Retrieved JSON data:', jsonData);
//   })
//   .catch((error) => {
//     console.error('Failed to retrieve JSON data:', error);
//   });


if(!loaded) return null;
  
  return (
    <NavigationContainer>
      <Stack.Navigator screenOptions={{ headerShown: false }}
        initialRouteName='Home'
      >
        <Stack.Screen name='Home' component={Home} />
        <Stack.Screen name='User' component={User} />
        <Stack.Screen name='Login' component={Login} />
      </Stack.Navigator>
    </NavigationContainer>
  );
}

