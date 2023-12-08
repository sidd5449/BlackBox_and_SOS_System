import { View, Text, StyleSheet, Image, Button, Pressable } from "react-native";
import React from "react";
import { sendEmergencyMsg, sendMsg } from "../utils/sendMsg";
import Glasses from "../assets/glasses.png";

export const txtColor = (status) => {
  if (status === "true") {
    return "#048501";
  } else {
    return "#750111";
  }
};

const Hero = () => {
  return (
    <View style={styles.container}>
      <View style={styles.box}>
        <Image source={Glasses} style={styles.glasses} />
        <Text style={styles.text1}>Your Device</Text>
        <Text style={styles.text2}>SmartGlasses Version 1.0</Text>
      </View>

      {/* Body  */}

      <View style={styles.mainbody}>
        <Text style={styles.text3}>Device Status</Text>
        <View style={styles.flex1}>
          <Text
            style={{
              color: txtColor("true"),
            }}
          >
            Accelerometer
          </Text>

          <Text
            style={{
              color: txtColor("true"),
            }}
          >
            Gyroscope
          </Text>
        </View>
        <Pressable style={styles.button} onPress={sendEmergencyMsg}>
          <Text style={{ color: "#fff" }}>Request Assistance</Text>
        </Pressable>
      </View>
    </View>
  );
};
const styles = StyleSheet.create({
  button: {
    borderWidth: 1,
    borderColor: "#fe0000",
    backgroundColor: "#fe0000",
    borderRadius: 15,
    width: 150,
    height: 60,
    display: 'flex',
    alignItems: "center",
    justifyContent: "center",
    marginLeft: 90,
    padding: 2,
    elevation: 5,
  },
  container: {
    // marginTop: -20,
    height: 1000,
    width: 360,
    backgroundColor: "#e1ebf0",
    // alignItems: 'center',
  },

  box: {
    position: "relative",
    marginTop: 30,
    marginLeft: 20,
    marginRight: 20,

    width: 320,
    height: 200,

    borderRadius: 20,
    backgroundColor: "#0c2340",
    // shadowColor: 'black',
    // shadowOffset: {width: 10, height: 10},
    // shadowOpacity: 1,
    // shadowRadius: 3,
    elevation: 3,
    zIndex:999,
  },

  glasses: {
    position: "absolute",
    left: -60,
    bottom: -40,
  },

  text1: {
    position: "absolute",
    left: 20,
    top: 12,
    color: "#fff",
    // fontFamily: "PoppinsRegular",
  },

  text2: {
    position: "absolute",
    bottom: 10,
    left: 140,

    color: "#fff",
    fontWeight: "bold",
    fontFamily: "Nebula",
  },
  // Body style

  mainbody: {
    marginTop: 20,
    marginLeft: 13,
  },
  text3: {
    color: "#000",
    fontSize: 20,
    fontWeight: "bold",
    marginLeft: 13,
    // fontFamily: "PoppinsRegular",
  },

  flex1: {
    display: "flex",
    flexDirection: "row",
    justifyContent: "space-around",
    width: 320,
    marginTop: 32,
    marginBottom: 50,
    // fontFamily: "PoppinsBold",
  },
});

export default Hero;
