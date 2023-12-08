import axios from 'axios';
import { useState } from 'react';

const [ip, setip] = useState()

const getIp = () => {
  let i=0;
  let j=0;
  for(i=0; i<=255; i++){
    for(j=0; j<=255; j++){
      axios.get(`http://192.168.${i}.${j}`).then((res) => {
        if(res.statusCode === 400){
          setip(`192.168.${i}.${j}`);
          console.log(ip);
        }
      })
    }
  }
}