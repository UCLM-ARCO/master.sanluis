#!flask/bin/python
from flask import Flask, jsonify

app = Flask(__name__)

sensors = [
    {
        'id': 1,
        'location': u'Universidad de San Luis',
        'description': u'sensor en clase de master sanluis', 
        'tipo': u'Temperatura'
    },
    {
        'id': 2,
        'location': u'Escuela Superior de Informatica',
        'description': u'sensor en la ESI', 
        'tipo': u'Temperatura'
    }
]

@app.route('/iot/api/v1.0/sensors', methods=['GET'])
def get_tasks():
    return jsonify({'sensors': sensors})

from flask import abort

@app.route('/iot/api/v1.0/sensors/<int:sensor_id>', methods=['GET'])
def get_sensor(sensor_id):
    sensor = [sensor for sensor in sensors if sensor['id'] == sensor_id]
    if len(sensor) == 0:
        abort(404)
    return jsonify({'sensor': sensor[0]})

from flask import request

@app.route('/iot/api/v1.0/sensors', methods=['POST'])
def create_sensor():
    if not request.json or not 'location' in request.json:
        abort(400)
    sensor = {
        'id': sensors[-1]['id'] + 1,
        'location': request.json['location'],
        'description': request.json.get('description', ""),
        'tipo': request.json.get('tipo',"")
    }
    sensors.append(sensor)
    return jsonify({'sensor': sensor}), 201


@app.route('/iot/api/v1.0/sensors/<int:sensor_id>', methods=['PUT'])
def update_sensor(sensor_id):
    sensor = [sensor for sensor in sensors if sensor['id'] == sensor_id]
    if len(sensor) == 0:
        abort(404)
    if not request.json:
        abort(400)
    if 'location' in request.json and type(request.json['location']) != unicode:
        abort(400)
    if 'description' in request.json and type(request.json['description']) is not unicode:
        abort(400)
    if 'tipo' in request.json and type(request.json['tipo']) is not unicode:
        abort(400)
    sensor[0]['location'] = request.json.get('location', sensor[0]['location'])
    sensor[0]['description'] = request.json.get('description', sensor[0]['description'])
    sensor[0]['tipo'] = request.json.get('tipo', sensor[0]['tipo'])
    return jsonify({'sensor': sensor[0]})



@app.route('/iot/api/v1.0/sensors/<int:sensor_id>', methods=['DELETE'])
def delete_sensor(sensor_id):
    print sensor_id
    sensor = [sensor for sensor in sensors if sensor['id'] == sensor_id]
    if len(sensor) == 0:
        abort(404)
    sensors.remove(sensor[0])
    return jsonify({'result': True})


if __name__ == '__main__':
    app.run(debug=True)
