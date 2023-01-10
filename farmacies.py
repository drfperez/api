import tkinter as tk
from tkinter import ttk
import requests

def get_data():
    response = requests.get('https://pompeu.neocities.org/farmacies/farmacies.json')
    if response.status_code != 200:
        raise ValueError(f'HTTP error! status: {response.status_code}')
    else:
        return response.json()

def search():
    postal_code = entry.get()
    data = get_data()
    search_results = [pharmacy for pharmacy in data if pharmacy['CODI POSTAL'] == postal_code]
    for i, result in enumerate(search_results):
        table.insert('', 'end', values=(i+1, result['NOM FARMACIA'], result['CODI POSTAL'], result['CODI ABS'], result['NOM ABS'], result['TIPUS VIA'], result['NOM VIA'], result['NUMERO VIA'], result['NOM MUNICIPI']))

root = tk.Tk()
root.title("Pharmacy Search")

#title 
title = tk.Label(root, text="Pharmacy Search", font=("Arial", 16))
title.grid(row=0, column=0, columnspan=3, padx=5, pady=5, ipadx=5, ipady=5)

#explanation
explanation = tk.Label(root, text="This is a Search to find Catalan pharmacies from their postal code")
explanation.grid(row=1, column=0, columnspan=3, padx=5, pady=5, ipadx=5, ipady=5)

#label
label = tk.Label(root, text="Postal Code:")
label.grid(row=2, column=0, padx=5, pady=5)

#entry
entry = tk.Entry(root)
entry.grid(row=2, column=1, padx=5, pady=5)

#search button
search_button = tk.Button(root, text="Search", command=search)
search_button.grid(row=2, column=2, padx=5, pady=5)

#table
table = ttk.Treeview(root, columns=("No", "Pharmacy Name", "Postal Code", "ABS Code", "ABS Name", "Type of Street", "Street Name", "Street Number", "Municipality"), show="headings")
table.heading("No", text="No.")
table.heading("Pharmacy Name", text="Pharmacy Name")
table.heading("Postal Code", text="Postal Code")
table.heading("ABS Code", text="ABS Code")
table.heading("ABS Name", text="ABS Name")
table.heading("Type of Street", text="Type of Street")
table.heading("Street Name", text="Street Name")
table.heading("Street Number", text="Street Number")
table.heading("Municipality", text="Municipality")
table.column("No", width=50)
table.column("Pharmacy Name", width=150)
table.column("Postal Code", width=100)
table.column("ABS Code", width=100)
table.column("ABS Name", width=150)
table.column("Type of Street", width=150)
table.column("Street Name", width=150)
table.column("Street Number", width=100)
table.column("Municipality", width=150)
table.grid(row=3, column=0, columnspan=3, padx=5, pady=5)

root.mainloop()

