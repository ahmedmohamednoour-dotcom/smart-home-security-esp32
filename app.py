import serial
import csv
from datetime import datetime
from flask import Flask, jsonify, render_template
import threading
import time

# Initialize Flask app
app = Flask(__name__)

# Initialize variables for sensor data  
sensor_data = {
    "temperature": "N/A",
    "humidity": "N/A",
    "alcohol": "N/A",
    "light_intensity": "N/A",
    "timestamp": "N/A"
}

# Serial setup for Bluetooth communication (ensure COM port is correct)
bluetooth_serial = serial.Serial('COM15', 115200)  # Replace 'COM' with your ESP32's Bluetooth COM port

# Route to serve the main page
@app.route('/')
def index():
    return render_template('index.html')

# Route to serve sensor data as JSON
@app.route('/data')
def data():
    return jsonify(sensor_data)

# Function to continuously read data from the ESP32 and update sensor_data
def read_from_esp32():
    while True:
        try:
            data = bluetooth_serial.readline().decode('utf-8').strip()  # Read and decode data
            if data:
                print(f"Received: {data}")  # Optional print for debugging
                data_list = data.split(',')
                
                if len(data_list) >= 2:
                    # Fill in missing values with '0' for alcohol and light intensity if not received
                    data_list += ['0'] * (4 - len(data_list))

                    # Update sensor_data dictionary
                    sensor_data.update({
                        "temperature": data_list[0],
                        "humidity": data_list[1],
                        "alcohol": data_list[2],
                        "light_intensity": data_list[3],
                        "timestamp": datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    })

                    # Optionally log the data into a CSV file
                    with open('sensor_data.csv', mode='a', newline='') as file:
                        writer = csv.writer(file)
                        writer.writerow([sensor_data["timestamp"], sensor_data["temperature"], sensor_data["humidity"], sensor_data["alcohol"], sensor_data["light_intensity"]])

                else:
                    print("Data format error: received unexpected data.")
        except Exception as e:
            print(f"Error: {e}")
            break

# Start the data reading in a background thread
data_thread = threading.Thread(target=read_from_esp32, daemon=True)
data_thread.start()

# Run the Flask app
if __name__ == '__main__':
    app.run(port =5000)
