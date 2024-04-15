from flask import Flask, jsonify, render_template
import requests
from paho.mqtt import client as mqtt_client

broker  = "192.168.43.248"
port = 1883

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client("server")
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


app = Flask(__name__)
server_ip = "http://192.168.43.248:3000"

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/getusers")
def getusers():
    headers = {'Accept': 'application/json'}
    url = "http://192.168.43.248:3000/users"
    r = requests.get(url, headers=headers)
    return r.json();

@app.route("/deleteuser/<int:user_id>", methods=["DELETE"])
def delete_user(user_id):
    headers = {'Accept': 'application/json'}
    url = f"http://192.168.43.248:3000/users/{user_id}"
    r = requests.delete(url, headers=headers)

    if r.status_code == 200:
        return jsonify({"message": "User deleted successfully"})
    else:
        return jsonify({"error": f"Failed to delete user. Status code: {r.status_code}"}), r.status_code

if __name__ == "__main__":
    client = connect_mqtt()
    app.run(host='0.0.0.0', debug=True)