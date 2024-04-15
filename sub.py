#pip install paho-mqtt
import paho.mqtt.client as mqtt
import requests
import json

def on_connect(client, userdata, flags, rc):
    print(f"Connected to broker {rc}")
    client.subscribe("users")

def on_message(client, userdata, msg):
    try:
        data = json.loads(msg.payload.decode())
        requests.post("http://192.168.43.248:3000/users", json=data)
        print(f"Message on topic {msg.topic}: {msg.payload.decode()}. Data posted successfully to the API")
    except (json.JSONDecodeError, requests.RequestException) as e:
        print(f"Error: {e}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("192.168.43.248", 1883)
client.loop_forever()