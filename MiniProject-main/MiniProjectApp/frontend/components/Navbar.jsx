import { View, Text, StyleSheet, Image } from "react-native";
import React from "react";
import User from "../assets/user.png";
import Logo from "../assets/logoTag-color.png";

const Navbar = () => {
  return (
    <View style={styles.container}>
      <View style={styles.logoContainer}>
        <Image source={Logo} style={styles.userlogo} />
        {/* <Text style={styles.logoText}>LOGO</Text> */}
      </View>
      <View style={styles.circle}>
        <Image source={User} style={styles.usericon} />
      </View>
    </View>
  );
};
const styles = StyleSheet.create({
  container: {
    // borderRadius: (0, 12, 12, 0),
    // marginTop: 20,
    height: 70,
    display: 'flex',
    backgroundColor: "#ffffff",
    flexDirection: "row",
    alignItems: "center",
    paddingHorizontal: 0,
    justifyContent:"center",
    shadowColor: '#000000',
    shadowOffset: {width: -2, height: 8},
    shadowOpacity: 0.2,
    shadowRadius: 3,
    elevation: 10,
  },
  logoContainer: {
    flex: 1,
    justifyContent: "center",
  },
  logoText: {
    fontSize: 20,
    // fontFamily: "PoppinsExtraBold",
    fontWeight: "bold",
    color: "#fff",
  },
  circle: {
    alignItems: "center",
    justifyContent: "center",
    width: 40,
    height: 40,
    borderRadius: 50,
    borderColor: "#fe0000",
    marginRight: 20,
    borderWidth: 2,
    // borderColor: "#fff",
  },

  usericon: {
    width: 25,
    height: 25,
  },

  userlogo: {
    width: 200,
    height: 60,
  },
});

export default Navbar;
