import { StatusBar, View } from "react-native";
import React from "react";
import Navbar from "../components/Navbar";
import Hero from "../components/Hero";
import { SafeAreaView } from "react-native-safe-area-context";
import FocusedStatusBar from "../components/FocusedStatusBar";

const Home = () => {

  return (
    
    <SafeAreaView>
    {/* <FocusedStatusBar background = "#000" /> */}
    <StatusBar style="dark" />
    <View>
      <Navbar />
      <Hero />
    </View>
    </SafeAreaView>
  );
};

export default Home;
