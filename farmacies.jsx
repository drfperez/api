import React, { useState, useEffect } from 'react';
import { StyleSheet, View, Text, TextInput, TouchableOpacity, FlatList } from 'react-native';

const PharmacySearch = () => {
  const [postalCode, setPostalCode] = useState('');
  const [results, setResults] = useState([]);

  const getData = async () => {
    try {
      const response = await fetch('https://pompeu.neocities.org/farmacies/farmacies.json');
      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      } else {
        const data = await response.json();
        return data;
      }
    } catch (error) {
      console.error(error);
    }
  }

  const search = async () => {
    const data = await getData();
    const searchResults = data.filter(pharmacy => pharmacy['CODI POSTAL'] === postalCode);
    setResults(searchResults);
  }

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Pharmacy Search</Text>
      <Text style={styles.explanation}>This is a Search to find Catalan pharmacies from their postal code</Text>
      <TextInput
        style={styles.input}
        placeholder="Postal Code"
        value={postalCode}
        onChangeText={text => setPostalCode(text)}
      />
      <TouchableOpacity style={styles.searchButton} onPress={search}>
        <Text style={styles.searchButtonText}>Search</Text>
      </TouchableOpacity>
      <FlatList
        data={results}
        renderItem={({ item, index }) => (
          <View style={styles.resultContainer}>
            <Text style={styles.resultTitle}>{item['NOM FARMACIA']}</Text>
            <Text style={styles.resultText}>Municipality: {item['NOM MUNICIPI']}</Text>
                        <Text style={styles.resultText}>Postal Code: {item['CODI POSTAL']}</Text>
            <Text style={styles.resultText}>ABS Code: {item['CODI ABS']}</Text>
            <Text style={styles.resultText}>ABS Name: {item['NOM ABS']}</Text>
            <Text style={styles.resultText}>
              Address: {item['TIPUS VIA']} {item['NOM VIA']}, {item['NUMERO VIA']}
            </Text>
          </View>
        )}
        keyExtractor={(item, index) => index.toString()}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
  },
  title: {
    fontSize: 20,
    fontWeight: 'bold',
    textAlign: 'center',
    marginBottom: 10,
  },
  explanation: {
    fontSize: 16,
    textAlign: 'center',
    marginBottom: 10,
  },
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    padding: 10,
    marginBottom: 10,
  },
  searchButton: {
    backgroundColor: 'blue',
    padding: 10,
    alignItems: 'center',
  },
  searchButtonText: {
    color: 'white',
  },
  resultContainer: {
    padding: 10,
    margin: 10,
    backgroundColor: 'lightgray',
  },
  resultTitle: {
    fontWeight: 'bold',
    marginBottom: 5,
  },
  resultText: {
    marginBottom: 5,
  },
});

export default PharmacySearch;

